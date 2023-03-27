#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortingelement.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QDebug>

#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout* layout = new QHBoxLayout; // gbSorting layout
    layout->setSpacing(1);
//    layout->setAlignment(Qt::AlignmentFlag::AlignBottom);
//                         Qt::AlignmentFlag::AlignHCenter);
//    layout->setDirection(QBoxLayout::Direction::LeftToRight);
    ui->gbSorting->setLayout(layout);



    std::vector<SortingElement> elements(NR);
    std::vector<size_t> numbers(NR);

    for(size_t i = 0; i < NR; ++i)
        numbers[i] = i + 1;

    srand(time(NULL));
    std::random_shuffle(numbers.begin(), numbers.end());
    for(size_t i = 0; i < NR; ++i)
        elements[i].value = numbers[i];

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

