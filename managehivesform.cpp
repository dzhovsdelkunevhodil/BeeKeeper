#include "managehivesform.h"
#include "beekeeperform.h"
ManageHivesForm::ManageHivesForm(const QString &login, QWidget *parent) : QWidget(parent) {

    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Manage hives for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);

    buttonLayout = new QHBoxLayout();

    editDataButton = new QPushButton("Edit Data", this);
    addDataButton = new QPushButton("Add Data", this);
    deleteDataButton = new QPushButton("Delete Data", this);
    backButton = new QPushButton("Back", this);

    buttonLayout->addWidget(editDataButton);
    buttonLayout->addWidget(addDataButton);
    buttonLayout->addWidget(deleteDataButton);
    buttonLayout->addWidget(backButton);

    mainLayout->addWidget(welcomeLabel);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    connect(editDataButton, &QPushButton::clicked, this,onEditButtonClicked);
    connect(addDataButton, &QPushButton::clicked, this, [this, login]() { onAddButtonClicked(login);});
    connect(deleteDataButton, &QPushButton::clicked, this, onDeleteButtonClicked);
    connect(backButton, &QPushButton::clicked, this, [this, login]() { onBackButtonClicked(login); });

    loadHivesData(login);

    setLayout(mainLayout);
    setWindowTitle("Manage Hives Form");
    resize(800, 600);
}

void ManageHivesForm::closeEvent(QCloseEvent *event) {
    event->accept();
    //delete buttonLayout;
}


ManageHivesForm::~ManageHivesForm() {
    delete backButton;
    delete editDataButton;
    delete addDataButton;
    delete deleteDataButton;
    delete buttonLayout;
    delete welcomeLabel;
    delete tableView;

    delete mainLayout;
    delete model;
    //

}

void ManageHivesForm::onEditButtonClicked() {
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

void ManageHivesForm::onBackButtonClicked(const QString &login) {
    //BeekeeperForm *beekeeperForm = new BeekeeperForm(login);
   // beekeeperForm->show();
    this->close();
}

void ManageHivesForm::onAddButtonClicked(const QString &login) {

    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT MAX(ID_Hive) FROM Hives");
    if (query.next()) {
        int maxId = query.value(0).toInt();
        int newId = maxId + 1;

        int beekeeperId = getBeekeeperId(login);

        int row = model->rowCount();
        model->insertRow(row);
        model->setData(model->index(row, 0), newId);
        model->setData(model->index(row, 1), beekeeperId);
        tableView->setCurrentIndex(model->index(row, 0));
    } else {
        QMessageBox::warning(this, "Error", "Failed to get the maximum ID_Hive!");
    }
}

void ManageHivesForm::onDeleteButtonClicked() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        model->submitAll();
    } else {
        QMessageBox::warning(this, "Error", "No row selected!");
    }
}

int ManageHivesForm::getBeekeeperId(const QString &login) {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT ID_Beekeeper FROM Beekeepers WHERE FIO = :login", {login});
    if (!query.next()) {
        QMessageBox::warning(this, "Error", "Beekeeper not found in the database!");
        return -1;
    }
    return query.value(0).toInt();
}

void ManageHivesForm::loadHivesData(const QString &login) {
    int beekeeperId = getBeekeeperId(login);
    if (beekeeperId == -1) {
        return;
    }


    model->setTable("Hives");
    model->setFilter("ID_Beekeeper = " + QString::number(beekeeperId));
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "No hives found for the beekeeper!");
    }
}


