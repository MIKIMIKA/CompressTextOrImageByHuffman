#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Structure.h"


/*�Թ��������ĸ������*/


/*���ļ���ȡ�ַ���������������Ҫ���ļ�����ΪӢ���ַ�������*/
TreeNode *create_huffman_tree(FILE *fp, int leaf_num, long file_length)
{
	TreeNode *huf_tree = NULL;
	int i,total_num;
	DataType data;
	//���ٶ������ռ�
	huf_tree = (TreeNode*) malloc(PIXELSIZE * sizeof(TreeNode));
	if (!huf_tree)
		exit(1);
	//��ʼ���ֵ��и����ʽ��
	for (i = 0; i < PIXELSIZE; i++)
	{
		//0-255Ϊ���ַ�����ʼ������������
		huf_tree[i].data = i;
		//Ȩֵ��ʼΪ0
		huf_tree[i].weight = 0;
	}
	//���ļ���ͳ�Ƹ��ַ���Ȩֵ
	for (file_length = 0; !feof(fp); ++file_length)
	{
		data = fgetc(fp); //�����ַ�
		huf_tree[data].weight++; //ͳ��Ȩֵ
	}

	//������������������Ҷ�ӽڵ����
	leaf_num = sort_tree(huf_tree);
	//�ܽ����Ϊ2*leaf-1
	total_num = 2 * leaf_num - 1;
	

}

/*���ַ���㰴��Ȩֵ��������Ȼ��ͳ�Ƴ�Ҷ�ӽ��
(Ҷ�ӽ����������ļ��г��ֵĽ��Ҳ��������Ҫʵ�ʱ���Ľ��)�ĸ�������*/
int sort_tree(TreeNode *ht)
{
	TreeNode temp;
	int i,j;
	int num = 0;
	//����Ȩֵ��С��������
	for (i = 0; i < MAXSIZE; i++)
	{
		for (j = 1; j < i; j++)
		{
			if (ht[j].weight > ht[j + 1].weight)
			{
				temp = ht[j];
				ht[j] = ht[j + 1];
				ht[j + 1] = temp;
			}
		}
	}

	//ͳ��Ҷ�ӽ�����
	for (i = 0; i < MAXSIZE; i++)
	{
		if (ht[i].weight != 0)
			num++; //ͳ��Ҷ�ӽ��
	}
	return num;
}