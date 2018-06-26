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
    ui->tableWidget_1->insertRow(0);
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
    ui->tableWidget_1->removeColumn(2);

    /*QDirIterator ItR("C:/Users/Илья1/Desktop/Test/", QDir::Files);
        while (ItR.hasNext()) {
                QFile file("ItR.next()");               //файл-источник, который находится по адресу ItR
                if(!file.open(QFile::ReadOnly)) {
                    //return 0;
                }
                qDebug()<<"Конский прибамбас";
                file.close();
        }*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DirButton_clicked()
{
    //ui->tableView->horizontalHeader()->setSectionResizeMode(/*номер столбца*/, QHeaderView::Stretch);
}
