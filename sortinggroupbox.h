#ifndef SORTINGGROUPBOX_H
#define SORTINGGROUPBOX_H

#include <QGroupBox>
#include <QObject>
#include <QWidget>
#include <QDebug>

class SortingGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    SortingGroupBox(QWidget* parent = nullptr);
};

#endif // SORTINGGROUPBOX_H
