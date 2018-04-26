#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_motorSpin_clicked();

    void on_selectMenu_activated(int index);

    void on_selectMenu_activated(const QString &arg1);

    void on_weightBox_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
