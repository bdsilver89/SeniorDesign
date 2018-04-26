#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_motorSpin_clicked()
{
    static int count = 0;
        QString strCount;

        // display text message in first label
        ui->lblSpins->setText("Number of spins");

        // display button clicked count in second label
        count++;
        strCount.sprintf("%d", count);
        ui->lblSpinCount->setText(strCount);
}

void MainWindow::on_selectMenu_activated(int index)
{

    ui->selectIndex->display(index);
}

void MainWindow::on_selectMenu_activated(const QString &arg1)
{
    ui->menuItem->setText(arg1);
}

void MainWindow::on_weightBox_editingFinished()
{
   const int value = ui->weightBox->value();
   QString valuestr;
   valuestr.sprintf("%d",value);
   if (value == 1) {
       ui->lblWeight->setText(valuestr + " gram");
   }
   else {
   ui->lblWeight->setText(valuestr + " grams");
   }
}
