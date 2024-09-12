#include "editbeekeeperform.h"

EditBeekeeperForm::EditBeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent), login(login) {
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:/BD/DB.accdb;");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to connect to the database!");
        return;
    }
    QVBoxLayout *layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Edit for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    editDataButton = new QPushButton("Edit Data", this);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    layout->addWidget(editDataButton);


    connect(editDataButton, &QPushButton::clicked, this, &EditBeekeeperForm::onEditDataButtonClicked);

    loadBeekeeperData(login);

    setLayout(layout);
    setWindowTitle("Beekeeper Form");
}

EditBeekeeperForm::~EditBeekeeperForm() {
    delete welcomeLabel;
    delete editDataButton;

    delete tableView;
    delete model;
    db.close();

}

void EditBeekeeperForm::onEditDataButtonClicked() {
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

void EditBeekeeperForm::loadBeekeeperData(const QString &login) {

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
