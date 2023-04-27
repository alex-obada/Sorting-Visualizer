#include "mainwindow.h"
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
        Sort();
    });

    elements.resize(NR);
    RandomiseNumbers(elements);

    auto layout = ResetSortingLayout();
    ui->gbSorting->setLayout(layout);

    for(auto& element : elements)
    {
        element.ptr = new QWidget();
        element.SetColor("black");
        element.UpdateSize(NR, element.ptr->height());

        layout->addWidget(element.ptr); //, 0, Qt::AlignBottom | Qt::AlignHCenter);
    }


}

MainWindow::~MainWindow()
{
    for(auto& element : elements)
        delete element.ptr;
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
    RandomiseNumbers(elements);
    for(auto& element : elements)
    {
        element.UpdateSize(NR, ui->gbSorting->height());
    }

    int r = rand() % elements.size();
    elements[r].ptr->setStyleSheet("background-color: red;");
}

void MainWindow::RandomiseNumbers(std::vector<SortingElement>& elements)
{
    std::vector<size_t> numbers(elements.size());
    for(size_t i = 0; i < NR; ++i)
        numbers[i] = i + 1;

    srand(time(NULL));
    std::random_shuffle(numbers.begin(), numbers.end());

    for(size_t i = 0; i < NR; ++i)
        elements[i].value = numbers[i];
}

void MainWindow::HighLightAllElements(size_t time)
{
    for(size_t i = 0; i < elements.size(); ++i)
    {
        qDebug() << i << ' ';
        elements[i].SetColor("red");
        repaint();
        QCoreApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

        qDebug() << i << " stop";
        elements[i].SetColor("black");
        repaint();
        QCoreApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

    }

    for(size_t i = 0; i < elements.size(); ++i)
        elements[i].SetColor("red");
    repaint();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for(size_t i = 0; i < elements.size(); ++i)
        elements[i].SetColor("black");
    repaint();
}

void MainWindow::Sort()
{
    size_t time = 50;

    bool sorted = false;
    while(!sorted)
    {
        sorted = true;
        for(size_t i = 0; i < elements.size() - 1; ++i)
        {
            qDebug() << "elementele " << i + 1 << ' ' << i + 2;
            elements[i].SetColor("red");
            elements[i + 1].SetColor("red");
            repaint();
            QCoreApplication::processEvents();

            std::this_thread::sleep_for(std::chrono::milliseconds(time));

            if(elements[i].value > elements[i + 1].value)
            {
                sorted = false;
                std::swap(elements[i].value, elements[i + 1].value);
                elements[i].UpdateSize(NR, ui->gbSorting->height());
                elements[i + 1].UpdateSize(NR, ui->gbSorting->height());
            }
            repaint();
            QCoreApplication::processEvents();
            elements[i].SetColor("black");
            elements[i + 1].SetColor("black");
            repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }
    }
    HighLightAllElements(time);
}

