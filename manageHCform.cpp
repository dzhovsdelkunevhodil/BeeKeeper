#include "manageHCform.h"

ManageHCForm::ManageHCForm(const QString &login, QWidget *parent) : QWidget(parent) {

    setStyleSheet("QWidget { background-color: #000000; }"
                  "QLineEdit { background-color: #000000; color: #FFA500; }"
                  "QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }"
                  "QPushButton:hover { background-color: #FFD700; }");
    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Manage hives for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);
    tableView->setStyleSheet("QTableView { background-color: #000000; color: #FFA500; }"
                             "QTableView::item { background-color: #000000; color: #FFA500; }"
                             "QHeaderView::section { background-color: #FFA500; color: #000000; }");

    buttonLayout = new QHBoxLayout();

    editDataButton = new QPushButton("Save Data", this);
    editDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    editDataButton->setFixedWidth(200);

    addDataButton = new QPushButton("Add Data", this);
    addDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    addDataButton->setFixedWidth(200);

    deleteDataButton = new QPushButton("Delete Data", this);
    deleteDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    deleteDataButton->setFixedWidth(200);

    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    backButton->setFixedWidth(200);

    buttonLayout->addWidget(editDataButton);
    buttonLayout->addWidget(addDataButton);
    buttonLayout->addWidget(deleteDataButton);
    buttonLayout->addWidget(backButton);

    mainLayout->addWidget(welcomeLabel);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    connect(editDataButton, &QPushButton::clicked, this, &ManageHCForm::onEditButtonClicked);
    connect(addDataButton, &QPushButton::clicked, this, [this, login]() { onAddButtonClicked(login); });
    connect(deleteDataButton, &QPushButton::clicked, this, &ManageHCForm::onDeleteButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &ManageHCForm::onBackButtonClicked);

    loadHCData(login);

    setLayout(mainLayout);
    setWindowTitle("Manage Hives Form");
    resize(800, 600);
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
}

void ManageHCForm::onBackButtonClicked() {
    this->close();
}

void ManageHCForm::onEditButtonClicked() {
    if (model->isDirty()) {
        if (model->submitAll()) {
            showMessageBox("Success", "Data saved successfully!", QMessageBox::Information);
        } else {
            showMessageBox("Error", "Failed to save data!", QMessageBox::Warning);
        }
    } else {
        showMessageBox("Info", "No changes to save.", QMessageBox::Information);
    }
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
            showMessageBox("Error", "No hives available for the beekeeper!", QMessageBox::Warning);
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
                showMessageBox("Error", "No colonies available for the selected hive!", QMessageBox::Warning);
                return;
            }

            QString selectedColonyId = QInputDialog::getItem(this, "Select Colony", "Choose a colony:", colonyIds, 0, false, &ok);
            if (ok && !selectedColonyId.isEmpty()) {
                int colonyId = selectedColonyId.toInt();

                query = DatabaseManager::getInstance().executeQuery("SELECT ID_Client FROM Clients");
                QStringList clientIds;
                while (query.next()) {
                    clientIds << query.value(0).toString();
                }

                if (clientIds.isEmpty()) {
                    showMessageBox("Error", "No clients available!", QMessageBox::Warning);
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
        showMessageBox("Error", "Failed to get the maximum ID_HC!", QMessageBox::Warning);
    }
}

void ManageHCForm::onDeleteButtonClicked() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        model->submitAll();
    } else {
        showMessageBox("Error", "No row selected!", QMessageBox::Warning);
    }
}

int ManageHCForm::getBeekeeperId(const QString &login) {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT ID_Beekeeper FROM Beekeepers WHERE FIO = :login", {login});
    if (!query.next()) {
        showMessageBox("Error", "Beekeeper not found in the database!", QMessageBox::Warning);
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
        showMessageBox("Error", "No HCollections found for the beekeeper!", QMessageBox::Warning);
    }
}

void ManageHCForm::showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon) {
    QMessageBox messageBox;
    messageBox.setIcon(icon);
    messageBox.setText(message);
    messageBox.setWindowTitle(title);
    messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                             "QMessageBox QLabel { color: #FFA500; }"
                             "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
    messageBox.exec();
}

void ManageHCForm::closeEvent(QCloseEvent *event) {
    event->accept();
}
