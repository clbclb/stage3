/********************************************************************************
** Form generated from reading UI file 'clock.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCK_H
#define UI_CLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clock
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdhour;
    QLCDNumber *lcdminute;
    QLCDNumber *lcdsecond;

    void setupUi(QWidget *clock)
    {
        if (clock->objectName().isEmpty())
            clock->setObjectName("clock");
        clock->resize(383, 143);
        clock->setMaximumSize(QSize(383, 143));
        layoutWidget = new QWidget(clock);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 381, 111));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lcdhour = new QLCDNumber(layoutWidget);
        lcdhour->setObjectName("lcdhour");

        horizontalLayout->addWidget(lcdhour);

        lcdminute = new QLCDNumber(layoutWidget);
        lcdminute->setObjectName("lcdminute");
        lcdminute->setMaximumSize(QSize(123, 109));

        horizontalLayout->addWidget(lcdminute);

        lcdsecond = new QLCDNumber(layoutWidget);
        lcdsecond->setObjectName("lcdsecond");

        horizontalLayout->addWidget(lcdsecond);


        retranslateUi(clock);

        QMetaObject::connectSlotsByName(clock);
    } // setupUi

    void retranslateUi(QWidget *clock)
    {
        clock->setWindowTitle(QCoreApplication::translate("clock", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class clock: public Ui_clock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCK_H
