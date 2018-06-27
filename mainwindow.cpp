#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "result.h"
#include <QDebug>
#include <stdlib.h>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QDirIterator>

using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_1->horizontalHeader()->resizeSection(0,110);
    ui->tableWidget_1->horizontalHeader()->resizeSection(2,110);
    ui->tableWidget_2->horizontalHeader()->resizeSection(1,140);
    ui->tableWidget_3->horizontalHeader()->resizeSection(0,180);
    ui->tableWidget_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /*ui->tableWidget_1->insertRow(0);
    ui->tableWidget_1->insertRow(1);
    ui->tableWidget_1->insertRow(2);
    ui->tableWidget_1->insertRow(1);
    ui->tableWidget_1->removeRow(0);
    ui->tableWidget_1->insertColumn(4);
    int NUMG=1;
    QString strNUMG=QString::number(NUMG);
    QStringList name_table;
    name_table << "asd" << "qwe" << "zxc";
    ui->tableWidget_1->setVerticalHeaderLabels(name_table);
    name_table <<"gfg";
    name_table<<strNUMG;
    ui->tableWidget_1->setHorizontalHeaderLabels(name_table);
    for(int i = 0; i<6; i++){
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(strNUMG);
                strNUMG+="2";
                ui->tableWidget_1->setItem(0,i,item);
    }
    ui->tableWidget_1->removeColumn(2);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

vector <Result> Results;
int Table1AddRows=0;

void MainWindow::on_DirButton_clicked()
{
    for(int i=0;i<Table1AddRows;i++){
        ui->tableWidget_1->removeRow(0);
    }
    Table1AddRows=0;
    Results.clear();
    //QString path = QFileDialog::getExistingDirectory(this,tr("Выбор папки с результатами"));
    QString path = "C:/Users/Илья1/Desktop/Test";
    QDir dir(path);
    int count=0;
    QDirIterator ItR(dir, QDirIterator::Subdirectories );
    while (ItR.hasNext()) {
        ItR.next();
        QFile file(ItR.filePath());
        if(file.open(QFile::ReadOnly))
        {
            count++;
            QTextStream stream(&file);
            QString TestName = stream.readLine();
            //if (TestName==ui->lineEdit->text())
            //{
                Result r;
                r.test_name = TestName;
                r.user_name = stream.readLine();
                r.time = stream.readLine();
                r.date = stream.readLine();
                QString strNumAnswer = stream.readLine();
                r.num_answer = strNumAnswer;
                int NumAnswer = strNumAnswer.toInt();
                for (int i=0;i<NumAnswer;i++){
                    r.correct.push_back(stream.readLine());
                }
                Results.push_back(r);
                //qDebug()<<str<<endl<<str1;
                //qDebug()<<count;
            //}
            file.close();
        }
    }
    for (int i=0;i<Results.size();i++){
        ui->tableWidget_1->insertRow(i);
        Table1AddRows++;
        for(int j = 0; j<4; j++){
            QTableWidgetItem *item = new QTableWidgetItem();
            if (j==0){item->setText(Results.at(i).user_name);}
            if (j==1){
                int NumAnswer = Results.at(i).num_answer.toInt();
                int totalCorrect=0;
                for(int k = 0; k<NumAnswer;k++){
                    if (Results.at(i).correct.at(k)=="1"){
                        totalCorrect++;
                    }
                }
            qDebug()<<totalCorrect;
            qDebug()<<NumAnswer;
            double percent = 100*totalCorrect/NumAnswer;
            qDebug()<<percent;
            item->setText(QString::number(percent));
            }
            if (j==2){item->setText(Results.at(i).time);}
            if (j==3){item->setText(Results.at(i).date);}
            ui->tableWidget_1->setItem(i,j,item);
        }
    }
}
