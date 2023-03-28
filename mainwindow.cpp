#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFrame>
#include <QDebug>

#include <vector>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto layout = ResetSortingLayout();
    ui->gbSorting->setLayout(layout);


    connect(ui->btnPlay, &QPushButton::clicked, this, [&](){
        ResetSortingElements();
    });

    elements.resize(NR);
    RandomiseNumbers();


    for(auto& element : elements)
    {
        element.ptr = new QWidget();
        element.ptr->setStyleSheet("background-color: black;");
        element.UpdateSize(NR, element.ptr->height());
        layout->addWidget(element.ptr);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

QHBoxLayout *MainWindow::ResetSortingLayout()
{
    delete ui->gbSorting->layout();
    QHBoxLayout* layout = new QHBoxLayout; // gbSorting layout

    //    layout->setAlignment(Qt::AlignmentFlag::AlignBottom);
    //                         Qt::AlignmentFlag::AlignHCenter);
    //    layout->setDirection(QBoxLayout::Direction::LeftToRight);

    layout->setSpacing(1);
    return layout;
}

void MainWindow::ResetSortingElements()
{
    RandomiseNumbers();
    for(auto& element : elements)
    {
        element.UpdateSize(NR, ui->gbSorting->height());
    }

}

void MainWindow::RandomiseNumbers()
{
    std::vector<size_t> numbers(NR);
    for(size_t i = 0; i < NR; ++i)
        numbers[i] = i + 1;

    srand(time(NULL));
    std::random_shuffle(numbers.begin(), numbers.end());

    for(size_t i = 0; i < NR; ++i)
        elements[i].value = numbers[i];
}

void MainWindow::Sort()
{
    bool sorted = false;
    while(!sorted)
    {
        sorted = true;
        for(size_t i = 0; i < elements.size() - 1; ++i)
            if(elements[i].value > elements[i + 1].value)
            {
                sorted = false;
//                auto layout = ResetSortingLayout();

                std::swap(elements[i].value, elements[i + 1].value);
                elements[i].UpdateSize(NR, ui->gbSorting->height());
                elements[i + 1].UpdateSize(NR, ui->gbSorting->height());
                elements[i].ptr->setStyleSheet("background-color: red;");
                elements[i + 1].ptr->setStyleSheet("background-color: red;");



                std::this_thread::sleep_for(std::chrono::milliseconds(5000));

                elements[i].ptr->setStyleSheet("background-color: black;");
                elements[i + 1].ptr->setStyleSheet("background-color: black;");
            }
    }

}

