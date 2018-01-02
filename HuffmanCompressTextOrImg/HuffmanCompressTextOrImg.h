#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qdialog.h>
#include "ui_HuffmanCompressTextOrImg.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class HuffmanCompressTextOrImg : public QDialog
{
	Q_OBJECT

public:
	HuffmanCompressTextOrImg(QWidget *parent = Q_NULLPTR);
	~HuffmanCompressTextOrImg();

signals:
	void findNext(const QString &str, Qt::CaseSensitivity cs);
	void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
	void findClicked();
	void enableFindButton(const QString &text);

private:
	QLabel *label;
	QLineEdit *lineEdit;
	QCheckBox *caseCheckBox;
	QCheckBox *backwardCheckBox;
	QPushButton *findButton;
	QPushButton *closeButton;
};
