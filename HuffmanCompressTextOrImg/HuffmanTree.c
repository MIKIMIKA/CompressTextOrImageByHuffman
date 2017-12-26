
#include "BaseHuffmanTree.h"
#include "Structure.h"


/*�Թ��������ĸ������*/


/*�����еĽ��������ѡȡ��Ȩֵ��С�Ľ������丸�׽��Ϊ0,�����������min����*/
void select_min_tree_node(TreeNode *ht, int n, int *min)
{
	int i = 0, temp_min;
	WeightType min_weight;
	//����һ��ȨֵΪ0�Ľ�㱣��������Ȼ��������Ƚϣ���ֹ�ظ�ѡȡ
	while (ht[i].parent != 0)
		i++;
	min_weight = ht[i].weight;
	temp_min = i;

	//����ʱ��С�Ľ���ҳ���
	for (; i < n; i++)
	{
		if (ht[i].parent == 0 && ht[i].weight < min_weight)
		{
			min_weight = ht[i].weight;
			temp_min = i;
		}
	}

	//��ѡȡ�����Ľ���˫������Ϊ1����ֹ֮����ظ�ѡȡ
	ht[temp_min].parent = 1;
	//�����ý��ĵ�ַ���� 
	*min = temp_min;
}


/*���ַ���㰴��Ȩֵ��������Ȼ��ͳ�Ƴ�Ҷ�ӽ��
(Ҷ�ӽ����������ļ��г��ֵĽ��Ҳ��������Ҫʵ�ʱ���Ľ��)�ĸ�������*/
int sort_tree(TreeNode *ht)
{
	TreeNode temp;
	int i, j;
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



/*���ļ���ȡ�ַ���������������Ҫ���ļ�����ΪӢ���ַ�������*/
TreeNode *create_huffman_tree(FILE *fp, int *leaf_num, long *file_length)
{
	TreeNode *huf_tree = NULL;
	int i,total_num,min1,min2;
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
	for (*file_length = 0; !feof(fp); ++ *file_length)
	{
		data = fgetc(fp); //�����ַ�
		huf_tree[data].weight++; //ͳ��Ȩֵ
	}

	//������������������Ҷ�ӽڵ����
	*leaf_num = sort_tree(huf_tree);
	//�ܽ����Ϊ2*leaf-1
	total_num = *leaf_num * 2 - 1;
	//��ʼ��ÿ��Ҷ�ӽ�㹹�ɵĶ�����
	for (i = 0; i < *leaf_num; i++)
	{
		huf_tree[i].l_child = -1;
		huf_tree[i].parent = -1;
		huf_tree[i].r_child = -1;
	}
	//������Ҷ�ӽ�㣬����������
	for (i = *leaf_num; i < total_num; i++)//�ӷ�Ҷ�ӽ�㿪ʼѭ��
	{
		//�����еĽ����ѡȡ����Ȩֵ��С�Ķ���parentΪ0�Ľ��
		//�����������min1��min2����
		select_min_tree_node(huf_tree, i - 1, &min1);
		huf_tree[min1].parent = i;//��ѡȡ������С���˫������Ϊi
		huf_tree[i].l_child = min1;
		select_min_tree_node(huf_tree, i - 1, &min2);
		huf_tree[min2].parent = i;//����һ����С�Ľ��˫������Ϊi
		huf_tree[i].r_child = min2;
		//�½���ȨֵΪmin1��min2��Ȩֵ֮��
		huf_tree[i].weight = huf_tree[min1].weight + huf_tree[min2].weight;
	}
	//���������������
	return huf_tree;
}

