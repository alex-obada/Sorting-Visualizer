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

    connect(ui->btnModify, &QPushButton::clicked, [&]() {
        UpdateSortingParameters();    
    });

#if _NO_DIALOG
    // speed, elements, sorting
    ui->gbSorting->SetSortingParameters(SortingParameters(100, 10, QuickSort));
#else
    UpdateSortingParameters();
#endif
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

MainWindow::~MainWindow()
{
    delete ui;
}
