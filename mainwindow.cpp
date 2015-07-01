#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
int smax=-2;
int max=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setColumnCount(20);
    f= new QChar*[20];
    for (int i = 0; i<20; i++)
    {
        f[i] = new QChar[20];
        for(int j=0;j<20;j++) f[i][j]=' ';
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{    Watch( );
    //Create_Feld();
    Seach_Feld();
    //Watch( );
}


/*
void MainWindow::Create_Feld()
{
    f= new QChar*[20];
    for (int i = 0; i<20; i++)
        {
            f[i] = new QChar[20];
            for (int j = 0; j<20; j++)
            {
                 QMessageBox::information(this,"rtrt","1");
               // QTableWidgetItem* itm= ui->tableWidget->item(i,j);
                QString sim=ui->tableWidget->item(i, j)->data(Qt::UserRole).toString();
                 QMessageBox::information(this,"rtrt","2");
                f[i][j]=sim[0];
            }
        }
    QMessageBox::information(this,"rtrt","3");
    Seach_Feld();
}*/

void MainWindow::Seach_Feld()
{

   /* if(max!=0 && smax!=max)
    {
        return;

    }
    else if (max!=0 && smax==max) QMessageBox::information(this,"ERROR","error");*/


    int numc=0;
     int  numr=0;
    int col=0;
    int row=0;
    max=0;
    ccol=-1;
    crow=-1;
    rcol=-1;
    rrow=-1;
    num_b=0;
    for(int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            //QRegExp reg("[А-Яа-я]");
            //QVariant v(reg);
            if(f[i][j]=='*' || (f[i][j]!='*' && f[i][j]!=' ' && (f[i][j-1]=='*' ||  f[i][j+1]=='*' )))
            {
                row++;
                if(f[i][j]!='*' && f[i][j]!=' ')
                {
                    numr=j;

                }

            }
            else
            {
                if (max<row)
                {
                    max=row;
                    ccol=-1;
                    crow=-1;
                    rcol=j;
                    rrow=i;
                    num_b=numr;
                    row=0;
                    numr=0;

                }
                //if (num_b!=0) QMessageBox::information(this,"ERROR","Error!!!!!!!!");

            }
 //=========================================================================
            if (f[j][i]=='*' || (f[j][i]!='*' && f[j][i]!=' ' && ( f[j-1][i]=='*' ||  f[j+1][i]=='*')))
            {
                col++;
                if(f[j][i]!='*' && f[j][i]!=' ')
                {
                    numc=j;
                    QMessageBox::information(this,"ERROR","Error2!!!!!!!!");

                }

            }
            else
            {
                if (max<col)
                {
                    max=col;
                    ccol=i;
                    crow=j;
                    rcol=-1;
                    rrow=-1;
                     num_b=numc;
                     col=0;
                     numc=0;
                }

            }


        }
        col=0;
        row=0;
    }

    if(max!=0)
    {
        if(smax<max) smax=max;
        Seach_Word();

    }
    else Watch();


}
void MainWindow::Seach_Word()
{

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    { QMessageBox::information(this,"ERROR","Error!!!!!!!!");

        return;
    }



    QTextStream in(&file);
       while (!in.atEnd()) {
           QString line = in.readLine();
   // Watch1(line[1]);

            if (line.length()==max)
            {
              if(rcol==-1 && num_b!=0)
                {
                   // QMessageBox::information(this,"OKKKKK",f[num_b][ccol]);
                    if(f[num_b][ccol]==line[num_b-(ccol-max)] ) Add_Word(line);
                    max=0;
                }
                else if(crow==-1 && num_b!=0)
                {
                 // QMessageBox::information(this,"OKKKKK",f[rrow][num_b]);
                    if(f[rrow][num_b]==line[num_b-(rcol-max)] ) Add_Word(line);
                    max=0;
                }
                else
                {
                  //QMessageBox::information(this,"OKKKKK","OK44");
                    Add_Word(line);
                    max=0;
                }
            }
           else if(max==0)
            {

              break;
            }

        }
       //if (max!=0 && in.atEnd())return;

       Seach_Feld();
    }



void MainWindow::Add_Word( QString str)
{

    int j=0;
    if (ccol==-1 && crow==-1)
    {
        for (int i=rcol-max;i<rcol;i++)
        {
           f[rrow][i]= str[j];
            j++;
        }
    }
    else
    {

        for (int i=crow-max;i<crow;i++)
        {
            f[i][ccol]= str[j];
            j++;
        }
    }
    Watch();


}
/*void MainWindow::Seach_word_feld()
{
    int min=10000;
    col=0;
    row=0;
    max=0;
    ccol=0;
    crow=0;
    rcol=0;
    rrow=0;
    num_b=0;
    if(f[i][j]!='*' && f[i][j]!=' ')
    {
        row++;
        if (min<row)
        {
            max=row;
            ccol=0;
            crow=0;
            rcol=j;
            rrow=i;
            num_b=numr;
            row=0;
            numr=0;

        }
    }
    if (f[j][i]!='*' && f[j][i]!=' ')
    {
        row++;
        if (min<row)
        {
            max=row;
            ccol=0;
            crow=0;
            rcol=j;
            rrow=i;
            num_b=numr;
            row=0;
            numr=0;

    }
}*/

/*void MainWindow::Delete_Word( QString str)
{

}*/

void MainWindow::Watch( )
{
    for(int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem(QString("%1").arg(f[i][j]));
            if (f[i][j]!=' ')
            {
            newItem->setBackgroundColor(QColor(192,192,192));
            }
            ui->tableWidget->setItem(i,j, newItem);
        }
    }
}



void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if (f[row][column]!='*')
    {
    QTableWidgetItem* newItem = new QTableWidgetItem(tr(" "));
    newItem->setBackgroundColor(QColor(192,192,192));
    ui->tableWidget->setItem(row,column, newItem);
    f[row][column]='*';
    }
    else
    {
        QTableWidgetItem* newItem = new QTableWidgetItem(tr(" "));
        newItem->setBackgroundColor(QColor(255,255,255));
        ui->tableWidget->setItem(row,column, newItem);
        f[row][column]=' ';
    }
}

void MainWindow::on_pushButton_2_clicked()
{

   filename=QFileDialog::getOpenFileName( this,
    QString("Open file"), QString(),
    QString("Text (*.txt);;All (*.*)"));
    //ui->lineEdit->displayText(filename);



}
