
#include "BaseHuffmanTree.h"
#include "Structure.h"


/*�Թ��������ĸ������*/


/*�����еĽ��������ѡȡ��Ȩֵ��С�Ľ������丸�׽��Ϊ-1,�����������min����*/
void select_min_tree_node(TreeNode *ht, int n, int *min)
{
	int i = 0, temp_min;
	WeightType min_weight;
	for (i = 0; i < n; i++)
	{
		if (ht[i].parent == -1)
		{
			min_weight = ht[i].weight;
			temp_min = i;
			break;
		}
	}

	//����ʱ��С�Ľ���ҳ���
	for (i++; i < n; i++)
	{
		if (ht[i].parent == -1 && ht[i].weight < min_weight)
		{
			min_weight = ht[i].weight;
			temp_min = i;
		}
	}

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
	//����ȨֵӦ�Ӵ�С���У���֤��Ȩֵ�Ľ�㴦�������ǰ��
	//������湹����Ҷ�ӽ��
	for (i = 0; i < PIXELSIZE; i++)
	{
		for (j = 0; j < PIXELSIZE - i - 1; j++)
		{
			if (ht[j].weight < ht[j + 1].weight)
			{
				temp = ht[j];
				ht[j] = ht[j + 1];
				ht[j + 1] = temp;
			}
		}
	}

	//ͳ��Ҷ�ӽ�����
	for (i = 0; i < PIXELSIZE; i++)
	{
		if (ht[i].weight != 0)
			num++;
	}
	return num;
}


/*�ɹ����������ɹ�����01�����,
����һ��map����ά���飬һά����ÿ��Ҷ�ӽ�㣬
��ά�д洢����ÿ��Ҷ�ӽ���Ӧ�Ĺ���������
*/
char **get_huffman_code(TreeNode *ht, int leaf_num)
{
	char **map, *temp;
	int i, left, right, t;
	//�ȿ��ٱ����ռ�
	//����ÿ�������ͷָ��
	map = (char **)malloc(leaf_num * sizeof(char*));
	//�������������ֻ��һ��Ҷ�ӽ������ 
	if (leaf_num == 1)
	{
		//�������Ҷ�ӽ�����Ŀռ�
		map[0] = (char*)malloc((leaf_num + 1) * sizeof(char));
		strcpy(map[0], "0"); //ֱ�Ӹ�Ϊ0
		return map;
	}
	//������һ������Ŀռ�
	//��Ϊÿ�����������Ҷ�ӽ������һ,leaf_num+1,Ҳ����Ȩֵ��С���Ǹ�Ҷ�ӽ��
	//�����ȡ�������ȿ������λ���������Ҷ�ӵı���ռ�
	temp = (char *)malloc((leaf_num + 1) * sizeof(char));
	//��Ҷ�ӽ�����ϻ�ȡ����(�������)
	temp[leaf_num] = '\0'; //���������ȡ����
	for (i = 0; i < leaf_num; i++) //��ȡ����Ҷ�ӽ��ı���
	{
		right = leaf_num; //��ָ���ʼʱָ���������һλ
		left = i; //��ָ���ʼʱָ��ǰ��һλ
		for (t = ht[i].parent; t != -1; t = ht[t].parent)
		{
			if (ht[t].l_child == left) //���������������Ϊ0
			{
				temp[--right] = '0';
			}
			else					   //����������Ϊ1
			{
				temp[--right] = '1';//
			}
			left = t; //������һ���������ʼ�±꣬��ʵ������ǰ�ƽ�һλ����Ϊÿ��ȡһ�Σ����볤�ȼ�һ
			//t = ht[t].parent; //ѭ������
		}
		//���ٱ���ռ�
		map[i] = (char *)malloc(sizeof(char) * (leaf_num - left));
		//�����븳ֵ
		strcpy(map[i], &temp[left]);
		//printf("%s\n", temp[left]);
	}
	free(temp);
	printf("����������������...\n");
	return map;
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
		huf_tree[i].data = (DataType)i;//��0~255����ֵǿתΪchar���ʹ浽�����
		//Ȩֵ��ʼΪ0
		huf_tree[i].weight = 0;
	}
	//���ļ���ͳ�Ƹ��ַ���Ȩֵ
	for (*file_length = 0; !feof(fp); ++(*file_length))
	{
		data = fgetc(fp); //��������
		huf_tree[data].weight++; //ͳ��Ȩֵ
	}

	//������������������Ҷ�ӽڵ����
	*leaf_num = sort_tree(huf_tree);
	//�ܽ����Ϊ2*leaf-1
	total_num = *leaf_num * 2 - 1;
	//����Ҷ�ӽ�����������ͷǷ����
	//���ֻ��һ��Ҷ�ӽ��
	if (*leaf_num == 1)
	{
		huf_tree[0].parent = 1;
	}
	else if (*leaf_num < 0)
	{
		return NULL;
	}
	//��ʼ���������е�ÿ�����
	for (i = total_num - 1; i >= 0; i--)
	{
		huf_tree[i].l_child = -1;
		huf_tree[i].parent = -1;
		huf_tree[i].r_child = -1;
	}
	//������Ҷ�ӽ�㣬����������
	//�����ÿ��ѭ������������ҳ�һ���µ������������������Ƿ�Ҷ�ӽ��ĸ���
	for (i = *leaf_num; i < total_num; i++)
	{
		//��huf_tree[0]~huf_tree[i - 1]���ҵ�����parentΪ-1Ȩֵ��С�Ľ��
		//�����������min1��min2����
		select_min_tree_node(huf_tree, i, &min1);
		huf_tree[min1].parent = i;//��ѡȡ������С���˫������Ϊi
		huf_tree[i].l_child = min1;
		select_min_tree_node(huf_tree, i, &min2);
		huf_tree[min2].parent = i;//����һ����С�Ľ��˫������Ϊi
		huf_tree[i].r_child = min2;
		//�½���ȨֵΪmin1��min2��Ȩֵ֮��
		huf_tree[i].weight = huf_tree[min1].weight + huf_tree[min2].weight;
	}
	//���������������
	return huf_tree;
}

