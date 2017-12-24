#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Structure.h"


/*对哈夫曼树的各项操作*/


/*从文件读取字符创建哈夫曼树，要求文件内容为英文字符或数字*/
TreeNode *create_huffman_tree(FILE *fp, int leaf_num, long file_length)
{
	TreeNode *huf_tree = NULL;
	int i,total_num;
	DataType data;
	//开辟二叉树空间
	huf_tree = (TreeNode*) malloc(PIXELSIZE * sizeof(TreeNode));
	if (!huf_tree)
		exit(1);
	//初始化字典中各单词结点
	for (i = 0; i < PIXELSIZE; i++)
	{
		//0-255为各字符，初始化到二叉树中
		huf_tree[i].data = i;
		//权值初始为0
		huf_tree[i].weight = 0;
	}
	//从文件中统计各字符的权值
	for (file_length = 0; !feof(fp); ++file_length)
	{
		data = fgetc(fp); //具体字符
		huf_tree[data].weight++; //统计权值
	}

	//构建哈夫曼树并返回叶子节点个数
	leaf_num = sort_tree(huf_tree);
	//总结点数为2*leaf-1
	total_num = 2 * leaf_num - 1;
	

}

/*对字符结点按照权值进行排序，然后统计出叶子结点
(叶子结点就是我们文件中出现的结点也就是我们要实际编码的结点)的个数返回*/
int sort_tree(TreeNode *ht)
{
	TreeNode temp;
	int i,j;
	int num = 0;
	//按照权值从小到大排序
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

	//统计叶子结点个数
	for (i = 0; i < MAXSIZE; i++)
	{
		if (ht[i].weight != 0)
			num++; //统计叶子结点
	}
	return num;
}