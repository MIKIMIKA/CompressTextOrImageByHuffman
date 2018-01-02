#include "HuffmanCompressTextOrImg.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <stdio.h>
#include "Structure.h"
#include "BaseHuffmanTree.h"




int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HuffmanCompressTextOrImg *dialog = new HuffmanCompressTextOrImg;
	dialog->show();
	//compress();
	//un_compress();
	return a.exec();
}


