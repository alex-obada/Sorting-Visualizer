#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gbSorting->setLayout(new QHBoxLayout());
//    ui->gbSorting->layout()->addWidget(new QPushButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

