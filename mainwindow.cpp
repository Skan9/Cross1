#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
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
{
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
    int numc,numr=0;
    col=0;
    row=0;
    max=0;
    ccol=0;
    crow=0;
    rcol=0;
    rrow=0;
    num_b=0;
    for(int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            QRegExp reg("[А-Яа-я]");
            QVariant v(reg);
            if(f[i][j]=='*'||(f[i][j]==v&&(f[i][j-1]=='*'||f[i-1][j]=='*'||f[i][j+1]=='*'||f[i+1][j]=='*')))
            {
                row++;
                if(f[j][i]!='*'||f[j][i]!=' ')
                {
                    numr=j;
                }

            }
            else
            {
                if (max<row)
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
 //=========================================================================
            if (f[j][i]=='*'||(f[j][i]==v&&(f[j][i-1]=='*'||f[j-1][i]=='*'||f[j][i+1]=='*'||f[j+1][i]=='*')))
            {
                col++;
                if(f[j][i]!='*'||f[j][i]!=' ')
                {
                    numc=j;
                }

            }
            else
            {
                if (max<col)
                {
                    max=col;
                    ccol=j;
                    crow=i;
                    rcol=0;
                    rrow=0;
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
        Seach_Word();

    }
    else Watch();


}
void MainWindow::Seach_Word()
{
    QString str;
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
                if (num_b==0)
                {

                Add_Word(str);
                }
                else if(rcol==0&&num_b==0)
                {

                    if(f[num_b][ccol]==str[num_b-(crow-max)] ) Add_Word(str);
                    max=0;
                }
                else if(rcol==0&&num_b!=0)
                {

                     Add_Word(str);
                     max=0;
                }
                else
                {
                    if(f[rcol-num_b][rrow]==str[crow-num_b] ) Add_Word(str);
                    max=0;
                }
            }
           else if(max==0)
            {

              break;
            }

        }
       Seach_Feld();
    }



void MainWindow::Add_Word( QString str)
{
    QMessageBox::information(this,"OKKKKK","OK4");
    int j=0;
    if (ccol==0 && crow==0)
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
/*
void MainWindow::Watch1( QChar r )
{
    for(int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem(QString("%1").arg(r));
            if (f[i][j]!=' ')
            {
            newItem->setBackgroundColor(QColor(192,192,192));
            }
            ui->tableWidget->setItem(i,j, newItem);
        }
    }
}*/
void MainWindow::Watch( )
{
    for(int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            QTableWidgetItem* newItem = new QTableWidgetItem(QString("%1").arg(filename));
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
