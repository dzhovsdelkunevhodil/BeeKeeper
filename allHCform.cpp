#include "allHCform.h"

AllHCForm::AllHCForm(QWidget *parent) : QWidget(parent) {

    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Honey Collections", this);
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

    connect(editDataButton, &QPushButton::clicked, this, &onEditButtonClicked);
    connect(addDataButton, &QPushButton::clicked, this, &onAddButtonClicked);
    connect(deleteDataButton, &QPushButton::clicked, this, &onDeleteButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &onBackButtonClicked);

    loadHCData();

    setLayout(mainLayout);
    setWindowTitle("Honey Collections");
    resize(800, 600);
}

void AllHCForm::closeEvent(QCloseEvent *event) {
    event->accept();
    //delete buttonLayout;
}


AllHCForm::~AllHCForm() {
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

void AllHCForm::onEditButtonClicked() {
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

void AllHCForm::onBackButtonClicked() {

    this->close();
}

void AllHCForm::onAddButtonClicked() {

    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT MAX(ID_HC) FROM Honey_Collections");
    if (query.next()) {
        int maxId = query.value(0).toInt();
        int newId = maxId + 1;


        int row = model->rowCount();
        model->insertRow(row);
        model->setData(model->index(row, 0), newId);
        tableView->setCurrentIndex(model->index(row, 0));
    } else {
        QMessageBox::warning(this, "Error", "Failed to get the maximum ID_HC!");
    }
}

void AllHCForm::onDeleteButtonClicked() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        model->submitAll();
    } else {
        QMessageBox::warning(this, "Error", "No row selected!");
    }
}

void AllHCForm::loadHCData() {

    model->setTable("Honey_Collections");
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "No HCollections found!");
    }
}

