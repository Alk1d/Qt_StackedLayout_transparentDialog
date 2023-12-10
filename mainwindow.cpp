#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QStackedLayout>
#include <QTableWidget>
#include <QMenuBar>
#include <QJsonDocument>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QHeaderView>
#include <informationdialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("kurs test"));
    Widget = new QWidget;
    MainWidget = new QWidget;
    setCentralWidget(MainWidget);
    information_dialog = new InformationDialog( this );
    information_dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    connect( information_dialog, SIGNAL(accepted()), SLOT( onDialogAccepted() ) );

    tableWidget = new QTableWidget;
    int row = 0;
    int column = 6;
    QStringList headers;
    headers << "Name" << "Surname" << "Last name" <<"Birth date" <<"Height" << "Weight";
    tableWidget->setRowCount(row);
    tableWidget->setColumnCount(column);
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* header = tableWidget->horizontalHeader();
     header->setSectionResizeMode(QHeaderView::Stretch);

    //buttons
    admitButton = new QPushButton(tr("Add"));
    deleteButton = new QPushButton(tr("Delete selected row"));

    //actions
    redactAct = new QAction("Editable table", this);
    redactAct->setCheckable(true);
    redactAct->setChecked(false);

    addDbAct = new QAction("Add JSON data base", this);
    //menu
    Menubar = new QMenuBar;
    Menu = menuBar()->addMenu("Menu");
    Menu->addAction(addDbAct);
    Menu->addAction(redactAct);


    //GridLayout for widget
    stackedLayout = new QStackedLayout;
    widgetLayout = new QGridLayout;
    widgetLayout->addWidget(Menubar, 0, 0);
    widgetLayout->addWidget(admitButton, 1, 0);
    widgetLayout->addWidget(deleteButton, 2, 0);
    widgetLayout->addWidget(tableWidget, 3, 0, 1, 2);
    Widget->setLayout(widgetLayout);

    stackedLayout->addWidget(Widget);
    stackedLayout->addWidget(information_dialog);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);

    MainWidget->setLayout(stackedLayout); // Information_dialog надо ограничить движение на размер Widget, сейчас выходит за рамки


    //connectors
    connect(admitButton, &QPushButton::clicked, this, &MainWindow::on_admitButtonClicked);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButtonClicked);
    connect(redactAct, &QAction::triggered, this, &MainWindow::redact);
    connect(addDbAct, &QAction::triggered, this, &MainWindow::on_addDbClicked);

    //creating json file
    QString path("kurs_test");
    QDir dir;

    if (!dir.exists(path))
        dir.mkpath(path);

    QFile file("AppData.json");
    dbPath = "AppData.json";
    file.open(QIODevice::ReadWrite);
    Db_reader();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Db_reader() // reading database into table
{
    file.setFileName(dbPath);
    row_counter = tableWidget->rowCount();
    if (file.open(QIODevice::ReadOnly))
    {
        db = QJsonDocument::fromJson(QByteArray(file.readAll()), &dbErr);
        file.close();

        if (dbErr.errorString().toInt() == QJsonParseError::NoError)
        {

            dbArr = QJsonValue(db.object().value("Cardfile")).toArray();
            for (int i = 0; i < dbArr.count(); i++)
            {

                if (row_counter <= i) tableWidget->insertRow(tableWidget->rowCount());
                tableWidget->setItem(i, 0, new QTableWidgetItem (dbArr.at(i).toObject().value("name").toString()));
                tableWidget->setItem(i, 1, new QTableWidgetItem (dbArr.at(i).toObject().value("surname").toString()));
                tableWidget->setItem(i, 2, new QTableWidgetItem (dbArr.at(i).toObject().value("lastname").toString()));
                tableWidget->setItem(i, 3, new QTableWidgetItem (dbArr.at(i).toObject().value("birthdate").toString()));
                tableWidget->setItem(i, 4, new QTableWidgetItem ((dbArr.at(i).toObject().value("height").toString())));
                tableWidget->setItem(i, 5, new QTableWidgetItem ((dbArr.at(i).toObject().value("weight").toString())));

            }
        }
    }
    else
    {
        QMessageBox::information(nullptr, "Database reader", "File is not opened");
    }
}



void MainWindow::on_admitButtonClicked() // clicking Add button
{
    information_dialog->show();


}
void MainWindow::onDialogAccepted()
{

        row_counter = tableWidget->rowCount();


    if (file.open(QIODevice::WriteOnly))
    {
        QVariantMap map;
        map.insert("name", information_dialog->getDialogNameLineEdit()->text());
        map.insert("surname", information_dialog->getDialogSurnameLineEdit()->text());
        map.insert("lastname", information_dialog->getDialogLastnameLineEdit()->text());
        map.insert("birthdate", information_dialog->getDialogBirthdateLineEdit()->text());
        map.insert("height", information_dialog->getDialogHeightLineEdit()->text());
        map.insert("weight", information_dialog->getDialogWeightLineEdit()->text());

        QJsonObject json = QJsonObject::fromVariantMap(map);
        if (db.isObject())
            WriteDb = db.object().value("Cardfile").toArray();
        else
        WriteDb = db.array();
        WriteDb.append(json);
        db.setArray(WriteDb);

        file.write("{\"Cardfile\":" +db.toJson() + "}");
        file.close();
    }
    else
    {
        QMessageBox::information(nullptr, "add button", "Database file is not opened");
        return;
    }

    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(row_counter,0,new QTableWidgetItem (information_dialog->getDialogNameLineEdit()->text()) );
    tableWidget->setItem(row_counter,1,new QTableWidgetItem (information_dialog->getDialogSurnameLineEdit()->text()) );
    tableWidget->setItem(row_counter,2,new QTableWidgetItem (information_dialog->getDialogLastnameLineEdit()->text()) );
    tableWidget->setItem(row_counter,3,new QTableWidgetItem (information_dialog->getDialogBirthdateLineEdit()->text()) );
    tableWidget->setItem(row_counter,4,new QTableWidgetItem (information_dialog->getDialogHeightLineEdit()->text()) );
    tableWidget->setItem(row_counter,5,new QTableWidgetItem (information_dialog->getDialogWeightLineEdit()->text()) );

    information_dialog->clearLineEdits();

}

void MainWindow::on_deleteButtonClicked() // clicking Delete selected row
{
    row_counter = tableWidget->currentRow();
    if (file.open(QIODevice::WriteOnly))
    {
        if (db.isObject())
            WriteDb = db.object().value("Cardfile").toArray();
        else
        WriteDb = db.array();
        WriteDb.removeAt(row_counter);
        db.setArray(WriteDb);
        file.write("{\"Cardfile\":" +db.toJson() + "}");
        file.close();
    }
    else
    {
        QMessageBox::information(nullptr, "delete button", "Database file is not opened");
        return;
    }
    tableWidget->removeRow(tableWidget->currentRow());
}

void MainWindow::redact() // clicking Editable table in Menu, doesn't add changes to database
{
    if (redactAct->isChecked() == true)
    {
        QMessageBox::information(nullptr, "Editable table","In this version of program changing the table will NOT change the database");
        tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    }
    else
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_addDbClicked()
{
    dbPath = QFileDialog::getOpenFileName(nullptr, "add json file", "", "*.json");
    file.setFileName(dbPath);
    if (file.isOpen() == false) return;
    while (tableWidget->rowCount() > 0) // clearing all rows in tableWidget
    {
        tableWidget->removeRow(0);
    }
    Db_reader();
}
