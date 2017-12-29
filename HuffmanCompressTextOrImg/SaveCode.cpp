#include "BaseHuffmanTree.h"
#include "Structure.h"
/*
�����Ƕ���ѹ������Ĵ洢����
*/


/*��ʼ��ѭ������*/
void init_cycle_queue(MyQueue *qu)
{
	if (!qu)
	{
		return;
	}
	else
	{	
		//���qu��Ϊ�ս��г�ʼ��
		qu->tag = 0;
		qu->front = 0;
		qu->rear = 0;
		qu->length = 0;
	}
	
}

/*
��Ӳ���
��0��1�ַ�������Ӳ���
*/
void in_queue(MyQueue *qu, char ch)
{
	if (qu->front == qu->rear && qu->tag == 1)
	{
		return;
	}
	qu->info[qu->rear] = ch;
	qu->rear = (qu->rear + 1) % MAXSIZE;
	qu->length++;
	qu->tag = 1;
}

/*
���Ӳ���
ÿ�ε���һ��0��1
*/
int out_queue(MyQueue *qu,char *ch)
{
	if (qu->tag == 0)
	{
		return NULL;
	}
	*ch = qu->info[qu->front];
	qu->length--;
	qu->front = (qu->front + 1) % MAXSIZE;
	if (qu->front == qu->rear)
		qu->tag = 0;
	return 1;
}

/*�Ӷ����г��Ӱ˸����룬����������װ��һ���ֽڳ����ַ�*/
DataType get_byte(MyQueue *queue)
{
	DataType byte = 0;
	int i;
	char ch;
	printf("%c", byte);
	for (i = 0; i < 8; i++) //���Ӱ˸�����
	{
		if (out_queue(queue,&ch) != 0)
		{
			if (ch == '0')
			{
				byte = byte << 1; //�������Ϊ0��ֱ������һλ����
			}
			else
			{
				byte = (byte << 1) | 1; //�������Ϊ1������һλ�����1������ǰλ���1
			}
		}
		else
		{
			break;
		}
	}
	return byte;
}


/*
�����ɵı��뱣�浽�ļ���,�����ش�ŵ��ֽڸ���
Ϊ�˴ﵽѹ����Ŀ�ģ����ｫÿ�˸�����ת����һ���ֽ�
�洢���ļ���
*/
int copy_huffman_code_to_file(FILE *fp, char **map, int leaf_num, MyQueue *queue, int *length)
{
	char *t;
	DataType byte;
	int i, j, num = 0; //���Ҫ���ص��ֽڸ���
	for (i = 0; i < leaf_num; i++) //��n��Ҷ�ӽ��ı���д���ļ���
	{
		for (t = map[i]; *t != '\0'; t++) //��ÿ��Ҷ�ӽ��ı��붼���
		{
			in_queue(queue, *t);
		}
		//������б������
		while (queue->length > 8) //ÿ��λ���һ���ֽڣ�����������ݶ���Ԫ�س��ȿ���ѭ��
		{
			byte = get_byte(queue);//���Ӱ�λ����	
			fputc(byte, fp);//����Ϻõ�һ���ַ�д���ļ���
			num++; //ͳ��������Ϻõ��ֽ���
		}

	}
	//���������������������ʣ����ַ�������8ʱ������Ҫ��ʣ����ַ����е�������װ
	*length = queue->length;
	i = 8 - *length;//ʣ��Ĳ����λ�ĸ���
	byte = get_byte(queue);//�Ƚ��⼸λ���,Ϊ�˺ϳ�һ���ֽڣ���ʣ�µļ�λ���в���
	for (j = 0; j < i; j++)
	{
		byte = byte >> 1;
	}
	fputc(byte, fp);//�����һ���ֽ�д���ļ���
	num++;
	init_cycle_queue(queue);
	fclose(fp);
	return num;
}