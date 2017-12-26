
#include "BaseHuffmanTree.h"
#include "Structure.h"


/*对哈夫曼树的各项操作*/


/*从已有的结点数组中选取出权值最小的结点而且其父亲结点为-1,将其结点序号用min返回*/
void select_min_tree_node(TreeNode *ht, int n, int *min)
{
	int i = 0, temp_min;
	WeightType min_weight;
	for (i = 0; i <= n; i++)
	{
		if (ht[i].parent == -1)
		{
			min_weight = ht[i].weight;
			temp_min = i;
			break;
		}
	}

	//将此时最小的结点找出来
	for (i++; i <= n; i++)
	{
		if (ht[i].parent == -1 && ht[i].weight < min_weight)
		{
			min_weight = ht[i].weight;
			temp_min = i;
		}
	}

	//并将该结点的地址返回 
	*min = temp_min;
}


/*对字符结点按照权值进行排序，然后统计出叶子结点
(叶子结点就是我们文件中出现的结点也就是我们要实际编码的结点)的个数返回*/
int sort_tree(TreeNode *ht)
{
	TreeNode temp;
	int i, j;
	int num = 0;
	//这里权值应从大到小排列，保证有权值的结点处在数组的前面
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

	//统计叶子结点个数
	for (i = 0; i < PIXELSIZE; i++)
	{
		if (ht[i].weight != 0)
			num++;
	}
	return num;
}



/*从文件读取字符创建哈夫曼树，要求文件内容为英文字符或数字*/
TreeNode *create_huffman_tree(FILE *fp, int *leaf_num, long *file_length)
{
	TreeNode *huf_tree = NULL;
	int i,total_num,min1,min2;
	DataType data;
	//开辟二叉树空间
	huf_tree = (TreeNode*) malloc( 2*PIXELSIZE * sizeof(TreeNode));
	if (!huf_tree)
		exit(1);
	//初始化字典中各单词结点
	for (i = 0; i < PIXELSIZE; i++)
	{
		//0-255为各字符，初始化到二叉树中
		huf_tree[i].data = (DataType)i;//将0~255整形值强转为char类型存到结点中
		//权值初始为0
		huf_tree[i].weight = 0;
	}
	//从文件中统计各字符的权值
	for (*file_length = 0; !feof(fp); ++(*file_length))
	{
		data = fgetc(fp); //具体像素
		huf_tree[data].weight++; //统计权值
	}

	//构建哈夫曼树并返回叶子节点个数
	*leaf_num = sort_tree(huf_tree);
	//总结点数为2*leaf-1
	total_num = *leaf_num * 2 - 1;
	//初始化二叉树中的每个结点
	for (i = total_num - 1; i >= 0; i--)
	{
		huf_tree[i].l_child = -1;
		huf_tree[i].parent = -1;
		huf_tree[i].r_child = -1;
	}
	//创建非叶子结点，构建二叉树
	//这里的每次循环的任务就是找出一棵新的最优子树，总数就是非叶子结点的个数
	for (i = *leaf_num; i < total_num; i++)
	{
		//从huf_tree[0]~huf_tree[i - 1]中找到两个parent为-1权值最小的结点
		//并将其序号用min1，min2返回
		select_min_tree_node(huf_tree, i - 1, &min1);
		huf_tree[min1].parent = i;//将选取出的最小结点双亲设置为i
		huf_tree[i].l_child = min1;
		select_min_tree_node(huf_tree, i - 1, &min2);
		huf_tree[min2].parent = i;//将另一个最小的结点双亲设置为i
		huf_tree[i].r_child = min2;
		//新结点的权值为min1，min2的权值之和
		huf_tree[i].weight = huf_tree[min1].weight + huf_tree[min2].weight;
	}
	//哈夫曼树构建完成
	return huf_tree;
}

