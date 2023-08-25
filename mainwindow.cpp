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
    setWindowTitle(tr("Sorting Visualizer"));

    ConnectButtons();

#ifdef _NO_DIALOG
    // speed, elements, sorting
    ui->gbSorting->
        SetSortingParameters(
            SortingParameters(100, 10, QuickSort));
#else
    UpdateSortingParameters();
#endif
}

void MainWindow::ConnectButtons()
{
    connect(ui->btnPlay, &QPushButton::clicked, this, [&](){
        ui->btnReset->setDisabled(true);
        ui->btnPlay->setDisabled(true);
        ui->btnModify->setDisabled(true);
        ui->gbSorting->Sort();
        ui->btnPlay->setDisabled(false);
        ui->btnModify->setDisabled(false);
        ui->btnReset->setDisabled(false);
    });

    connect(ui->btnModify, &QPushButton::clicked, this, [&]() {
        UpdateSortingParameters();
    });
    
    connect(ui->btnStop, &QPushButton::clicked, this, [&]() {
        ui->gbSorting->Stop();
    });

    connect(ui->btnReset, &QPushButton::clicked, this, [&]() {
        ui->gbSorting->ResetSortingElements();
    });
}

void MainWindow::UpdateSortingParameters()
{
    static ModifyDialog* dialog = nullptr;
    if(!dialog)
        dialog = new ModifyDialog();

    dialog->exec();
    auto result = dialog->GetResult();
    ui->gbSorting->SetSortingParameters(result);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ui->gbSorting->Stop();
}

MainWindow::~MainWindow()
{
    delete ui;
}
