/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <drawlabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    DrawLabel *drawLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *fillPushButton;
    QPushButton *clearPushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1550, 900);
        QFont font;
        font.setPointSize(14);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        drawLabel = new DrawLabel(centralWidget);
        drawLabel->setObjectName(QString::fromUtf8("drawLabel"));
        drawLabel->setGeometry(QRect(310, 10, 1201, 881));
        drawLabel->setMaximumSize(QSize(1201, 16777215));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 351, 291, 541));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        fillPushButton = new QPushButton(layoutWidget);
        fillPushButton->setObjectName(QString::fromUtf8("fillPushButton"));

        verticalLayout->addWidget(fillPushButton);

        clearPushButton = new QPushButton(layoutWidget);
        clearPushButton->setObjectName(QString::fromUtf8("clearPushButton"));

        verticalLayout->addWidget(clearPushButton);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        drawLabel->setText(QString());
        fillPushButton->setText(QCoreApplication::translate("MainWindow", "\320\267\320\260\320\272\321\200\320\260\321\201\320\270\321\202\321\214", nullptr));
        clearPushButton->setText(QCoreApplication::translate("MainWindow", "\320\276\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
