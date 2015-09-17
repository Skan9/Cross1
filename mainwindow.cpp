#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <time.h>
#include <windows.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
       ui->tableWidget->setRowCount(50);
       ui->tableWidget->setColumnCount(50);
       now= new QChar*[51];
       for (int i = 0; i<51; i++)
       {
           now[i] = new QChar[51];
           for(int j=0;j<51;j++) now[i][j]=' ';
       }
       lab=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if (now[row][column]!='*')
       {
       QTableWidgetItem* newItem = new QTableWidgetItem(tr(" "));
       newItem->setBackgroundColor(QColor(255,0,0));
       ui->tableWidget->setItem(row,column, newItem);
       now[row][column]='*';
       }
       else
       {
           QTableWidgetItem* newItem = new QTableWidgetItem(tr(" "));
           newItem->setBackgroundColor(QColor(255,255,255));
           ui->tableWidget->setItem(row,column, newItem);
           now[row][column]=' ';
       }

}

void MainWindow::on_pushButton_clicked()
{
    Create_Future_Field();
}

void MainWindow::Create_Future_Field()
{
    lab++;
    future= new QChar*[51];
    for (int i =0; i<51; i++)
    {
        future[i] = new QChar[50];
        for(int j=0;j<51;j++) Counter_Cell(i, j);
    }
    Copy_Future_Field_in_Now_Field();


}

/*void MainWindow::Counter_Border_Cell()
{
    int n=0;
    for (int i=0; i<50;i++)
    {

    }
}*/

void MainWindow::Counter_Cell(int row, int col)
{
    int n=0;
    for (int i=row-1;i<=row+1;i++)
    {
        for(int j=col-1;j<=col+1; j++)
            if (i!=-1&&i!=51&&j!=-1&&j!=51)
            if (now[i][j]=='*') n++;
    }
    Check_Cell(row,col, n);
}

 void MainWindow::Check_Cell(int row, int col,int n)
 {
     if(now[row][col]=='*')
     {

         n--;
         if(n==2||n==3)
          future[row][col]='*';

         else future[row][col]=' ';
     }
     else
     {
         if(n==3)future[row][col]='*';
         else future[row][col]=' ' ;

     }
 }

void MainWindow::Copy_Future_Field_in_Now_Field()
{
    for (int i = 0; i<50; i++)
    {
        for(int j=0;j<50;j++)
        {
            now[i][j]=future[i][j];
        };
    }
    //~masive();
    Watch( );
}
void MainWindow::Watch( )
{

    for(int row=0;row<50;row++)
    {
        for (int col=0;col<50;col++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem(QString("%1").arg(' '));

            if (now[row][col]!=' ')
            {
            newItem->setBackgroundColor(QColor(255,0,0));
            }
            ui->tableWidget->setItem(row,col, newItem);
            ui->label->setNum(lab);
        }
    }
     //time = new QTimer(this);
    //connect(time, SIGNAL(timeout()), SLOT(slotUpdateDateTime()));
     //Sleep(2000);
   // time->start(1000);
   // Create_Future_Field();
}
/*MainWindow::~masive()
{
    delete []future;
}*/

void MainWindow::on_pushButton_2_clicked()
{
    for (int i = 0; i<51; i++)
    for(int j=0;j<51;j++) now[i][j]=' ';
    lab=1;
    Watch( );

}
