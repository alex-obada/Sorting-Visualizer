#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <thread>
#include <chrono>

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

#include "modifyresult.h"

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QDialog
{
    Q_OBJECT

public:

    ModifyResult GetResult() const;
    explicit ModifyDialog(QWidget *parent = nullptr);
    
private:
    void InitCbAlgorithm();
    void InitSpinBoxes();
    void InitButton();
    void InitLayout();

private:
    QComboBox *cbAlgorithm;
    QSpinBox *sbSpeed;
    QSpinBox *sbNumber;
    QPushButton *button;
};

#endif // MODIFYDIALOG_H
