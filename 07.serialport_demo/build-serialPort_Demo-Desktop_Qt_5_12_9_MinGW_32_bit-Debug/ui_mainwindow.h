/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *cbb;
    QPushButton *btn_serialPort;
    QLineEdit *edit_BmsId;
    QLabel *label;
    QDoubleSpinBox *dsb_Vol;
    QDoubleSpinBox *dsb_Cur;
    QSpinBox *sp_Soc;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        cbb = new QComboBox(centralwidget);
        cbb->setObjectName(QString::fromUtf8("cbb"));
        cbb->setGeometry(QRect(20, 10, 131, 22));
        btn_serialPort = new QPushButton(centralwidget);
        btn_serialPort->setObjectName(QString::fromUtf8("btn_serialPort"));
        btn_serialPort->setGeometry(QRect(180, 10, 75, 23));
        edit_BmsId = new QLineEdit(centralwidget);
        edit_BmsId->setObjectName(QString::fromUtf8("edit_BmsId"));
        edit_BmsId->setGeometry(QRect(480, 10, 261, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(420, 10, 41, 21));
        dsb_Vol = new QDoubleSpinBox(centralwidget);
        dsb_Vol->setObjectName(QString::fromUtf8("dsb_Vol"));
        dsb_Vol->setGeometry(QRect(480, 60, 121, 21));
        dsb_Cur = new QDoubleSpinBox(centralwidget);
        dsb_Cur->setObjectName(QString::fromUtf8("dsb_Cur"));
        dsb_Cur->setGeometry(QRect(480, 110, 121, 21));
        sp_Soc = new QSpinBox(centralwidget);
        sp_Soc->setObjectName(QString::fromUtf8("sp_Soc"));
        sp_Soc->setGeometry(QRect(480, 170, 121, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_serialPort->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        label->setText(QApplication::translate("MainWindow", "BMS ID:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
