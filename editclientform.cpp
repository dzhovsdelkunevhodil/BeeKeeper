#include "editclientform.h"

EditClientForm::EditClientForm(const QString &login, QWidget *parent) : QWidget(parent) {

    setStyleSheet("QWidget { background-color: #000000; }"
                  "QLineEdit { background-color: #000000; color: #FFA500; }"
                  "QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }"
                  "QPushButton:hover { background-color: #FFD700; }");

    layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Edit for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");

    editDataButton = new QPushButton("Save Data", this);
    editDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    editDataButton->setFixedWidth(200);

    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    backButton->setFixedWidth(200);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);
    tableView->setStyleSheet("QTableView { background-color: #000000; color: #FFA500; }"
                             "QTableView::item { background-color: #000000; color: #FFA500; }"
                             "QHeaderView::section { background-color: #FFA500; color: #000000; }");

    phoneDelegate = new PhoneDelegate(this);
    emailDelegate = new EmailDelegate(this);

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    layout->addWidget(editDataButton);
    layout->addWidget(backButton);

    connect(editDataButton, &QPushButton::clicked, this, &EditClientForm::onEditDataButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &EditClientForm::onBackButtonClicked);

    loadClientData(login);

    setLayout(layout);
    setWindowTitle("Edit Client Form");
    resize(800, 600);
}

EditClientForm::~EditClientForm() {
    delete welcomeLabel;
    delete editDataButton;
    delete backButton;
    delete layout;
    delete tableView;
    delete model;
    delete phoneDelegate;
    delete emailDelegate;
}

void EditClientForm::onBackButtonClicked() {

    this->close();
}

void EditClientForm::onEditDataButtonClicked() {
    if (model->isDirty()) {
        if (model->submitAll()) {
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Information);
            messageBox.setText("Data saved successfully!");
            messageBox.setWindowTitle("Success");
            messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                     "QMessageBox QLabel { color: #FFA500; }"
                                     "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
            messageBox.exec();
        } else {
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("Failed to save data!");
            messageBox.setWindowTitle("Error");
            messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                     "QMessageBox QLabel { color: #FFA500; }"
                                     "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
            messageBox.exec();
        }
    } else {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText("No changes to save.");
        messageBox.setWindowTitle("Info");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
    }
}

void EditClientForm::loadClientData(const QString &login) {
    model->setTable("Clients");
    model->setFilter("FIO = '" + login + "'");
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Clients not found in the database!");
        messageBox.setWindowTitle("Error");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
    }
    int phoneColumn = model->fieldIndex("Phone");
    if (phoneColumn != -1) {
        tableView->setItemDelegateForColumn(phoneColumn, phoneDelegate);
    }

    int emailColumn = model->fieldIndex("Email");
    if (emailColumn != -1) {
        tableView->setItemDelegateForColumn(emailColumn, emailDelegate);
    }
}
void EditClientForm::closeEvent(QCloseEvent *event) {

    event->accept();
}
