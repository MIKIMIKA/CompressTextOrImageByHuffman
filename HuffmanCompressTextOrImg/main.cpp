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
	FILE *fp,*res;
	TreeNode *huf_tree;
	int leaf_num,end_length,num = 0;
	long file_length;
	char **map;
	char *res_file_name = "resultfile.barack";
	MyQueue *qu = NULL;

	qu = (MyQueue *)malloc(sizeof(MyQueue));
	init_cycle_queue(qu);

	fp = fopen("C://Users//22876//Desktop//测试.bmp", "r");
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
	res = fopen(res_file_name, "wb");
	num = copy_huffman_code_to_file(res, map, leaf_num, qu, &end_length);
	cout << "字节数" << num << endl;
	
	system("pause");
	getchar();
	return a.exec();
}


