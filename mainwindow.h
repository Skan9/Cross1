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
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;
    QChar** now;
    QChar** future;
    void Create_Future_Field();
    void Check_Cell(int row, int col,int n);
    void Counter_Cell(int row, int col);
    void Copy_Future_Field_in_Now_Field();
    void Watch( );

};

#endif // MAINWINDOW_H
