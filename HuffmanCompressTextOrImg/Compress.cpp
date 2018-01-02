#include "Structure.h"
#include "BaseHuffmanTree.h"
#include <iostream>

using namespace std;

void compress()
{
	FILE *fp, *res;
	TreeNode *huf_tree;
	int i,leaf_num, num = 0;
	WeightType byte_length = 0,file_char_num = 0,file_length;
	char **map,**new_map,*temp;
	char *res_file_name = "resultfile.barack";
	MyQueue *qu = NULL;
	DataType ch, end_length, min, max, byte, m;

	qu = (MyQueue *)malloc(sizeof(MyQueue));
	init_cycle_queue(qu);

	fp = fopen("C://Users//22876//Desktop//test.txt", "r");
	if (!fp)
	{
		cout << "文件打开失败" << endl;
	}
	huf_tree = create_huffman_tree(fp, &leaf_num, &file_length);
	for (int i = 0; i < PIXELSIZE; i++)
	{
		printf("序号为：%d 像素值为：%d，权值为：%d 双亲结点为:%d:", i, huf_tree[i].data, huf_tree[i].weight, huf_tree[i].parent);
		printf("\n");
	}
	cout << "叶子结点数：" << leaf_num << endl;
	cout << "哈夫曼编码为:" << endl;
	map = get_huffman_code(huf_tree, leaf_num);
	//为了方便获取对应编码，重新建立一个字符编码表new_map
	new_map = (char **)malloc(PIXELSIZE * sizeof(char*)); 
	if (!new_map)
	{
		cout << "空间未开辟" << endl;
		return;
	}
	//初始化新表
	for (i = 0; i < PIXELSIZE; i++)
		new_map[i] = NULL;
	//将叶子结点对应的编码写入到新表中
	for (i = 0; i < leaf_num; i++)
	{
		new_map[(int)huf_tree[i].data] = map[i];
	}
	res = fopen(res_file_name, "wb");
	//将文件游标移动到一个位置，目的是为了给一些编码的信息留出空间
	fseek(res, sizeof(WeightType) + 2 * sizeof(int) + 4 * sizeof(DataType), SEEK_SET);
	//计算最大最小编码长度，并将每个叶子和编码长度写入文件中
	get_max_min_code_length(res, huf_tree, map, leaf_num, &max, &min);
	free(huf_tree);
	//将所有编码转换成字节写入文件中，并计算字节数
	num = copy_huffman_code_to_file(res, map, leaf_num, qu, &end_length);
	rewind(res); //将文件游标移动到开头位置
	fseek(res, sizeof(WeightType) + sizeof(DataType), SEEK_SET);
	fwrite(&leaf_num, sizeof(int), 1, res); //写入叶子结点数
	fwrite(&max, sizeof(DataType), 1, res); //写入最大编码长度
	fwrite(&min, sizeof(DataType), 1, res); //写入最小编码长度
	fwrite(&num, sizeof(int), 1, res); //写入编码字节数
	fwrite(&end_length, sizeof(DataType), 1, res); //写入最后剩余的字符数，需要特殊处理
	fseek(res, leaf_num * 2 * sizeof(DataType) + num, SEEK_CUR); //跨过之前写入的字节数，每个叶子结点和他们的编码长度
	rewind(fp); //将源文件重新定位回起点，准备压缩
	//压缩
	while (file_char_num < file_length)
	{
		ch = fgetc(fp); //从原文件中读取字符
		++file_char_num; 
		for (temp = new_map[ch]; *temp != '\0'; temp++) //将编码入队
		{
			in_queue(qu, *temp);
		}
		while (qu->length > 8)
		{
			byte = get_byte(qu);
			fputc(byte, res); //将合成的字节写入文件
			byte_length++; //统计字节数
		}
	}

	//处理最后剩下的和不成一个字节的编码
	end_length = qu->length; //剩下的位数
	m = 8 - end_length; //不足八位的位数
	byte = get_byte(qu); 
	//剩下不足八位的位置都用'0'补全
	for (i = 0; i < m; i++)
	{
		byte <<= 1;
	}
	fwrite(&byte, sizeof(DataType), 1, res);//将最后一个字节写入文件
	byte_length++;
	rewind(res); //将文件游标重新定位到开头，填写文件信息
	fwrite(&byte_length, sizeof(WeightType), 1, res); //写入压缩后的字节数
	fwrite(&end_length, sizeof(DataType), 1, res); //写入最后剩余的编码位数，在解压的时候需要特殊处理
	//计算新压缩后的文件长度
	byte_length = byte_length + 16 + num;
	cout << "压缩完成..." << endl;
	//cout << "字节数" << num << endl;
	//cout << "int" << sizeof(int) << endl; //4
	//cout << "WeightType" << sizeof(WeightType) << endl; //4
	//cout << "Datatype" << sizeof(DataType) << endl; //1
	//cout << "short" << sizeof(short) << endl; //2
	//计算压缩比率
	if (byte_length >= file_length)
	{
		cout << "压缩失败..." << endl;
	}
	else
	{
		cout << "原文件大小: " << file_length << endl;
		cout << "压缩文件大小: " << byte_length << endl;
		cout << "压缩比率为： " << (double)((file_length - byte_length) / (double)file_length * 100.0) << '%' << endl;
	}

	free(qu);
	free(map);
	free(new_map);
	fclose(fp);
	fclose(res);
}