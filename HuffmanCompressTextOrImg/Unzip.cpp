#include "Structure.h"
#include "BaseHuffmanTree.h"


/*
��ѹ��
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
	res_name = "D:\\upzip.bmp"; //��ѹ����ļ�
	
	src = fopen(src_name, "rb");
	res = fopen(res_name, "wb");
	if (!src || !res)
	{
		printf("�ļ���ʧ��\n");
		return;
	}

	fread(&src_len, sizeof(WeightType), 1, src); //��ȡѹ���ļ��ֽ���
	fread(&end_len, sizeof(DataType), 1, src); //��ȡ���ʣ���λ������Ҫ���⴦��
	fread(&leaf_num, sizeof(int), 1, src); //��ȡҶ����
	fread(&max_len, sizeof(DataType), 1, src); //��ȡ���볤�����ֵ
	fread(&min_len, sizeof(DataType), 1, src); //��ȡ���볤����Сֵ

	//����ռ�
	leaf_data_list = (char *)malloc(leaf_num * sizeof(leaf_num)); //���ٴ��Ҷ�ӵ�����
	code_len_list = (char *)malloc(leaf_num * sizeof(leaf_num)); //���ٴ��ÿ��Ҷ�Ӷ�Ӧ����ĳ�������
	qu = (MyQueue *)malloc(sizeof(MyQueue));
	
	if (!leaf_data_list || !code_len_list || !qu)
	{
		printf("���ٿռ�ʧ��...");
		return;
	}
	
	fread(&code_num, sizeof(int), 1, src); //��ȡѹ���������ֽ���
	fread(&final, sizeof(DataType), 1, src); //��ȡʣ��λ��
	
	//��ȡҶ�ӺͶ�Ӧ���볤��
	for (i = 0; i < leaf_num; i++)
	{
		fread(&leaf_data_list[i], sizeof(DataType), 1, src);
		fread(&code_len_list[i], sizeof(DataType), 1, src);
	}
	init_cycle_queue(qu);
	map = (char **)malloc(sizeof(char *) * leaf_num); //�ع������
	for (i = j = 0; i < code_num - 1; i++) 
	{
		ch = fgetc(src);
		//����ȡ�����ַ�ת�ɰ�λ0��1�ַ����
		cast_in_queue(qu, ch);
	}
}