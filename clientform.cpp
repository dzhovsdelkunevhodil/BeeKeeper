#include "clientform.h"
#include "editclientform.h"
#include "orderhistoryform.h"
#include "buyform.h"
ClientForm::ClientForm(const QString &login, QWidget *parent) : QWidget(parent) {
    if (!DatabaseManager::getInstance().connectToDatabase()) {
        return;
    }

    setWindowTitle("Client Form");
    setFixedSize(800, 600);

    layout = new QVBoxLayout(this);

    orderHistoryButton = new QPushButton("Order history", this);
    editDataButton = new QPushButton("Edit Data", this);
    buyButton = new QPushButton("Buy", this);


    // orderHistoryButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border: none; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
    // editDataButton->setStyleSheet("QPushButton { background-color: #008CBA; color: white; border: none; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
    // buyButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; border: none; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");

    connect(orderHistoryButton, &QPushButton::clicked, this, [this, login]() { showOrderHistory(login); });
    connect(editDataButton, &QPushButton::clicked, this, [this, login]() { editData(login); });
    connect(buyButton, &QPushButton::clicked, this, [this, login]() {buy(login); });

    layout->addWidget(orderHistoryButton);
    layout->addWidget(editDataButton);
    layout->addWidget(buyButton);

    setLayout(layout);
}

void ClientForm::closeEvent(QCloseEvent *event) {

    event->accept();
}

ClientForm::~ClientForm() {
    delete orderHistoryButton;
    delete editDataButton;
    delete buyButton;
    delete layout;
    DatabaseManager::getInstance().closeDatabase();
}
void ClientForm::showOrderHistory(const QString &login) {
    OrderHistoryForm *orderHform = new OrderHistoryForm(login);
    orderHform->show();
}

void ClientForm::editData(const QString &login) {
    EditClientForm *editCform = new EditClientForm(login);
    editCform->show();
}

void ClientForm::buy(const QString &login) {
    BuyForm *buyform = new BuyForm(login);
    buyform->show();
}
