#include "modifydialog.h"

#include <QMessageBox>

ModifyResult ModifyDialog::GetResult() const
{
    ModifyResult result;
    result.number = sbNumber->value();
    result.speed = sbSpeed->value();
    result.algorithm = (SortingAlgorithm)cbAlgorithm->currentIndex();

    qDebug() << "Algo:" << result.algorithm << '\n'
                 << "Timp:" << result.speed << '\n'
                 << "Nr  :" << result.number << '\n';

    return result;
}

ModifyDialog::ModifyDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Alege Parametri"));
    InitLayout();
} 

void ModifyDialog::InitCbAlgorithm()
{
    cbAlgorithm = new QComboBox;
    cbAlgorithm->addItem(tr("Alege Sortare"));
    cbAlgorithm->addItem(tr("Sortarea Bulelor"));
    cbAlgorithm->addItem(tr("Sortarea Minimului"));
    cbAlgorithm->addItem(tr("Sortare prin Intercalare"));
    cbAlgorithm->addItem(tr("Quick Sort"));
}

void ModifyDialog::InitSpinBoxes()
{
    sbSpeed = new QSpinBox;
    sbSpeed->setMaximum(100);
    sbSpeed->setMinimum(0);

    sbNumber = new QSpinBox;
    sbNumber->setMaximum(1000);
    sbNumber->setMinimum(10);
}

void ModifyDialog::InitButton()
{
    button = new QPushButton(tr("Ok"));
    button->setFixedWidth(80);
    connect(button, &QPushButton::clicked, [&]() { 
        if(!cbAlgorithm->currentIndex())
        {
            QMessageBox::information(nullptr, tr("Info"), 
                tr("Nu ati ales algorithmul."));
            return;
        }
        close(); 
    });
}

void ModifyDialog::InitLayout()
{
    auto layout = new QGridLayout;

    InitCbAlgorithm();
    InitSpinBoxes();
    InitButton();
    InitButton();

    auto lblAlgo = new QLabel(tr("Algoritm:"));
    auto lblSpeed = new QLabel(tr("Viteza (ms):"));
    auto lblNumber = new QLabel(tr("Numar de elemente:"));

    layout->addWidget(lblAlgo, 0, 0);
    layout->addWidget(cbAlgorithm, 0, 1);
    layout->addWidget(lblSpeed, 1, 0);
    layout->addWidget(sbSpeed, 1, 1);
    layout->addWidget(lblNumber, 2, 0);
    layout->addWidget(sbNumber, 2, 1);
    layout->addWidget(button, 3, 1, Qt::AlignBottom | Qt::AlignRight);
    setLayout(layout);
}
