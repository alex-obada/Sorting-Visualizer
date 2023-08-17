#ifndef SORTINGGROUPBOX_H
#define SORTINGGROUPBOX_H

#include <QGroupBox>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QBoxLayout>

#include "sortingelement.h"
#include "modifyResult.h"

class SortingGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    SortingGroupBox(QWidget* parent = nullptr);

    QBoxLayout* ResetSortingLayout();
    void ResetSortingElements();
    void RandomiseNumbers(std::vector<SortingElement>& elements);
    void HighLightAllElements(size_t time);
    void Sort();
    void SetNumber(size_t n);
    void SetSortingParameters(ModifyResult const& result);

private:
    void BubbleSort();
    void MinimumSort();
    void MergeSort(size_t st, size_t dr);
    void Interclasare(size_t st, size_t dr);

protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    size_t elements_number;
    size_t iter_sleep_time;
    SortingAlgorithm algorithm;
    std::vector<SortingElement> elements;
    std::vector<size_t> tmp;
};

#endif // SORTINGGROUPBOX_H
