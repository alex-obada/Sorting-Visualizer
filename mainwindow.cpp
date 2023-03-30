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

//    connect(ui->btnPlay, &QPushButton::clicked, this, [&](){
//        std::thread t([](MainWindow* p) {
//            p->ResetSortingElements();
//        });
//        t.join();
//    });


    connect(ui->btnPlay, &QPushButton::clicked, this, [&](){
//        ResetSortingElements();
        Sort();
    });

    elements.resize(NR);
    RandomiseNumbers();

    auto layout = ResetSortingLayout();
    ui->gbSorting->setLayout(layout);

    for(auto& element : elements)
    {
        element.ptr = new QWidget();
        element.SetColor("black");
        element.UpdateSize(NR, element.ptr->height());

        layout->addWidget(element.ptr); //, 0, Qt::AlignBottom | Qt::AlignHCenter);
    }

//    qDebug() << Qt::Alignment(Qt::AlignBottom | Qt::AlignHCenter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QBoxLayout *MainWindow::ResetSortingLayout()
{
    delete ui->gbSorting->layout();
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight); // gbSorting layout
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

    int r = rand() % elements.size();
    elements[r].ptr->setStyleSheet("background-color: red;");

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
    for(size_t i = 0; i < elements.size() - 1; ++i)
    {
        elements[i].SetColor("red");
//        elements[i].SetColor("red");
        repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
#endif
#if 1
    std::thread t([&]()
    {
        for(size_t i = 0; i < elements.size() - 1; ++i)
        {
            elements[i].SetColor("red");
            elements[i + 1].SetColor("red");
            repaint();

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            if(elements[i].value > elements[i + 1].value)
            {
//                std::swap(elements[i].value, elements[i + 1].value);
            }


            elements[i].SetColor("black");
            elements[i + 1].SetColor("black");
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            repaint();

        }
    });
    t.join();
#endif
#if 0
    bool sorted = true;
    while(!sorted)
    {
        sorted = true;
        for(size_t i = 0; i < elements.size() - 1; ++i)
        {
            elements[i].SetColor("red");
            elements[i + 1].SetColor("red");

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            if(elements[i].value > elements[i + 1].value)
            {
                std::swap(elements[i].value, elements[i + 1].value);

            }

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            elements[i].SetColor("black");
            elements[i + 1].SetColor("black");
        }
    }
#endif
}

