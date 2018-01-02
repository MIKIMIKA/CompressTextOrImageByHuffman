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
		cout << "�ļ���ʧ��" << endl;
	}
	huf_tree = create_huffman_tree(fp, &leaf_num, &file_length);
	for (int i = 0; i < PIXELSIZE; i++)
	{
		printf("���Ϊ��%d ����ֵΪ��%d��ȨֵΪ��%d ˫�׽��Ϊ:%d:", i, huf_tree[i].data, huf_tree[i].weight, huf_tree[i].parent);
		printf("\n");
	}
	cout << "Ҷ�ӽ������" << leaf_num << endl;
	cout << "����������Ϊ:" << endl;
	map = get_huffman_code(huf_tree, leaf_num);
	//Ϊ�˷����ȡ��Ӧ���룬���½���һ���ַ������new_map
	new_map = (char **)malloc(PIXELSIZE * sizeof(char*)); 
	if (!new_map)
	{
		cout << "�ռ�δ����" << endl;
		return;
	}
	//��ʼ���±�
	for (i = 0; i < PIXELSIZE; i++)
		new_map[i] = NULL;
	//��Ҷ�ӽ���Ӧ�ı���д�뵽�±���
	for (i = 0; i < leaf_num; i++)
	{
		new_map[(int)huf_tree[i].data] = map[i];
	}
	res = fopen(res_file_name, "wb");
	//���ļ��α��ƶ���һ��λ�ã�Ŀ����Ϊ�˸�һЩ�������Ϣ�����ռ�
	fseek(res, sizeof(WeightType) + 2 * sizeof(int) + 4 * sizeof(DataType), SEEK_SET);
	//���������С���볤�ȣ�����ÿ��Ҷ�Ӻͱ��볤��д���ļ���
	get_max_min_code_length(res, huf_tree, map, leaf_num, &max, &min);
	free(huf_tree);
	//�����б���ת�����ֽ�д���ļ��У��������ֽ���
	num = copy_huffman_code_to_file(res, map, leaf_num, qu, &end_length);
	rewind(res); //���ļ��α��ƶ�����ͷλ��
	fseek(res, sizeof(WeightType) + sizeof(DataType), SEEK_SET);
	fwrite(&leaf_num, sizeof(int), 1, res); //д��Ҷ�ӽ����
	fwrite(&max, sizeof(DataType), 1, res); //д�������볤��
	fwrite(&min, sizeof(DataType), 1, res); //д����С���볤��
	fwrite(&num, sizeof(int), 1, res); //д������ֽ���
	fwrite(&end_length, sizeof(DataType), 1, res); //д�����ʣ����ַ�������Ҫ���⴦��
	fseek(res, leaf_num * 2 * sizeof(DataType) + num, SEEK_CUR); //���֮ǰд����ֽ�����ÿ��Ҷ�ӽ������ǵı��볤��
	rewind(fp); //��Դ�ļ����¶�λ����㣬׼��ѹ��
	//ѹ��
	while (file_char_num < file_length)
	{
		ch = fgetc(fp); //��ԭ�ļ��ж�ȡ�ַ�
		++file_char_num; 
		for (temp = new_map[ch]; *temp != '\0'; temp++) //���������
		{
			in_queue(qu, *temp);
		}
		while (qu->length > 8)
		{
			byte = get_byte(qu);
			fputc(byte, res); //���ϳɵ��ֽ�д���ļ�
			byte_length++; //ͳ���ֽ���
		}
	}

	//�������ʣ�µĺͲ���һ���ֽڵı���
	end_length = qu->length; //ʣ�µ�λ��
	m = 8 - end_length; //�����λ��λ��
	byte = get_byte(qu); 
	//ʣ�²����λ��λ�ö���'0'��ȫ
	for (i = 0; i < m; i++)
	{
		byte <<= 1;
	}
	fwrite(&byte, sizeof(DataType), 1, res);//�����һ���ֽ�д���ļ�
	byte_length++;
	rewind(res); //���ļ��α����¶�λ����ͷ����д�ļ���Ϣ
	fwrite(&byte_length, sizeof(WeightType), 1, res); //д��ѹ������ֽ���
	fwrite(&end_length, sizeof(DataType), 1, res); //д�����ʣ��ı���λ�����ڽ�ѹ��ʱ����Ҫ���⴦��
	//������ѹ������ļ�����
	byte_length = byte_length + 16 + num;
	cout << "ѹ�����..." << endl;
	//cout << "�ֽ���" << num << endl;
	//cout << "int" << sizeof(int) << endl; //4
	//cout << "WeightType" << sizeof(WeightType) << endl; //4
	//cout << "Datatype" << sizeof(DataType) << endl; //1
	//cout << "short" << sizeof(short) << endl; //2
	//����ѹ������
	if (byte_length >= file_length)
	{
		cout << "ѹ��ʧ��..." << endl;
	}
	else
	{
		cout << "ԭ�ļ���С: " << file_length << endl;
		cout << "ѹ���ļ���С: " << byte_length << endl;
		cout << "ѹ������Ϊ�� " << (double)((file_length - byte_length) / (double)file_length * 100.0) << '%' << endl;
	}

	free(qu);
	free(map);
	free(new_map);
	fclose(fp);
	fclose(res);
}