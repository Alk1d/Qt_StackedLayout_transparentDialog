#include "informationdialog.h"
#include "ui_informationdialog.h"
#include <QScreen>
#include <iostream>

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);

        DialogNameLineEdit = ui->NameLineEdit;
        DialogSurnameLineEdit = ui->SurnameLineEdit;
        DialogLastnameLineEdit = ui->LastnameLineEdit;
        DialogBirthdateLineEdit = ui->BirthdateLineEdit;
        DialogHeightLineEdit = ui->HeightLineEdit;
        DialogWeightLineEdit = ui->WeightLlineEdit;

}

InformationDialog::~InformationDialog()
{
    delete ui;
}


void InformationDialog::on_InformationDialog_accepted()
{

    show();

}

void InformationDialog::clearLineEdits()
{
    ui->NameLineEdit->clear();
    ui->SurnameLineEdit->clear();
    ui->LastnameLineEdit->clear();
    ui->BirthdateLineEdit->clear();
    ui->HeightLineEdit->clear();
    ui->WeightLlineEdit->clear();

}

QLineEdit *InformationDialog::getDialogWeightLineEdit() const
{
    return DialogWeightLineEdit;
}

QLineEdit *InformationDialog::getDialogHeightLineEdit() const
{
    return DialogHeightLineEdit;
}

QLineEdit *InformationDialog::getDialogBirthdateLineEdit() const
{
    return DialogBirthdateLineEdit;
}

QLineEdit *InformationDialog::getDialogLastnameLineEdit() const
{
    return DialogLastnameLineEdit;
}

QLineEdit *InformationDialog::getDialogSurnameLineEdit() const
{
    return DialogSurnameLineEdit;
}

QLineEdit *InformationDialog::getDialogNameLineEdit() const
{
    return DialogNameLineEdit;
}

void InformationDialog::mousePressEvent(QMouseEvent *event)
{
   cur_pos = event->globalPosition().toPoint();
}

void InformationDialog::mouseMoveEvent(QMouseEvent *event)
{
    new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
    move(x() + new_pos.x(), y()+ new_pos.y());
    cur_pos = event->globalPosition().toPoint();
}
