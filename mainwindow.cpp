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
}

MainWindow::~MainWindow()
{
    delete ui;
}

vector <Result> Results;
int Table1AddRows=0;
int Table2AddRows=0;
int Table3AddRows=0;
int Table3AddColumn=0;
int NumAnswer=0;
int ResultSize=0;

void MainWindow::on_DirButton_clicked()
{
    for(int i=0;i<Table1AddRows;i++){
        ui->tableWidget_1->removeRow(0);
    }
    for(int i=0;i<Table2AddRows;i++){
        ui->tableWidget_2->removeRow(0);
    }
    for(int i=0;i<Table3AddRows;i++){
        ui->tableWidget_3->removeRow(0);
    }
    for(int i=0;i<Table3AddColumn;i++){
        ui->tableWidget_3->removeColumn(1);
    }
    Table1AddRows=0;
    Table1AddRows=0;
    Table3AddRows=0;
    Table3AddColumn=0;
    Results.clear();
    QString path = QFileDialog::getExistingDirectory(this,tr("Выбор папки с результатами"));
    //QString path = "C:/Users/Илья1/Desktop/Test";
    QDir dir(path);
    int count=0;
    QDirIterator ItR(dir, QDirIterator::Subdirectories );
    while (ItR.hasNext()) {
        ItR.next();
        QFile file(ItR.filePath());
        if(file.open(QFile::ReadOnly))
        {
            QTextStream stream(&file);
            QString TestName = stream.readLine();
            if (TestName==ui->lineEdit->text())
            {
                count++;
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
            }
            file.close();
        }
    }
    if(count>0)
    {
        ResultSize=Results.size();
        for (int i=0;i<ResultSize;i++){                             //Table 1
            ui->tableWidget_1->insertRow(i);
            Table1AddRows++;
            for(int j = 0; j<4; j++){
                QTableWidgetItem *item = new QTableWidgetItem();
                if (j==0){item->setText(Results.at(i).user_name);}
                if (j==1){
                    NumAnswer = Results.at(i).num_answer.toInt();
                    int totalCorrect=0;
                    for(int k = 0; k<NumAnswer;k++){
                        if (Results.at(i).correct.at(k)=="1"){
                            totalCorrect++;
                        }
                    }
                    double percent = 100*totalCorrect/NumAnswer;
                    item->setText(QString::number(percent));
                }
                if (j==2){item->setText(Results.at(i).time);}
                if (j==3){item->setText(Results.at(i).date);}
                ui->tableWidget_1->setItem(i,j,item);
            }
        }                                                               //
        QStringList name_table2;
        for (int i=0;i<NumAnswer;i++){                                  //Table 2
            ui->tableWidget_2->insertRow(i);
            Table2AddRows++;
            name_table2 << "";
            for(int k = 0; k<2;k++){
                QTableWidgetItem *item = new QTableWidgetItem();
                if (k==0){
                    item->setText(QString::number(i+1));
                }
                if (k==1){
                    int answerCorrect=0;
                    for (int j=0;j<ResultSize;j++){
                        if (Results.at(j).correct.at(i)=="1"){
                            answerCorrect++;
                        }
                    }
                    double percent = 100*answerCorrect/Results.size();
                    item->setText(QString::number(percent));
                }
                ui->tableWidget_2->setItem(i,k,item);
            }
        }
        ui->tableWidget_2->setVerticalHeaderLabels(name_table2);         //
        QStringList name_table3;
        name_table3 << "Имя ученика\\Номер задания";
        for (int i=0;i<ResultSize;i++){                             //Table 3
            ui->tableWidget_3->insertRow(i);
            Table3AddRows++;
        }
        for (int i=0;i<NumAnswer;i++){
            ui->tableWidget_3->insertColumn(i+1);
            Table3AddColumn++;
            name_table3<<QString::number(i+1);
        }
        ui->tableWidget_3->setHorizontalHeaderLabels(name_table3);
        for (int i=0;i<ResultSize;i++){
            for (int j=0;j<NumAnswer+1;j++){
                QTableWidgetItem *item = new QTableWidgetItem();
                if(j==0){
                    item->setText(Results.at(i).user_name);
                }
                else {
                    if(Results.at(i).correct.at(j-1)=="1"){
                        item->setText("+");
                    }
                    else{
                        item->setText("-");
                    }
                }
                ui->tableWidget_3->setItem(i,j,item);
            }
        }
    }
}
