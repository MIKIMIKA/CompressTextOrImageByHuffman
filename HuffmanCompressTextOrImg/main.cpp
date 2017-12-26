#include "HuffmanCompressTextOrImg.h"
#include <QtWidgets/QApplication>
#include <iostream>
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
		fp = fopen("test.txt", "r+");
		if (!fp)
		{
			cout << "文件打开失败" << endl;
			return 0;
		}
		huf_tree = create_huffman_tree(fp, &leaf_num, &file_length);
		for (int i = 0; i < 4; i++)
		{
			cout << huf_tree[i].data << endl;
		}
		system("pause");
		return a.exec();
	}


