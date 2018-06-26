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
    //ui->tableWidget_1->removeColumn(1);
    /*QTableWidgetItem *item = new QTableWidgetItem();
                item->setText("line");
                ui->tableWidget_1->setItem(0,1,item);
     item->setText("fghfhe");
     ui->tableWidget_1->setItem(1,1,item);*/
    ui->tableWidget_1->item(0, 0)->setText(strNUMG);
    //ui->tableWidget_1->item(0,0)->setText(strNUMG);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DirButton_clicked()
{
    //ui->tableView->horizontalHeader()->setSectionResizeMode(/*номер столбца*/, QHeaderView::Stretch);
}
