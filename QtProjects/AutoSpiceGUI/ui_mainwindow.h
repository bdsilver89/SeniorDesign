/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *doubleSpinBox;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QWidget *page_2;
    QLineEdit *lineEdit;
    QWidget *page_3;
    QWidget *page_4;
    QPushButton *manualButton;
    QPushButton *menuButton;
    QPushButton *configButton;
    QMenuBar *menuBar;
    QMenu *menuAutoSpice_v_01;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1080);
        MainWindow->setMinimumSize(QSize(1920, 1080));
        MainWindow->setMaximumSize(QSize(1920, 1080));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 60, 1341, 751));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(410, 180, 171, 221));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(layoutWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(layoutWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout->addWidget(checkBox_3);

        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(80, 180, 321, 221));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        verticalLayout_2->addWidget(doubleSpinBox);

        comboBox = new QComboBox(layoutWidget1);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(100, 90, 531, 31));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        stackedWidget->addWidget(page_4);
        manualButton = new QPushButton(centralWidget);
        manualButton->setObjectName(QStringLiteral("manualButton"));
        manualButton->setGeometry(QRect(110, 30, 89, 25));
        menuButton = new QPushButton(centralWidget);
        menuButton->setObjectName(QStringLiteral("menuButton"));
        menuButton->setGeometry(QRect(400, 30, 89, 25));
        configButton = new QPushButton(centralWidget);
        configButton->setObjectName(QStringLiteral("configButton"));
        configButton->setGeometry(QRect(630, 30, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 22));
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

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "Vial One", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "VIal Two", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("MainWindow", "Vial Three", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Grams", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Tbsp", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Tsp", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("MainWindow", "Dispense", Q_NULLPTR));
        manualButton->setText(QApplication::translate("MainWindow", "Manual", Q_NULLPTR));
        menuButton->setText(QApplication::translate("MainWindow", "Menu", Q_NULLPTR));
        configButton->setText(QApplication::translate("MainWindow", "Configure", Q_NULLPTR));
        menuAutoSpice_v_01->setTitle(QApplication::translate("MainWindow", "AutoSpice v.01", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
