#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
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


    void on_ClearButton_clicked();

    void on_StopButton_clicked();



    void on_StartButton_clicked();
public slots:
    void StartButton();
    void StopButton();
    void Create_Future_Field();
    void saveGame();
    void loadGame();
private:
    Ui::MainWindow *ui;
    QChar** now;
    QChar** future;
    QTimer* timer;
    int lab;
    QFile file;
    //void Create_Future_Field();
    void Check_Cell(int row, int col,int n);
    void Counter_Cell(int row, int col);
    void Copy_Future_Field_in_Now_Field();
    void Watch( );


};

#endif // MAINWINDOW_H
