#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //~masive();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QChar** now;
    QChar** future;
    QTimer* time;
    int lab;

    void Create_Future_Field();
    void Check_Cell(int row, int col,int n);
    void Counter_Cell(int row, int col);
    void Copy_Future_Field_in_Now_Field();
    void Watch( );


};

#endif // MAINWINDOW_H
