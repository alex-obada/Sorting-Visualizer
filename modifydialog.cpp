#include "modifydialog.h"
#include "ui_modifydialog.h"

ModifyResult ModifyDialog::GetResult() const
{
    ModifyResult rez;
    rez.number = ui->hsTime->value();
    rez.time = ui->hsTime->value();
    rez.sort = (SortingMethod)ui->cmbMethod->currentIndex();
}

ModifyDialog::ModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}
