/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLCDNumber *lcdhour;
    QLCDNumber *lcdminute;
    QLCDNumber *lcdsecond;
    QPushButton *startTime;
    QPushButton *endTime;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        lcdhour = new QLCDNumber(centralWidget);
        lcdhour->setObjectName("lcdhour");
        lcdhour->setGeometry(QRect(90, 200, 161, 151));
        lcdhour->setProperty("value", QVariant(0.000000000000000));
        lcdminute = new QLCDNumber(centralWidget);
        lcdminute->setObjectName("lcdminute");
        lcdminute->setGeometry(QRect(310, 200, 161, 151));
        lcdsecond = new QLCDNumber(centralWidget);
        lcdsecond->setObjectName("lcdsecond");
        lcdsecond->setGeometry(QRect(520, 200, 161, 151));
        startTime = new QPushButton(centralWidget);
        startTime->setObjectName("startTime");
        startTime->setGeometry(QRect(0, 497, 141, 41));
        endTime = new QPushButton(centralWidget);
        endTime->setObjectName("endTime");
        endTime->setGeometry(QRect(672, 497, 121, 41));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 0, 101, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startTime->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        endTime->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\235\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
