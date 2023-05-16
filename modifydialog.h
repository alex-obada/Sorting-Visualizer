#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <thread>
#include <chrono>

#include <QDialog>

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
    ~ModifyDialog();

private:
    Ui::ModifyDialog *ui;
};

#endif // MODIFYDIALOG_H
