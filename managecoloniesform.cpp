#include "managecoloniesform.h"
#include "beekeeperform.h"
ManageColoniesForm::ManageColoniesForm(const QString &login, QWidget *parent) : QWidget(parent) {


    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Manage colonies for " + login + "!", this);
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

    loadColoniesData(login);

    setLayout(mainLayout);
    setWindowTitle("Manage Colonies Form");
    resize(800, 600);
}

void ManageColoniesForm::closeEvent(QCloseEvent *event) {


    event->accept();
    //delete buttonLayout;
}


ManageColoniesForm::~ManageColoniesForm() {
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

void ManageColoniesForm::onEditButtonClicked() {
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

void ManageColoniesForm::onBackButtonClicked(const QString &login) {
    //BeekeeperForm *beekeeperForm = new BeekeeperForm(login);
    //beekeeperForm->show();
    this->close();
}


void ManageColoniesForm::onAddButtonClicked(const QString &login) {

    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT MAX(ID_Colony) FROM Bee_Colonies");
    if (query.next()) {
        int maxId = query.value(0).toInt();
        int newId = maxId + 1;


        int beekeeperId = getBeekeeperId(login);
        query = DatabaseManager::getInstance().executeQuery("SELECT ID_Hive FROM Hives WHERE ID_Beekeeper = :beekeeperId", {beekeeperId});
        QStringList hiveIds;
        while (query.next()) {
            hiveIds << query.value(0).toString();
        }

        if (hiveIds.isEmpty()) {
            QMessageBox::warning(this, "Error", "No hives available for the beekeeper!");
            return;
        }


        bool ok;
        QString selectedHiveId = QInputDialog::getItem(this, "Select Hive", "Choose a hive:", hiveIds, 0, false, &ok);
        if (ok && !selectedHiveId.isEmpty()) {
            int hiveId = selectedHiveId.toInt();


            int row = model->rowCount();
            model->insertRow(row);
            model->setData(model->index(row, 0), newId);
            model->setData(model->index(row, 1), hiveId);
            tableView->setCurrentIndex(model->index(row, 0));
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to get the maximum ID_Colony!");
    }
}



void ManageColoniesForm::onDeleteButtonClicked() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        model->submitAll();
    } else {
        QMessageBox::warning(this, "Error", "No row selected!");
    }
}

int ManageColoniesForm::getBeekeeperId(const QString &login) {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT ID_Beekeeper FROM Beekeepers WHERE FIO = :login", {login});
    if (!query.next()) {
        QMessageBox::warning(this, "Error", "Beekeeper not found in the database!");
        return -1;
    }
    return query.value(0).toInt();
}


void ManageColoniesForm::loadColoniesData(const QString &login) {
    int beekeeperId = getBeekeeperId(login);
    if (beekeeperId == -1) {
        return;
    }


    model->setTable("Bee_Colonies");
    model->setFilter("ID_Hive IN (SELECT ID_Hive FROM Hives WHERE ID_Beekeeper = " + QString::number(beekeeperId) + ")");
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "No colonies found for the beekeeper!");
    }
}

