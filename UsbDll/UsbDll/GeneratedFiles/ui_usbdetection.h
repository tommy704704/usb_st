/********************************************************************************
** Form generated from reading UI file 'usbdetection.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USBDETECTION_H
#define UI_USBDETECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_usbDetectionClass
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textBrowser;

    void setupUi(QWidget *usbDetectionClass)
    {
        if (usbDetectionClass->objectName().isEmpty())
            usbDetectionClass->setObjectName(QStringLiteral("usbDetectionClass"));
        usbDetectionClass->resize(600, 400);
        gridLayout = new QGridLayout(usbDetectionClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textBrowser = new QTextEdit(usbDetectionClass);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);


        retranslateUi(usbDetectionClass);

        QMetaObject::connectSlotsByName(usbDetectionClass);
    } // setupUi

    void retranslateUi(QWidget *usbDetectionClass)
    {
        usbDetectionClass->setWindowTitle(QApplication::translate("usbDetectionClass", "usbDetection", 0));
    } // retranslateUi

};

namespace Ui {
    class usbDetectionClass: public Ui_usbDetectionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBDETECTION_H
