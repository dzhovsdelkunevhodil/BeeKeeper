#include "manageHCform.h"


ManageHCForm::ManageHCForm(const QString &login, QWidget *parent) : QWidget(parent) {

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

    connect(editDataButton, &QPushButton::clicked, this, &onEditButtonClicked);
    connect(addDataButton, &QPushButton::clicked, this, [this, login]() { onAddButtonClicked(login);});
    connect(deleteDataButton, &QPushButton::clicked, this, &onDeleteButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &onBackButtonClicked);

    loadHCData(login);

    setLayout(mainLayout);
    setWindowTitle("Manage Hives Form");
    resize(800, 600);
}

void ManageHCForm::closeEvent(QCloseEvent *event) {
    event->accept();

}


ManageHCForm::~ManageHCForm() {
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

void ManageHCForm::onEditButtonClicked() {
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

void ManageHCForm::onBackButtonClicked() {

    this->close();
}

void ManageHCForm::onAddButtonClicked(const QString &login) {

    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT MAX(ID_HC) FROM Honey_Collections");
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


            query = DatabaseManager::getInstance().executeQuery("SELECT ID_Colony FROM Bee_Colonies WHERE ID_Hive = :hiveId", {hiveId});
            QStringList colonyIds;
            while (query.next()) {
                colonyIds << query.value(0).toString();
            }

            if (colonyIds.isEmpty()) {
                QMessageBox::warning(this, "Error", "No colonies available for the selected hive!");
                return;
            }


            QString selectedColonyId = QInputDialog::getItem(this, "Select Colony", "Choose a colony:", colonyIds, 0, false, &ok);
            if (ok && !selectedColonyId.isEmpty()) {
                int colonyId = selectedColonyId.toInt();


                query = DatabaseManager::getInstance().executeQuery("SELECT ID_Client FROM Clients");
                QStringList clientIds;
                //clientIds.append("0");
                while (query.next()) {
                    clientIds << query.value(0).toString();
                }

                if (clientIds.isEmpty()) {
                    QMessageBox::warning(this, "Error", "No clients available!");
                    return;
                }


                QString selectedClientId = QInputDialog::getItem(this, "Select Client", "Choose a client (7 - without client):", clientIds, 0, false, &ok);
                if (ok && !selectedClientId.isEmpty()) {
                    int clientId = selectedClientId.toInt();


                    int row = model->rowCount();
                    model->insertRow(row);
                    model->setData(model->index(row, 0), newId);
                    model->setData(model->index(row, 1), beekeeperId);
                    model->setData(model->index(row, 2), hiveId);
                    model->setData(model->index(row, 3), colonyId);
                    model->setData(model->index(row, 4), clientId);
                    tableView->setCurrentIndex(model->index(row, 0));
                }
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to get the maximum ID_HC!");
    }
}



void ManageHCForm::onDeleteButtonClicked() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        model->submitAll();
    } else {
        QMessageBox::warning(this, "Error", "No row selected!");
    }
}

int ManageHCForm::getBeekeeperId(const QString &login) {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT ID_Beekeeper FROM Beekeepers WHERE FIO = :login", {login});
    if (!query.next()) {
        QMessageBox::warning(this, "Error", "Beekeeper not found in the database!");
        return -1;
    }
    return query.value(0).toInt();
}

void ManageHCForm::loadHCData(const QString &login) {
    int beekeeperId = getBeekeeperId(login);
    if (beekeeperId == -1) {
        return;
    }


    model->setTable("Honey_Collections");
    model->setFilter("ID_Beekeeper = " + QString::number(beekeeperId));
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "No HCollections found for the beekeeper!");
    }
}
