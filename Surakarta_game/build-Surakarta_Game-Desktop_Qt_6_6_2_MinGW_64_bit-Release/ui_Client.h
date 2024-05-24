/********************************************************************************
** Form generated from reading UI file 'Client.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEdit_2;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName("Client");
        Client->resize(858, 559);
        textEdit = new QTextEdit(Client);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(80, 140, 261, 51));
        pushButton = new QPushButton(Client);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(380, 220, 80, 18));
        label = new QLabel(Client);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 120, 151, 20));
        label_2 = new QLabel(Client);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 240, 171, 20));
        textEdit_2 = new QTextEdit(Client);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(80, 260, 271, 51));

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
        pushButton->setText(QCoreApplication::translate("Client", "ok", nullptr));
        label->setText(QCoreApplication::translate("Client", "reset your ip", nullptr));
        label_2->setText(QCoreApplication::translate("Client", "reset your port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
