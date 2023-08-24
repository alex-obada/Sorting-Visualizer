#ifndef SORTINGGROUPBOX_H
#define SORTINGGROUPBOX_H

#include <QGroupBox>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QBoxLayout>

#include "sortingelement.h"
#include "sortingparameters.h"

class SortingGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    SortingGroupBox(QWidget* parent = nullptr);

    void Sort();
    void Stop();
    bool isBusy() const noexcept;
    void SetSortingParameters(SortingParameters const& result);

private:
    void ResetSortingElements();
    void RandomiseValuesOfElements();
    void HighLightAllElements();
    void Tick();

private:
    void BubbleSort();
    void MinimumSort();
    void MergeSort();
    void InnerMergeSort(size_t st, size_t dr);
    void Merge(size_t st, size_t dr);
    void QuickSort();
    void InnerQuickSort(size_t st, size_t dr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    size_t elements_number;
    size_t iter_sleep_time;
    SortingAlgorithm algorithm;
    std::vector<SortingElement> elements;
    std::vector<size_t> tmp;
    bool busy = false;
    bool stop = false;
};

#endif // SORTINGGROUPBOX_H
