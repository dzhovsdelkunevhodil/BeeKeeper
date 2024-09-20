#include "buyform.h"

BuyForm::BuyForm(const QString &login, QWidget *parent) : QWidget(parent), login(login) {
    setStyleSheet("QWidget { background-color: #000000; }");

    layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Products!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");

    buyButton = new QPushButton("Buy", this);
    buyButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    buyButton->setFixedWidth(200);

    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    backButton->setFixedWidth(200);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);
    tableView->setStyleSheet("QTableView { background-color: #000000; color: #FFA500; }"
                             "QTableView::item { background-color: #000000; color: #FFA500; }"
                             "QHeaderView::section { background-color: #FFA500; color: #000000; }");

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    layout->addWidget(buyButton);
    layout->addWidget(backButton);

    connect(buyButton, &QPushButton::clicked, this, [this, login]() { onBuyButtonClicked(login); });
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
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText("There are no products to buy");
        messageBox.setWindowTitle("No");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
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
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Client not found in the database!");
        messageBox.setWindowTitle("Error");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
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
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText("There are no products to buy");
        messageBox.setWindowTitle("No");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
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
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("Update failed");
            messageBox.setWindowTitle("Error");
            messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                     "QMessageBox QLabel { color: #FFA500; }"
                                     "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
            messageBox.exec();
            return;
        }

        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText("Покупка успешно завершена!");
        messageBox.setWindowTitle("Успех");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();

        loadProductsData();
    }
}
