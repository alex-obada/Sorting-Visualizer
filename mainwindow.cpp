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
        element.ptr->setMaximumHeight(element.value * element.ptr->height() / NR);
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
    auto layout = ResetSortingLayout();

    RandomiseNumbers();
    for(auto& element : elements)
    {

        element.ptr->setMaximumHeight(element.value * ui->gbSorting->height() / NR);
        layout->addWidget(element.ptr);
    }

    ui->gbSorting->setLayout(layout);
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

#if 0
    bool sorted = false;
    while(!sorted)
    {
        sorted = true;
        for(size_t i = 0; i < elements.size() - 1; ++i)
            if(elements[i].value > elements[i + 1].value)
            {
                sorted = false;
                auto layout = ui->gbSorting->layout();
                for(auto& element : elements)
                    layout->removeWidget(element.ptr);

                std::swap(elements[i], elements[i + 1]);
                elements[i].ptr->setStyleSheet("background-color: red;");
                elements[i + 1].ptr->setStyleSheet("background-color: red;");


                for(auto& element : elements)
                    layout->addWidget(element.ptr);

                std::this_thread::sleep_for(std::chrono::milliseconds(5000));

                elements[i].ptr->setStyleSheet("background-color: black;");
                elements[i + 1].ptr->setStyleSheet("background-color: black;");
            }
    }
#endif
}

