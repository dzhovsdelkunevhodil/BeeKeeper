#include "buyform.h"

BuyForm::BuyForm(const QString &login, QWidget *parent): QWidget(parent), login(login) {
    layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Products!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    buyButton = new QPushButton("Buy", this);
    backButton = new QPushButton("Back", this);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    layout->addWidget(buyButton);
    layout->addWidget(backButton);

    connect(buyButton, &QPushButton::clicked, this, [this, login]() {onBuyButtonClicked(login);});
    connect(backButton, &QPushButton::clicked, this, &BuyForm::onBackButtonClicked);

    loadProductsData();

    setLayout(layout);
    setWindowTitle("Products Form");
    resize(800, 600);

}

void BuyForm::closeEvent(QCloseEvent *event) {

    event->accept();
}

BuyForm::~BuyForm() {
    delete welcomeLabel;
    delete buyButton;
    delete backButton;
    delete tableView;
    delete model;
    delete layout;
}

void BuyForm::loadProductsData() {

    model->setTable("Honey_Collections");
    model->setFilter("ID_Client = 7");
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No", "There are no products to buy");
    }

    tableView->setModel(model);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void BuyForm::onBackButtonClicked() {

    this->close();
}

int BuyForm::getClientId(const QString &login) {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT ID_Client FROM Clients WHERE FIO = :login", {login});
    if (!query.next()) {
        QMessageBox::warning(this, "Error", "Client not found in the database!");
        return -1;
    }
    return query.value(0).toInt();
}

void BuyForm::onBuyButtonClicked(const QString &login) {

    int clientid = getClientId(login);
    if (clientid == -1) {
        return;
    }


    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT ID_HC FROM Honey_Collections WHERE ID_Client = 7");
    QStringList HCIds;
    while (query.next()) {
        HCIds << query.value(0).toString();
    }

    if (HCIds.isEmpty()) {
        QMessageBox::information(this, "No", "There are no products to buy");
        return;
    }


    bool ok;
    QString selectedHCId = QInputDialog::getItem(this, "Select Product", "Choose a Product id:", HCIds, 0, false, &ok);
    if (ok && !selectedHCId.isEmpty()) {
        QSqlQuery query2;
        query2.prepare("UPDATE Honey_Collections SET ID_Client = :clientid WHERE ID_HC = :selectedHCId");
        query2.bindValue(":clientid", clientid);
        query2.bindValue(":selectedHCId", selectedHCId);

        if (!query2.exec()) {
            QMessageBox::warning(this, "Error", "Update failed");
            return;
        }

        QMessageBox::information(this, "Успех", "Покупка успешно завершена!");
        loadProductsData();

    }
}
