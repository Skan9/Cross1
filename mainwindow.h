#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Seach_Feld();
    void Seach_Word();
    void Add_Word( QString str);
    void Create_Feld();
    void Watch( );
    void Watch1( QChar r );

private slots:
    void on_pushButton_clicked();
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
   // const int n=20;
    QTableWidget tbl;
    int col,row,max,ccol,crow, rcol,rrow,num_b;
    QChar ** f;
    QString filename;

};

#endif // MAINWINDOW_H
