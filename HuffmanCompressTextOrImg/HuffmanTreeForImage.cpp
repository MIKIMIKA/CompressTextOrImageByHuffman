
#include "BaseHuffmanTree.h"
#include "Structure.h"


/*对哈夫曼树的各项操作*/


/*从已有的结点数组中选取出权值最小的结点而且其父亲结点为-1,将其结点序号用min返回*/
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

	//将此时最小的结点找出来
	for (i++; i < n; i++)
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
	//方便后面构建非叶子结点
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


/*由哈夫曼树生成哈夫曼01编码表,
返回一个map，二维数组，一维的是每个叶子结点，
二维中存储的是每个叶子结点对应的哈夫曼编码
*/
char **get_huffman_code(TreeNode *ht, int leaf_num)
{
	char **map, *temp;
	int i, left, right, t;
	//先开辟编码表空间
	//开辟每个编码的头指针
	map = (char **)malloc(leaf_num * sizeof(char*));
	//处理特殊情况，只有一个叶子结点的情况 
	if (leaf_num == 1)
	{
		//开辟这个叶子结点编码的空间
		map[0] = (char*)malloc((leaf_num + 1) * sizeof(char));
		strcpy(map[0], "0"); //直接赋为0
		return map;
	}
	//开辟下一个编码的空间
	//因为每个编码最长就是叶子结点数加一,leaf_num+1,也就是权值最小的那个叶子结点
	//逆向获取，所以先开辟这个位于最下面的叶子的编码空间
	temp = (char *)malloc((leaf_num + 1) * sizeof(char));
	//从叶子结点向上获取编码(逆向编码)
	temp[leaf_num] = '\0'; //从右向左获取编码
	for (i = 0; i < leaf_num; i++) //获取所有叶子结点的编码
	{
		right = leaf_num; //右指针初始时指向数组最后一位
		left = i; //左指针初始时指向当前第一位
		for (t = ht[i].parent; t != -1; t = ht[t].parent)
		{
			if (ht[t].l_child == left) //如果是左子树设置为0
			{
				temp[--right] = '0';
			}
			else					   //右子树设置为1
			{
				temp[--right] = '1';//
			}
			left = t; //设置下一次数组的起始下标，其实就是向前推进一位，因为每获取一次，编码长度减一
			//t = ht[t].parent; //循环条件
		}
		//开辟编码空间
		map[i] = (char *)malloc(sizeof(char) * (leaf_num - left));
		//将编码赋值
		strcpy(map[i], &temp[left]);
		//printf("%s\n", temp[left]);
	}
	free(temp);
	printf("哈夫曼编码已生成...\n");
	return map;
}


/*从文件读取字符创建哈夫曼树，要求文件内容为英文字符或数字*/
TreeNode *create_huffman_tree(FILE *fp, int *leaf_num, long *file_length)
{
	TreeNode *huf_tree = NULL;
	int i,total_num,min1,min2;
	DataType data;
	//开辟二叉树空间
	huf_tree = (TreeNode*) malloc(PIXELSIZE * sizeof(TreeNode));
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
	//处理叶子结点的特殊情况和非法情况
	//如果只有一个叶子结点
	if (*leaf_num == 1)
	{
		huf_tree[0].parent = 1;
	}
	else if (*leaf_num < 0)
	{
		return NULL;
	}
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
		select_min_tree_node(huf_tree, i, &min1);
		huf_tree[min1].parent = i;//将选取出的最小结点双亲设置为i
		huf_tree[i].l_child = min1;
		select_min_tree_node(huf_tree, i, &min2);
		huf_tree[min2].parent = i;//将另一个最小的结点双亲设置为i
		huf_tree[i].r_child = min2;
		//新结点的权值为min1，min2的权值之和
		huf_tree[i].weight = huf_tree[min1].weight + huf_tree[min2].weight;
	}
	//哈夫曼树构建完成
	return huf_tree;
}

