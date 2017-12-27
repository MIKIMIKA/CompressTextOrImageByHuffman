#include "HuffmanCompressTextOrImg.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <stdio.h>
#include "Structure.h"
#include "BaseHuffmanTree.h"

using namespace std;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HuffmanCompressTextOrImg w;
	w.show();
	FILE *fp;
	TreeNode *huf_tree;
	int leaf_num;
	long file_length;
	char **map;


	fp = fopen("C://Users//22876//Desktop//test.bmp", "r");
	if (!fp)
	{
		cout << "文件打开失败" << endl;
	}
	huf_tree = create_huffman_tree(fp, &leaf_num, &file_length);
	for (int i = 0; i < PIXELSIZE; i++)
	{
		printf("序号为：%d 像素值为：%d，权值为：%d 双亲结点为:%d:", i,huf_tree[i].data,huf_tree[i].weight,huf_tree[i].parent);
		printf("\n");
	}
	cout << "叶子结点数：" << leaf_num << endl;
	cout << "哈夫曼编码为:" << endl;
	map = get_huffman_code(huf_tree, leaf_num);

	
	system("pause");
	getchar();
	return a.exec();
}


