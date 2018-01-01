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

	fp = fopen("C://Users//�����//Desktop//test.bmp", "r");
	if (!fp)
	{
		cout << "�ļ���ʧ��" << endl;
	}
	huf_tree = create_huffman_tree(fp, &leaf_num, &file_length);
	for (int i = 0; i < PIXELSIZE; i++)
	{
		printf("���Ϊ��%d ����ֵΪ��%d��ȨֵΪ��%d ˫�׽��Ϊ:%d:", i,huf_tree[i].data,huf_tree[i].weight,huf_tree[i].parent);
		printf("\n");
	}
	cout << "Ҷ�ӽ������" << leaf_num << endl;
	cout << "����������Ϊ:" << endl;
	map = get_huffman_code(huf_tree, leaf_num);
	res = fopen(res_file_name, "wb");
	//���ļ��α��ƶ���һ��λ�ã�Ŀ����Ϊ�˸�һЩ�������Ϣ�����ռ�
	fseek(res, sizeof(WeightType) + sizeof(int) + 6 * sizeof(DataType), SEEK_SET);
	//���������С���볤�ȣ�����ÿ��Ҷ�Ӻͱ��볤��д���ļ���
	get_max_min_code_length(res, huf_tree, map, leaf_num, &max, &min);
	//�����б���ת�����ֽ�д���ļ��У��������ֽ���
	num = copy_huffman_code_to_file(res, map, leaf_num, qu, &end_length);
	rewind(res); //���ļ��α��ƶ�����ͷλ��
	fseek(res, sizeof(WeightType) + sizeof(DataType), SEEK_SET);
	fwrite(&leaf_num, sizeof(int), 1, res); //д��Ҷ�ӽ����
	fwrite(&max, sizeof(DataType), 1, res); //д�������볤��
	fwrite(&min, sizeof(DataType), 1, res); //д����С���볤��
	fwrite(&num, sizeof(int), 1, res); //д������ֽ���
	fwrite(&end_length, sizeof(DataType), 1, res); //д�����ʣ����ַ�������Ҫ���⴦��
	fseek(res, leaf_num * 2 * sizeof(DataType) + num, SEEK_CUR);
	cout << "�ֽ���" << num << endl;
	cout << "int" << sizeof(int) << endl; //4
	cout << "WeightType" << sizeof(WeightType) << endl; //4
	cout << "Datatype" << sizeof(DataType) << endl; //1
	
	fclose(fp);
	fclose(res);
	system("pause");
	getchar();
	return a.exec();
}


