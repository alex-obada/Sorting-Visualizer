#include "mainwindow.h"
#include "modifydialog.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFrame>
#include <QDebug>
#include <QTimer>

#include <vector>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnPlay, &QPushButton::clicked, this, [&](){
        ui->gbSorting->Sort();
    });
   ui->gbSorting->SetNumber(50);
    // ModifyDialog dialog;
    // if(dialog.exec() == QDialog::Accepted)
    //     ui->gbSorting->SetSortingParameters(dialog.GetResult());

}

MainWindow::~MainWindow()
{
    delete ui;
}
