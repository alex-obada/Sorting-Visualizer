#include "sortinggroupbox.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QBrush>

#include <vector>
#include <thread>
#include <random>
#include <chrono>


void SleepFor(size_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool SortingGroupBox::isBusy() const noexcept
{
    return busy;
}

void SortingGroupBox::Tick()
{
    repaint();
    QCoreApplication::processEvents();
    SleepFor(iter_sleep_time);
}

SortingGroupBox::SortingGroupBox(QWidget *parent)
    : QGroupBox(parent)
{}

void SortingGroupBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);

    QBrush brush(Qt::black);
    painter.setBrush(brush);

    size_t space = 3; // pixels
    int64_t elem_width = (int64_t)(size().width() - space * (elements.size() - 1)) / 
                         (int64_t)elements.size();
    size_t max_height = size().height(); 


    // qDebug() << elem_width;
    if(elem_width <= 0)
        return;

    size_t elem_height;
    size_t x, y;

    for(size_t i = 0; i < elements.size(); ++i)
    {
        elem_height = (double)elements[i].value / elements.size() * max_height;
        x = elem_width * i + space * i;
        y = size().height() - elem_height;

        painter.setBrush(elements[i].color);

        if(i + 1 == elements.size())
            painter.drawRect(x, y, size().width() - x, elem_height);
        else
            painter.drawRect(x, y, elem_width, elem_height);
    }
}


void SortingGroupBox::ResetSortingElements()
{
    RandomiseValuesOfElements();
    repaint();
}

void SortingGroupBox::RandomiseValuesOfElements()
{
    std::vector<size_t> numbers(elements.size());
    for(size_t i = 0; i < elements_number; ++i)
        numbers[i] = i + 1;

    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    for(size_t i = 0; i < elements_number; ++i)
        elements[i].value = numbers[i];
}

void SortingGroupBox::Sort()
{
    busy = true;
    switch (algorithm)
    {
        case SortingAlgorithm::Empty :
            QMessageBox::critical(nullptr, tr("Eroare"), tr("Nu a fost specificata nicio sortare."));
            busy = false;
            return;
        case SortingAlgorithm::BubbleSort :
            BubbleSort();
            break;
        case SortingAlgorithm::MinimumSort :
            MinimumSort();
            break;
        case SortingAlgorithm::MergeSort :
            MergeSort();
            break;
        case SortingAlgorithm::QuickSort :
            QuickSort();
            break;
    }

    HighLightAllElements();
    busy = false;
}

void SortingGroupBox::SetSortingParameters(SortingParameters const& result)
{
    elements_number = result.number;
    iter_sleep_time = result.speed;
    algorithm       = result.algorithm;

    elements.resize(elements_number);
    RandomiseValuesOfElements();
}

void SortingGroupBox::HighLightAllElements()
{
    for(size_t i = 0; i < elements.size(); ++i)
    {
        elements[i].color = Qt::red;
        Tick();

        elements[i].color = Qt::black;
        Tick();
    }

    for(size_t i = 0; i < elements.size(); ++i)
        elements[i].color = Qt::red;
    repaint();
    SleepFor(1000);

    for(size_t i = 0; i < elements.size(); ++i)
        elements[i].color = Qt::black;
    repaint();
}

///////////////////////
/// SORTING METHODS ///
///////////////////////

void SortingGroupBox::BubbleSort()
{
    bool sorted = false;
    while(!sorted)
    {
        sorted = true;
        for(size_t i = 0; i < elements.size() - 1; ++i)
        {
            qDebug() << "elementele " << i + 1 << ' ' << i + 2;
            elements[i].color = Qt::red;
            elements[i + 1].color = Qt::red;
            Tick();

            if(elements[i].value > elements[i + 1].value)
            {
                sorted = false;
                std::swap(elements[i].value, elements[i + 1].value);
                Tick();
            }

            elements[i].color = Qt::black;
            elements[i + 1].color = Qt::black;
            Tick();
        }
    }
}

void SortingGroupBox::MinimumSort()
{
    size_t index_min;
    for(size_t i = 0; i < elements.size(); ++i)
    {
        index_min = i;
        elements[i].color = Qt::red;
        Tick();

        for(size_t j = i + 1; j < elements.size(); ++j)
        {
            qDebug() << "element " << i + 1;
            elements[j].color = Qt::red;
            Tick();

            if(elements[j].value < elements[index_min].value)
                index_min = j;

            elements[j].color = Qt::black;
            Tick();
        }

        if(index_min != i)
        {
            std::swap(elements[i].value, elements[index_min].value);

        }
        elements[i].color = Qt::black;
        elements[i + 1].color = Qt::black;
        Tick();
    }
}

void SortingGroupBox::MergeSort()
{
    tmp.resize(elements.size());
    InnerMergeSort(0, elements.size() - 1);
}

void SortingGroupBox::InnerMergeSort(size_t st, size_t dr)
{
    if(st == dr)
        return;
    int m = (st + dr) >> 1;
    InnerMergeSort(st, m);
    InnerMergeSort(m + 1, dr);
    Merge(st, dr);
}

void SortingGroupBox::Merge(size_t st, size_t dr)
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
        elements[i].color = Qt::red;
        Tick();
        elements[i].color = Qt::black;
        Tick();
    }
}

void SortingGroupBox::QuickSort()
{
    InnerQuickSort(0, elements.size() - 1);
}

void SortingGroupBox::InnerQuickSort(size_t st, size_t dr)
{
    if(st >= dr)
        return;
    
    size_t pivot_index = (st + dr) >> 1;
    size_t pivot = elements[pivot_index].value;
    size_t i = st, j = dr;
    elements[pivot_index].color = Qt::green;

    while(i <= j)
    {
        while(elements[i].value < pivot)
        {
            elements[i].color = Qt::red;
            Tick();
            elements[i].color = Qt::black;
            i++;
        }
        elements[i].color = Qt::red;

        while(j >= 0 && elements[j].value > pivot)
        {
            elements[j].color = Qt::red;
            Tick();
            elements[j].color = Qt::black;
            j--;
        }

        if((long long)j < 0)
        {
            elements[i].color = Qt::black;
            return;
        }

        elements[i].color = Qt::red;
        Tick();
        
        if(i <= j)
        {
            assert((long long)j >= 0);

            elements[i].color = Qt::blue;
            elements[j].color = Qt::blue;
            std::swap(elements[i++].value, elements[j--].value);
            Tick();

            elements[i - 1].color = Qt::black;
            elements[j + 1].color = Qt::black;
        }
        else
        {
            elements[i].color = Qt::black;
            elements[j].color = Qt::black;
        }
        Tick();
    }
    elements[pivot_index].color = Qt::black;

    InnerQuickSort(st, j);
    InnerQuickSort(i, dr);
}
