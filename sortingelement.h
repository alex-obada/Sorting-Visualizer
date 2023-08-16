#ifndef SORTINGELEMENT_H
#define SORTINGELEMENT_H

#include <QWidget>

struct SortingElement {
    size_t value;
    QWidget* ptr;

    void UpdateSize(size_t valmax, size_t height)
    {
        ptr->setMaximumHeight(value * height / valmax);
    }

    void SetColor(QString const& color)
    {
        ptr->setStyleSheet("background-color: " + color + ';');
    }

    ~SortingElement() 
    { 
        // se elibereaza automat de qt
        // delete ptr;
    }
};


#endif // SORTINGELEMENT_H
