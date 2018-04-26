/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionc;
    QWidget *centralWidget;
    QPushButton *motorSpin;
    QLCDNumber *selectIndex;
    QSpinBox *weightBox;
    QLabel *lblWeight;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lblSpins;
    QLabel *lblSpinCount;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblMenu;
    QLabel *menuItem;
    QComboBox *selectMenu;
    QMenuBar *menuBar;
    QMenu *menuAutoSpice_v_01;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(498, 402);
        actionc = new QAction(MainWindow);
        actionc->setObjectName(QStringLiteral("actionc"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        motorSpin = new QPushButton(centralWidget);
        motorSpin->setObjectName(QStringLiteral("motorSpin"));
        motorSpin->setGeometry(QRect(30, 0, 91, 31));
        selectIndex = new QLCDNumber(centralWidget);
        selectIndex->setObjectName(QStringLiteral("selectIndex"));
        selectIndex->setGeometry(QRect(320, 260, 131, 81));
        selectIndex->setSmallDecimalPoint(false);
        selectIndex->setProperty("value", QVariant(0));
        weightBox = new QSpinBox(centralWidget);
        weightBox->setObjectName(QStringLiteral("weightBox"));
        weightBox->setGeometry(QRect(350, 60, 48, 26));
        lblWeight = new QLabel(centralWidget);
        lblWeight->setObjectName(QStringLiteral("lblWeight"));
        lblWeight->setGeometry(QRect(340, 90, 67, 17));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 40, 161, 51));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblSpins = new QLabel(widget);
        lblSpins->setObjectName(QStringLiteral("lblSpins"));

        verticalLayout->addWidget(lblSpins);

        lblSpinCount = new QLabel(widget);
        lblSpinCount->setObjectName(QStringLiteral("lblSpinCount"));

        verticalLayout->addWidget(lblSpinCount);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(30, 210, 191, 91));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblMenu = new QLabel(widget1);
        lblMenu->setObjectName(QStringLiteral("lblMenu"));
        lblMenu->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lblMenu);

        menuItem = new QLabel(widget1);
        menuItem->setObjectName(QStringLiteral("menuItem"));
        menuItem->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(menuItem);

        selectMenu = new QComboBox(widget1);
        selectMenu->setObjectName(QStringLiteral("selectMenu"));

        verticalLayout_2->addWidget(selectMenu);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 498, 22));
        menuAutoSpice_v_01 = new QMenu(menuBar);
        menuAutoSpice_v_01->setObjectName(QStringLiteral("menuAutoSpice_v_01"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuAutoSpice_v_01->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionc->setText(QApplication::translate("MainWindow", "c", Q_NULLPTR));
        motorSpin->setText(QApplication::translate("MainWindow", "Spin Motors", Q_NULLPTR));
        lblWeight->setText(QString());
        lblSpins->setText(QString());
        lblSpinCount->setText(QString());
        lblMenu->setText(QApplication::translate("MainWindow", "Menu Selection", Q_NULLPTR));
        menuItem->setText(QString());
        selectMenu->clear();
        selectMenu->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Manual", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Custom", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Configure", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Recipes", Q_NULLPTR)
        );
        menuAutoSpice_v_01->setTitle(QApplication::translate("MainWindow", "AutoSpice v.01", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
