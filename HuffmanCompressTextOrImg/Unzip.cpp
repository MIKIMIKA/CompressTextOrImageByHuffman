#include "Structure.h"
#include "BaseHuffmanTree.h"


/*
解压缩
*/
void un_compress()
{
	DataType max_len, min_len, end_len = 0,final = 0;
	WeightType src_len = 0;
	FILE *src, *res;
	int i,j,leaf_num, code_num;
	char ch,*src_name, *res_name, **map, *leaf_data_list, *code_len_list;
	MyQueue *qu = NULL;

	src_name = "resultfile.barack";
	res_name = "D:\\upzip.bmp"; //解压后的文件
	
	src = fopen(src_name, "rb");
	res = fopen(res_name, "wb");
	if (!src || !res)
	{
		printf("文件打开失败\n");
		return;
	}

	fread(&src_len, sizeof(WeightType), 1, src); //读取压缩文件字节数
	fread(&end_len, sizeof(DataType), 1, src); //读取最后剩余的位数，需要特殊处理
	fread(&leaf_num, sizeof(int), 1, src); //读取叶子数
	fread(&max_len, sizeof(DataType), 1, src); //读取编码长度最大值
	fread(&min_len, sizeof(DataType), 1, src); //读取编码长度最小值

	//申请空间
	leaf_data_list = (char *)malloc(leaf_num * sizeof(leaf_num)); //开辟存放叶子的数组
	code_len_list = (char *)malloc(leaf_num * sizeof(leaf_num)); //开辟存放每个叶子对应编码的长度数组
	qu = (MyQueue *)malloc(sizeof(MyQueue));
	
	if (!leaf_data_list || !code_len_list || !qu)
	{
		printf("开辟空间失败...");
		return;
	}
	
	fread(&code_num, sizeof(int), 1, src); //读取压缩编码后的字节数
	fread(&final, sizeof(DataType), 1, src); //读取剩余位数
	
	//读取叶子和对应编码长度
	for (i = 0; i < leaf_num; i++)
	{
		fread(&leaf_data_list[i], sizeof(DataType), 1, src);
		fread(&code_len_list[i], sizeof(DataType), 1, src);
	}
	init_cycle_queue(qu);
	map = (char **)malloc(sizeof(char *) * leaf_num); //重构编码表
	for (i = j = 0; i < code_num - 1; i++) 
	{
		ch = fgetc(src);
		//将读取到的字符转成八位0，1字符入队
		cast_in_queue(qu, ch);
	}
}