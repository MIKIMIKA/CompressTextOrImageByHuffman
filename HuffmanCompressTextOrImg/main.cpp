#include "HuffmanCompressTextOrImg.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <stdio.h>
#include "Structure.h"
#include "BaseHuffmanTree.h"

using namespace std;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HuffmanCompressTextOrImg w;
	w.show();
	FILE *fp,*res;
	TreeNode *huf_tree;
	int leaf_num,num = 0;
	long file_length;
	char **map;
	char *res_file_name = "resultfile.barack";
	MyQueue *qu = NULL;
	DataType end_length,min, max;

	qu = (MyQueue *)malloc(sizeof(MyQueue));
	init_cycle_queue(qu);

	fp = fopen("C://Users//鲍骞月//Desktop//test.bmp", "r");
	if (!fp)
	{
		cout << "文件打开失败" << endl;
	}
	huf_tree = create_huffman_tree(fp, &leaf_num, &file_length);
	for (int i = 0; i < PIXELSIZE; i++)
	{
		printf("序号为：%d 像素值为：%d，权值为：%d 双亲结点为:%d:", i,huf_tree[i].data,huf_tree[i].weight,huf_tree[i].parent);
		printf("\n");
	}
	cout << "叶子结点数：" << leaf_num << endl;
	cout << "哈夫曼编码为:" << endl;
	map = get_huffman_code(huf_tree, leaf_num);
	res = fopen(res_file_name, "wb");
	//将文件游标移动到一个位置，目的是为了给一些编码的信息留出空间
	fseek(res, sizeof(WeightType) + sizeof(int) + 6 * sizeof(DataType), SEEK_SET);
	//计算最大最小编码长度，并将每个叶子和编码长度写入文件中
	get_max_min_code_length(res, huf_tree, map, leaf_num, &max, &min);
	//将所有编码转换成字节写入文件中，并计算字节数
	num = copy_huffman_code_to_file(res, map, leaf_num, qu, &end_length);
	rewind(res); //将文件游标移动到开头位置
	fseek(res, sizeof(WeightType) + sizeof(DataType), SEEK_SET);
	fwrite(&leaf_num, sizeof(int), 1, res); //写入叶子结点数
	fwrite(&max, sizeof(DataType), 1, res); //写入最大编码长度
	fwrite(&min, sizeof(DataType), 1, res); //写入最小编码长度
	fwrite(&num, sizeof(int), 1, res); //写入编码字节数
	fwrite(&end_length, sizeof(DataType), 1, res); //写入最后剩余的字符数，需要特殊处理
	fseek(res, leaf_num * 2 * sizeof(DataType) + num, SEEK_CUR);
	cout << "字节数" << num << endl;
	cout << "int" << sizeof(int) << endl; //4
	cout << "WeightType" << sizeof(WeightType) << endl; //4
	cout << "Datatype" << sizeof(DataType) << endl; //1
	
	fclose(fp);
	fclose(res);
	system("pause");
	getchar();
	return a.exec();
}


