#include "Structure.h"
#include "BaseHuffmanTree.h"


/*
��ѹ��
*/
void un_compress()
{
	DataType max_len, min_len, end_len = 0,final = 0;
	WeightType src_len = 0, new_file_len = 0;
	FILE *src, *res;
	int i,j,leaf_num, code_num;
	char ch, a, *temp_code, *src_name, *res_name, **map, *leaf_data_list, *code_len_list, *code_buf;
	MyQueue *qu = NULL;

	src_name = "D://resultfile.bmp.huf";
	res_name = "D://upzip.bmp"; //��ѹ����ļ�
	
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
	code_buf = (char *)malloc(max_len * sizeof(char) + 2); //����������β��'\0'�ĳ���
	leaf_data_list = (char *)malloc(leaf_num * sizeof(DataType)); //���ٴ��Ҷ�ӵ�����
	code_len_list = (char *)malloc(leaf_num * sizeof(DataType)); //���ٴ��ÿ��Ҷ�Ӷ�Ӧ����ĳ�������
	qu = (MyQueue *)malloc(sizeof(MyQueue));
	
	if (!leaf_data_list || !code_len_list || !qu || !code_buf)
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
	if (!map)
		return;
	--code_num;
	for (i = j = 0; i < code_num; i++) 
	{
		ch = fgetc(src);
		//����ȡ�����ַ�ת�ɰ�λ0��1�ַ����
		cast_in_queue(qu, ch);
		while (qu->length > max_len) 
		{
			map[j] = temp_code = (char *)malloc(code_len_list[j] + 1);//���ٽ�������������
			for (ch = 0; ch < code_len_list[j]; ch++) //���Ӹ�Ҷ�ӵı���
			{
				out_queue(qu, &a); //������Ԫ�س��ӣ���ֵ��a
				*temp_code++ = a;
			}
			*temp_code = '\0';
			j++;
		}
	}
	//�������һ���ֽ�
	ch = fgetc(src);
	cast_in_queue(qu, ch);
	//��Ϊ8 - final�ǲ�0�ļ�λ��������Ҫ���⴦��
	final = 8 - final;
	while (qu->length > final)
	{
		map[j] = temp_code = (char *)malloc(code_len_list[j] + 1);
		for (ch = 0; ch < code_len_list[j]; ch++)
		{
			out_queue(qu, &a);
			*temp_code++ = a;
		}
		*temp_code = '\0';
		j++;
	}

	//���ö���
	init_cycle_queue(qu);
	--src_len;
	--min_len;
	//��ѹ
	while (new_file_len < src_len)
	{
		ch = fgetc(src); //�ӵڶ���д����ֽ���ѡȡ�ַ�
		cast_in_queue(qu, ch); //ת������ӱ���
		new_file_len++;
		
		//��min_len~max_len�ķ�Χ�ڽ��б����ƥ��ͻ�ȡ
		while (qu->length > max_len)
		{
			for (i = 0; i < min_len; i++)
			{
				out_queue(qu, &a);
				code_buf[i] = a;
			}
			for (; i < max_len; i++)
			{
				out_queue(qu, &a);
				code_buf[i] = a; //��һ���ȱȶԱ�����̵�
				code_buf[i + 1] = '\0';
				for (j = 0; j < leaf_num; j++)
				{
					if (code_len_list[j] == i + 1 && strcmp(map[j], code_buf) == 0) //Ѱ�ҵ���Ӧ�ı���
					{
						ch = leaf_data_list[j]; //�ӱ������ȡ��Ҷ������
						fputc(ch, res); //�����������Ҷ��д�뵽���ļ���
						break;
					}
				}
				//Ѱ����ϣ�����ѭ��
				if (j < leaf_num)
					break;
			}
		}
	}

	//�����Ǹ����������ֽ�
	ch = fgetc(src);
	cast_in_queue(qu, ch);
	end_len = 8 - end_len;
	while (qu->length > end_len)
	{
		for (i = 0; i < min_len; i++)
		{
			out_queue(qu, &a);
			code_buf[i] = a;
		}
		for (; i < max_len; i++)
		{
			out_queue(qu, &a);
			code_buf[i] = a; //��һ���ȱȶԱ�����̵�
			code_buf[i + 1] = '\0';
			for (j = 0; j < leaf_num; j++)
			{
				if (code_len_list[j] == i + 1 && strcmp(map[j], code_buf) == 0) //Ѱ�ҵ���Ӧ�ı���
				{
					ch = leaf_data_list[j]; //�ӱ������ȡ��Ҷ������
					fputc(ch, res); //�����������Ҷ��д�뵽���ļ���
					break;
				}
			}
			//Ѱ����ϣ�����ѭ��
			if (j < leaf_num)
				break;
		}
	}
	free(qu);
	free(code_buf);
	free(map);
	free(code_len_list);
	free(leaf_data_list);
	fclose(res);
	fclose(src);
	
}