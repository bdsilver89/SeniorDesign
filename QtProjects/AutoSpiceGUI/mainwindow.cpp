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

void MainWindow::on_manualButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_menuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_configButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_doubleSpinBox_editingFinished()
{
    const double inputWeight = ui->doubleSpinBox->value();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    QString inputType = arg1;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Dispensing Spices", "Would you like to dispense?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
      } else {
        qDebug() << "Yes was *not* clicked";
      }
}

void MainWindow::on_lineEdit_returnPressed()
{

}
