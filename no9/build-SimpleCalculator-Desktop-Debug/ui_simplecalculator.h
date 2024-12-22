/********************************************************************************
** Form generated from reading UI file 'simplecalculator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLECALCULATOR_H
#define UI_SIMPLECALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimpleCalculator
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEditDisplay;
    QPushButton *button0;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button8;
    QPushButton *button9;
    QPushButton *buttonClear;
    QPushButton *buttonEquals;
    QPushButton *buttonDivide;
    QPushButton *buttonMultiply;
    QPushButton *buttonSubtract;
    QPushButton *buttonAdd;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SimpleCalculator)
    {
        if (SimpleCalculator->objectName().isEmpty())
            SimpleCalculator->setObjectName(QString::fromUtf8("SimpleCalculator"));
        SimpleCalculator->resize(351, 469);
        centralwidget = new QWidget(SimpleCalculator);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEditDisplay = new QLineEdit(centralwidget);
        lineEditDisplay->setObjectName(QString::fromUtf8("lineEditDisplay"));
        lineEditDisplay->setGeometry(QRect(20, 30, 311, 81));
        QFont font;
        font.setPointSize(28);
        lineEditDisplay->setFont(font);
        button0 = new QPushButton(centralwidget);
        button0->setObjectName(QString::fromUtf8("button0"));
        button0->setGeometry(QRect(110, 360, 51, 51));
        button1 = new QPushButton(centralwidget);
        button1->setObjectName(QString::fromUtf8("button1"));
        button1->setGeometry(QRect(30, 290, 51, 51));
        button2 = new QPushButton(centralwidget);
        button2->setObjectName(QString::fromUtf8("button2"));
        button2->setGeometry(QRect(110, 290, 51, 51));
        button3 = new QPushButton(centralwidget);
        button3->setObjectName(QString::fromUtf8("button3"));
        button3->setGeometry(QRect(190, 290, 51, 51));
        button4 = new QPushButton(centralwidget);
        button4->setObjectName(QString::fromUtf8("button4"));
        button4->setGeometry(QRect(30, 220, 51, 51));
        button5 = new QPushButton(centralwidget);
        button5->setObjectName(QString::fromUtf8("button5"));
        button5->setGeometry(QRect(110, 220, 51, 51));
        button6 = new QPushButton(centralwidget);
        button6->setObjectName(QString::fromUtf8("button6"));
        button6->setGeometry(QRect(190, 220, 51, 51));
        button7 = new QPushButton(centralwidget);
        button7->setObjectName(QString::fromUtf8("button7"));
        button7->setGeometry(QRect(30, 150, 51, 51));
        button8 = new QPushButton(centralwidget);
        button8->setObjectName(QString::fromUtf8("button8"));
        button8->setGeometry(QRect(110, 150, 51, 51));
        button9 = new QPushButton(centralwidget);
        button9->setObjectName(QString::fromUtf8("button9"));
        button9->setGeometry(QRect(190, 150, 51, 51));
        buttonClear = new QPushButton(centralwidget);
        buttonClear->setObjectName(QString::fromUtf8("buttonClear"));
        buttonClear->setGeometry(QRect(30, 360, 51, 51));
        buttonEquals = new QPushButton(centralwidget);
        buttonEquals->setObjectName(QString::fromUtf8("buttonEquals"));
        buttonEquals->setGeometry(QRect(190, 360, 51, 51));
        buttonDivide = new QPushButton(centralwidget);
        buttonDivide->setObjectName(QString::fromUtf8("buttonDivide"));
        buttonDivide->setGeometry(QRect(270, 150, 51, 51));
        buttonMultiply = new QPushButton(centralwidget);
        buttonMultiply->setObjectName(QString::fromUtf8("buttonMultiply"));
        buttonMultiply->setGeometry(QRect(270, 220, 51, 51));
        buttonSubtract = new QPushButton(centralwidget);
        buttonSubtract->setObjectName(QString::fromUtf8("buttonSubtract"));
        buttonSubtract->setGeometry(QRect(270, 290, 51, 51));
        buttonAdd = new QPushButton(centralwidget);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setGeometry(QRect(270, 360, 51, 51));
        SimpleCalculator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SimpleCalculator);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 351, 20));
        SimpleCalculator->setMenuBar(menubar);
        statusbar = new QStatusBar(SimpleCalculator);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SimpleCalculator->setStatusBar(statusbar);

        retranslateUi(SimpleCalculator);

        QMetaObject::connectSlotsByName(SimpleCalculator);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleCalculator)
    {
        SimpleCalculator->setWindowTitle(QCoreApplication::translate("SimpleCalculator", "SimpleCalculator", nullptr));
        button0->setText(QCoreApplication::translate("SimpleCalculator", "0", nullptr));
        button1->setText(QCoreApplication::translate("SimpleCalculator", "1", nullptr));
        button2->setText(QCoreApplication::translate("SimpleCalculator", "2", nullptr));
        button3->setText(QCoreApplication::translate("SimpleCalculator", "3", nullptr));
        button4->setText(QCoreApplication::translate("SimpleCalculator", "4", nullptr));
        button5->setText(QCoreApplication::translate("SimpleCalculator", "5", nullptr));
        button6->setText(QCoreApplication::translate("SimpleCalculator", "6", nullptr));
        button7->setText(QCoreApplication::translate("SimpleCalculator", "7", nullptr));
        button8->setText(QCoreApplication::translate("SimpleCalculator", "8", nullptr));
        button9->setText(QCoreApplication::translate("SimpleCalculator", "9", nullptr));
        buttonClear->setText(QCoreApplication::translate("SimpleCalculator", "C", nullptr));
        buttonEquals->setText(QCoreApplication::translate("SimpleCalculator", "=", nullptr));
        buttonDivide->setText(QCoreApplication::translate("SimpleCalculator", "/", nullptr));
        buttonMultiply->setText(QCoreApplication::translate("SimpleCalculator", "*", nullptr));
        buttonSubtract->setText(QCoreApplication::translate("SimpleCalculator", "-", nullptr));
        buttonAdd->setText(QCoreApplication::translate("SimpleCalculator", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimpleCalculator: public Ui_SimpleCalculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLECALCULATOR_H
