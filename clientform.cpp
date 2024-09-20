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


    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap("C:/BD/background.png").scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());
    backgroundLabel->lower();


    QWidget *blackRect = new QWidget(this);
    blackRect->setStyleSheet("background-color: #000000;");
    blackRect->setGeometry(100, 100, 600, 400);

    QVBoxLayout *layout = new QVBoxLayout(blackRect);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *loginLabel = new QLabel(login, this);
    loginLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #FFA500;");
    loginLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(loginLabel);

    orderHistoryButton = new QPushButton("Order history", this);
    orderHistoryButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    orderHistoryButton->setFixedWidth(200);

    editDataButton = new QPushButton("Edit Data", this);
    editDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    editDataButton->setFixedWidth(200);

    buyButton = new QPushButton("Buy", this);
    buyButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    buyButton->setFixedWidth(200);

    connect(orderHistoryButton, &QPushButton::clicked, this, [this, login]() { showOrderHistory(login); });
    connect(editDataButton, &QPushButton::clicked, this, [this, login]() { editData(login); });
    connect(buyButton, &QPushButton::clicked, this, [this, login]() { buy(login); });

    layout->addWidget(orderHistoryButton);
    layout->addWidget(editDataButton);
    layout->addWidget(buyButton);

    blackRect->setLayout(layout);
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
