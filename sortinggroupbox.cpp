#include "sortinggroupbox.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>

#include <vector>
#include <thread>
#include <random>
#include <chrono>

SortingGroupBox::SortingGroupBox(QWidget *parent)
    : QGroupBox(parent)
{

}

SortingGroupBox::~SortingGroupBox()
{
    for(auto& element : elements)
        delete element.ptr;
}

void SortingGroupBox::resizeEvent(QResizeEvent *event)
{
    for(auto& element : elements)
    {
        element.UpdateSize(nelements, this->height());
    }
}

QBoxLayout *SortingGroupBox::ResetSortingLayout()
{
    delete this->layout();
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight); // gbSorting layout
    layout->setSpacing(1);
    return layout;
}

void SortingGroupBox::ResetSortingElements()
{
    RandomiseNumbers(elements);
    for(auto& element : elements)
    {
        element.UpdateSize(nelements, this->height());
    }

    int r = rand() % elements.size();
    elements[r].ptr->setStyleSheet("background-color: red;");
}

void SortingGroupBox::RandomiseNumbers(std::vector<SortingElement>& elements)
{
    std::vector<size_t> numbers(elements.size());
    for(size_t i = 0; i < nelements; ++i)
        numbers[i] = i + 1;

    //std::random_device rd;
    //std::mt19937 g(rd());
    std::srand(std::time(NULL));
    std::random_shuffle(numbers.begin(), numbers.end());

    for(size_t i = 0; i < nelements; ++i)
        elements[i].value = numbers[i];
}

void SortingGroupBox::HighLightAllElements(size_t time)
{
    for(size_t i = 0; i < elements.size(); ++i)
    {
        elements[i].SetColor("red");
        repaint();
        QCoreApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

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

void SortingGroupBox::Sort()
{
    time = 10;
//    switch (control)
//    {
//        case value:

//            break;
//        default:
//            return;
//    }
//    BubbleSort();
//    MinimumSort();
    tmp.resize(elements.size());
    MergeSort(0, elements.size() - 1);
    for(auto el : elements)
        qDebug() << el.value;

    HighLightAllElements(time);
}

void SortingGroupBox::BubbleSort()
{
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
                elements[i].UpdateSize(nelements, this->height());
                elements[i + 1].UpdateSize(nelements, this->height());
            }
            repaint();
            QCoreApplication::processEvents();
            elements[i].SetColor("black");
            elements[i + 1].SetColor("black");
            repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }
    }
}

void SortingGroupBox::MinimumSort()
{
    size_t index, minim;
    for(size_t i = 0; i < elements.size(); ++i)
    {
        minim = 1e9;

        elements[i].SetColor("red");
        repaint();
        QCoreApplication::processEvents();

        for(size_t j = i + 1; j < elements.size(); ++j)
        {
            qDebug() << "element " << i + 1;
            elements[j].SetColor("red");
            repaint();
            QCoreApplication::processEvents();


            if(elements[j].value < minim)
            {
                minim = elements[j].value;
                index = j;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(time));
            elements[j].SetColor("black");
            repaint();
            QCoreApplication::processEvents();

            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }

        if(minim < elements[i].value)
        {
            std::swap(elements[i].value, elements[index].value);
            elements[i].UpdateSize(nelements, this->height());
            elements[index].UpdateSize(nelements, this->height());
        }
        elements[i].SetColor("black");
        elements[index].SetColor("black");
        repaint();
        QCoreApplication::processEvents();
    }
}

void SortingGroupBox::MergeSort(size_t st, size_t dr)
{
    if(st == dr)
        return;
    int m = (st + dr) >> 1;
    MergeSort(st, m);
    MergeSort(m + 1, dr);
    Interclasare(st, dr);
}

void SortingGroupBox::Interclasare(size_t st, size_t dr)
{
    size_t m = (st + dr) >> 1,
           i = st, j = m + 1, k = -1;
    while(i <= m && j <= dr)
    {
        if(elements[i].value <= elements[j].value)
            tmp[++k] = elements[i++].value;
        else
            tmp[++k] = elements[j++].value;
    }

    while(i <= m)
        tmp[++k] = elements[i++].value;
    while(j <= dr)
        tmp[++k] = elements[j++].value;

    for(size_t i = st; i <= dr; ++i)
    {
        elements[i].value = tmp[i - st];
        elements[i].SetColor("red");
        elements[i].UpdateSize(elements.size(), this->height());

        repaint();
        QCoreApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        elements[i].SetColor("black");
        repaint();
        QCoreApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

    }

}

void SortingGroupBox::SetNumber(size_t n)
{
    nelements = n;

    elements.resize(nelements);
    RandomiseNumbers(elements);

    auto layout = ResetSortingLayout();
    this->setLayout(layout);

    for(auto& element : elements)
    {
        element.ptr = new QWidget();
        element.SetColor("black");
        element.UpdateSize(nelements, element.ptr->height());

        layout->addWidget(element.ptr); //, 0, Qt::AlignBottom | Qt::AlignHCenter);
    }
}

void SortingGroupBox::SetSortingParameters(ModifyResult result)
{
    nelements = result.number;
    time = result.time;
    sortingMethod = result.sort;

    elements.resize(nelements);
    RandomiseNumbers(elements);
}
