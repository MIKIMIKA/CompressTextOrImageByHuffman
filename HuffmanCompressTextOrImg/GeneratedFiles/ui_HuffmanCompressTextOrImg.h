/********************************************************************************
** Form generated from reading UI file 'HuffmanCompressTextOrImg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUFFMANCOMPRESSTEXTORIMG_H
#define UI_HUFFMANCOMPRESSTEXTORIMG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HuffmanCompressTextOrImgClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HuffmanCompressTextOrImgClass)
    {
        if (HuffmanCompressTextOrImgClass->objectName().isEmpty())
            HuffmanCompressTextOrImgClass->setObjectName(QStringLiteral("HuffmanCompressTextOrImgClass"));
        HuffmanCompressTextOrImgClass->resize(600, 400);
        centralWidget = new QWidget(HuffmanCompressTextOrImgClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 80, 411, 131));
        HuffmanCompressTextOrImgClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HuffmanCompressTextOrImgClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        HuffmanCompressTextOrImgClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HuffmanCompressTextOrImgClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HuffmanCompressTextOrImgClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HuffmanCompressTextOrImgClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HuffmanCompressTextOrImgClass->setStatusBar(statusBar);

        retranslateUi(HuffmanCompressTextOrImgClass);

        QMetaObject::connectSlotsByName(HuffmanCompressTextOrImgClass);
    } // setupUi

    void retranslateUi(QMainWindow *HuffmanCompressTextOrImgClass)
    {
        HuffmanCompressTextOrImgClass->setWindowTitle(QApplication::translate("HuffmanCompressTextOrImgClass", "HuffmanCompressTextOrImg", Q_NULLPTR));
        label->setText(QApplication::translate("HuffmanCompressTextOrImgClass", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HuffmanCompressTextOrImgClass: public Ui_HuffmanCompressTextOrImgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUFFMANCOMPRESSTEXTORIMG_H
