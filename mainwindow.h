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
    void on_tableWidget_cellClicked(int row, int column);//Выделение живых клеток


    void on_ClearButton_clicked();//Очистка поля

public slots:
    void StartButton();//Старт игры
    void StopButton();// Остановка игры
    void Create_Future_Field();//Создание массива следующего поколения
    void saveGame();//Сохронение текущего поля
    void loadGame();//Загрузка сохронённого поля
private:
    Ui::MainWindow *ui;
    QChar** now;//Массив текущего поколения
    QChar** future;//Массив следующего поколения
    QTimer* timer;//Таймер
    int lab;//Номер поколения
    QFile file;
    //void Create_Future_Field();
    void Check_Cell(int row, int col,int n);//Определение жизни клетки для следующего поколения
    void Counter_Cell(int row, int col);//Подсчёт живых клеток вокруг
    void Copy_Future_Field_in_Now_Field();//Передвижение времени
    void Watch( );//Показ на экране


};

#endif // MAINWINDOW_H
