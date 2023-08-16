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
    // ui->gbSorting->SetNumber(50);
    connect(ui->btnModify, &QPushButton::clicked, [&]() {
        UpdateSortingParameters();    
    });

    UpdateSortingParameters();
}

void MainWindow::UpdateSortingParameters()
{
    static ModifyDialog* dialog;
    if(!dialog)
        dialog = new ModifyDialog();

    dialog->exec();
    auto result = dialog->GetResult();
    ui->gbSorting->SetSortingParameters(result);
}

MainWindow::~MainWindow()
{
    delete ui;
}
