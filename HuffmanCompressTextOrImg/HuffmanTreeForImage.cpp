#include "BaseHuffmanTree.h"
#include "Structure.h"


/*对哈夫曼树的各项操作*/

/*计算已生成的哈夫曼编码的最长和最短编码长度，方便压缩和解压缩时使用*/
void get_max_min_code_length(FILE *fp, TreeNode *ht, char **map, int leaf_num, DataType *max, DataType *min)
{
	DataType length;
	int i;
	*max = *min = strlen(map[0]); //将第一个编码的长度赋初值给max和min
	//将每个叶子结点和他们对应的编码长度写入文件中
	for (i = 0; i < leaf_num; i++)
	{
		length = strlen(map[i]);
		fwrite(&ht[i].data, sizeof(DataType), 1, fp); //将叶子结点的信息域写入文件中
		fwrite(&length, sizeof(DataType), 1, fp); //将每个叶子对应的编码长度写入文件中
		//寻找编码的最值
		if (length < *min)
		{
			*min = length;
		}
		if (length > *max)
		{
			*max = length;
		}
	}
}



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
	//并将该结点的下标返回 
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
	int i, current, right, father;
	//先开辟编码表空间
	//开辟每个编码的头指针空间
	map = (char **)malloc(leaf_num * sizeof(char*));
	//处理特殊情况，只有一个叶子结点的情况 
	if (leaf_num == 1)
	{
		//开辟这个叶子结点编码的空间
		*map = (char*)malloc((leaf_num)* sizeof(char));
		strcpy(map[0], "0"); //直接赋为0
		return map;
	}
	//开辟临时存放编码的空间
	//因为每个编码最长就是叶子结点数,leaf_num,也就是权值最小的那个叶子结点
	temp = (char *)malloc(leaf_num * sizeof(char));
	//从叶子结点向上获取编码(逆向编码)
	temp[leaf_num - 1] = '\0'; //从右向左存储编码
	for (i = 0; i < leaf_num; i++) //获取所有叶子结点的编码
	{
		right = leaf_num - 1; //右指针初始时指向数组最后一位
		current = i;//定义当前访问的叶子结点，任意一个叶子结点都可以
		father = ht[i].parent;
		while (father != -1) //根结点无双亲
		{
			if (ht[father].l_child == current) //如果是左子树设置为0
			{
				temp[--right] = '0'; //right索引向左推进一位存储
			}
			else					   //右子树设置为1
			{
				temp[--right] = '1';
			}
			current = father; //下次处理结点为当前结点的父亲
			father = ht[father].parent; //循环条件
		}
		//开辟一个编码的空间
		//将临时空间temp中的编码放进去
		//这里减去right正好是当前编码的长度，right是最终位置的下标
		map[i] = (char *)malloc(sizeof(char) * (leaf_num - right));
		//将编码赋值
		//strcpy的参数是两个字符串的起始地址
		strcpy(map[i], temp + right);//这里temp就是临时空间的首地址，加上right下标就是编码开始的位置
		printf("像素值为:%d,哈夫曼编码为:%s\n", ht[i].data, map[i]);

	}
	free(temp);//释放临时空间的长度
	printf("哈夫曼编码已生成...\n");
	return map;
}


/*从文件读取字符创建哈夫曼树，要求文件内容为英文字符或数字*/
TreeNode *create_huffman_tree(FILE *fp, int *leaf_num, WeightType *file_length)
{
	TreeNode *huf_tree = NULL;
	int i, total_num, min1, min2;
	DataType data;
	//开辟二叉树空间
	huf_tree = (TreeNode*)malloc(PIXELSIZE * sizeof(TreeNode));
	if (!huf_tree)
		exit(1);
	//初始化字典中各像素结点
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
	--(*file_length); //去掉文件结束后的长度

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

