#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>

#include "sortingelement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QHBoxLayout* ResetSortingLayout();
    void ResetSortingElements();
    void RandomiseNumbers();
    void Sort();
//    void SetNR(size_t n);

private:
    Ui::MainWindow *ui;

    size_t NR = 10;
    std::vector<SortingElement> elements;
};
#endif // MAINWINDOW_H
