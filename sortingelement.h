#ifndef SORTINGELEMENT_H
#define SORTINGELEMENT_H

#include <QWidget>

struct SortingElement {
    int value;
    QWidget* ptr;

    void UpdateSize(size_t nmax, size_t height)
    {
        ptr->setMaximumHeight(value * height / nmax);
    }

    void SetColor(QString const& color)
    {
        ptr->setStyleSheet("background-color: " + color + ';');
    }
};


#endif // SORTINGELEMENT_H
