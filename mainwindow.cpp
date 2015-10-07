#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <windows.h>
#include <QTimer>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    //timer.setSingleShot(true);
     //timer->setInterval(300);
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
         connect(ui->StartButton, SIGNAL(clicked()), SLOT(StartButton()));
       connect(ui->StopButton, SIGNAL(clicked()), this, SLOT(StopButton()));
       connect(timer, SIGNAL(timeout()), this, SLOT(Create_Future_Field()));
        connect(ui->SaveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
        connect(ui->LoadButton, SIGNAL(clicked()), this, SLOT(loadGame()));
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

void MainWindow:: StartButton()
{
   timer->start(500);


}
void MainWindow:: StopButton()
{
    timer->stop();


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

    for(int row=0;row<51;row++)
    {
        for (int col=0;col<51;col++)
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
    //timer->start(1000);
    //StartButton();
}
/*MainWindow::~masive()
{
    delete []future;
}*/



void MainWindow::on_ClearButton_clicked()
{
    for (int i = 0; i<51; i++)
    for(int j=0;j<51;j++) now[i][j]=' ';
    lab=1;
    Watch( );
}
void MainWindow::saveGame()
{
    QString fr= QFileDialog::getSaveFileName(this,tr("Save"), QDir::homePath(),tr("Save Life (*.txt)"));
     QFile file(fr);
     file.open(QIODevice::WriteOnly | QIODevice::Text);
     QTextStream out(&file);

      out.setCodec(QTextCodec::codecForName("windows-1251"));


    for (int i =0; i<50; i++)
    {

        for(int j=0;j<50;j++)
        {

             out<<now[i][j];

        }
        out<<";";
    }
    out<<lab;

    file.close();
}
void MainWindow::loadGame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Open saved game"),
                                                        QDir::homePath(),
                                                        tr("Conway's Game Of Life File (*.txt)"));
        if(filename.length() < 1)
            return;
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
            return;
        QTextStream in(&file);


        for(int i=0; i < 50; i++) {
           for(int j=0;j<50;j++){

               in >> now[i][j];
           }

               QString t;
           in>>t;

        }
        in>>lab;
        Watch();



}

