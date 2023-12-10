#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "informationdialog.h"
#include "qjsondocument.h"
#include "qstackedlayout.h"
#include <QLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QAction>
#include <QLabel>
#include <QMenuBar>

#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
#include <QJsonParseError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *Widget;
    QTableWidget *tableWidget;
    QWidget *MainWidget;

    QLineEdit *nameLineEdit;
    QLineEdit *surnameLineEdit;
    QLineEdit *lastnameLineEdit;
    QLineEdit *birthdateLineEdit;
    QLineEdit *heightLineEdit;
    QLineEdit *weightLineEdit;

    QLabel *nameLabel;
    QLabel *surnameLabel;
    QLabel *lastnameLabel;
    QLabel *birthdateLabel;
    QLabel *heightLabel;
    QLabel *weightLabel;

    QPushButton *admitButton;
    QPushButton *deleteButton;

    QGroupBox *parametresGroupbox;
    QGroupBox *fullnameGroupbox;

    QGridLayout *fullnameLayout;
    QGridLayout *parametresLayout;
    QGridLayout *widgetLayout;

    QStackedLayout *stackedLayout;

    QAction *redactAct;
    QAction *addDbAct;
    QMenuBar *Menubar;
    QMenu *Menu;

    InformationDialog* information_dialog;

    QJsonDocument db;
    QJsonArray dbArr;
    QJsonArray WriteDb;
    QJsonParseError dbErr;
    QString dbPath;
    QFile file;

    int row_counter;
    void Db_reader();



public slots:
    void on_admitButtonClicked();
    void onDialogAccepted();
    void on_deleteButtonClicked();
    void redact();
    void on_addDbClicked();
};
#endif // MAINWINDOW_H
