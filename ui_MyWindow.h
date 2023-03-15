/********************************************************************************
** Form generated from reading UI file 'MyWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMyWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMyWindow *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QString::fromUtf8("MyWindow"));
        MyWindow->resize(1207, 671);
        centralwidget = new QWidget(MyWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setCursor(QCursor(Qt::CrossCursor));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(15, 11, 1151, 561));
        MyWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1207, 25));
        MyWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MyWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MyWindow->setStatusBar(statusbar);

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QMyWindow *MyWindow)
    {
        MyWindow->setWindowTitle(QCoreApplication::translate("MyWindow", "MyWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MyWindow_H
