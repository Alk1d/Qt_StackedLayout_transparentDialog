#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H


#include "qlineedit.h"
#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(QWidget *parent = nullptr);
    ~InformationDialog();

    QPoint getCur_pos() const;

    QLineEdit *getDialogNameLineEdit() const;

    QLineEdit *getDialogSurnameLineEdit() const;

    QLineEdit *getDialogLastnameLineEdit() const;

    QLineEdit *getDialogBirthdateLineEdit() const;

    QLineEdit *getDialogHeightLineEdit() const;

    QLineEdit *getDialogWeightLineEdit() const;

    void clearLineEdits();

private slots:

    void on_InformationDialog_accepted();

private:
    Ui::InformationDialog *ui;

    QLineEdit *DialogNameLineEdit;
    QLineEdit *DialogSurnameLineEdit;
    QLineEdit *DialogLastnameLineEdit;
    QLineEdit *DialogBirthdateLineEdit;
    QLineEdit *DialogHeightLineEdit;
    QLineEdit *DialogWeightLineEdit;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QPoint cur_pos;
    QPoint new_pos;
};

#endif // INFORMATIONDIALOG_H
