#include "editbeekeeperform.h"

EditBeekeeperForm::EditBeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent) {

    layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Edit for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    editDataButton = new QPushButton("Edit Data", this);
    backButton = new QPushButton("Back", this);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    layout->addWidget(editDataButton);
    layout->addWidget(backButton);

    connect(editDataButton, &QPushButton::clicked, this, &onEditDataButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &onBackButtonClicked);

    loadBeekeeperData(login);

    setLayout(layout);
    setWindowTitle("Edit Beekeeper Form");
    resize(800, 600);
}

EditBeekeeperForm::~EditBeekeeperForm() {
    delete welcomeLabel;
    delete editDataButton;
    delete backButton;
    delete layout;
    delete tableView;
    delete model;
}

void EditBeekeeperForm::onBackButtonClicked() {
    this->close();
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

void EditBeekeeperForm::closeEvent(QCloseEvent *event) {

    event->accept();
}
