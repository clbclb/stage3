/********************************************************************************
** Form generated from reading UI file 'Server.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName("Server");
        Server->resize(800, 600);
        textEdit = new QTextEdit(Server);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(150, 130, 201, 91));
        pushButton = new QPushButton(Server);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(390, 170, 80, 18));

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QWidget *Server)
    {
        Server->setWindowTitle(QCoreApplication::translate("Server", "Server", nullptr));
        pushButton->setText(QCoreApplication::translate("Server", "set your port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
