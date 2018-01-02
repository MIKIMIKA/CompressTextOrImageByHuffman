#include "HuffmanCompressTextOrImg.h"
#include <QtWidgets>


HuffmanCompressTextOrImg::HuffmanCompressTextOrImg(QWidget *parent)
	: QDialog(parent)
{
	//新建控件
	label = new QLabel(tr("Find &what:"));
	lineEdit = new QLineEdit;
	label->setBuddy(lineEdit);

	caseCheckBox = new QCheckBox(tr("Match &case"));
	backwardCheckBox = new QCheckBox(tr("Search &backford"));

	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);
	findButton->setEnabled(false);

	closeButton = new QPushButton(tr("Close"));

	//信号槽创建
	connect(lineEdit, SIGNAL(textChange(const QString&)), this, SLOT(enableFindButton(const QString&)));
	connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addWidget(caseCheckBox);
	leftLayout->addWidget(backwardCheckBox);

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(findButton);
	rightLayout->addWidget(closeButton);
	rightLayout->addStretch();

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);

	setWindowTitle(tr("Find"));

}
HuffmanCompressTextOrImg::~HuffmanCompressTextOrImg()
{

}

void HuffmanCompressTextOrImg::findClicked()
{
	QString text = lineEdit->text();
	Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseInsensitive : Qt::CaseSensitive;
	if (backwardCheckBox->isChecked()) {
		emit findPrevious(text, cs);
	}
	else {
		emit findNext(text, cs);
	}
}

void HuffmanCompressTextOrImg::enableFindButton(const QString &text)
{
	findButton->setEnabled(!text.isEmpty());
}
