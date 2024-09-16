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
