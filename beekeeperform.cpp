#include "beekeeperform.h"

BeekeeperForm::BeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent), login(login) {
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:/BD/DB.accdb;");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to connect to the database!");
        return;
    }
    QVBoxLayout *layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Welcome, " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    editDataButton = new QPushButton("Edit Data", this);
    button4 = new QPushButton("Button 4", this);
    button5 = new QPushButton("Button 5", this);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    layout->addWidget(editDataButton);
    layout->addWidget(button4);
    layout->addWidget(button5);

    connect(editDataButton, &QPushButton::clicked, this, &BeekeeperForm::onEditDataButtonClicked);

    loadBeekeeperData(login);

    setLayout(layout);
    setWindowTitle("Beekeeper Form");
}

BeekeeperForm::~BeekeeperForm() {
    delete welcomeLabel;
    delete editDataButton;
    delete button4;
    delete button5;
    delete tableView;
    delete model;
    db.close();

}

void BeekeeperForm::onEditDataButtonClicked() {
    if (model->isDirty()) {
        if (model->submitAll()) {
            QMessageBox::information(this, "Success", "Data saved successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save data!");
        }
    } else {
        QMessageBox::information(this, "Info", "No changes to save.");
    }
}

void BeekeeperForm::loadBeekeeperData(const QString &login) {

    model->setTable("Beekeepers");
    model->setFilter("FIO = '" + login + "'");
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "Beekeeper not found in the database!");
    }

}

//Изменение своих данных

//Добавление/удаление/изменение
//улья, за которым назначен
//ответственным.

//Добавление/удаление/изменение
//пчелиной колонии, за которой через
//улей назначен ответственным.

//Добавление/удаление/изменение
//сбора меда, за которым назначен
//ответственным.

//Просмотр всех пчеловодов, всех
//сборов меда, пчелиных семей, ульев.
