#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HuffmanCompressTextOrImg.h"

class HuffmanCompressTextOrImg : public QMainWindow
{
	Q_OBJECT

public:
	HuffmanCompressTextOrImg(QWidget *parent = Q_NULLPTR);

private:
	Ui::HuffmanCompressTextOrImgClass ui;
};
