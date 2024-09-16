#include "orderhistoryform.h"
OrderHistoryForm::OrderHistoryForm(const QString &login, QWidget *parent) : QWidget(parent) {

    layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Order History for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    //editDataButton = new QPushButton("Edit Data", this);
    backButton = new QPushButton("Back", this);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    //layout->addWidget(editDataButton);
    layout->addWidget(backButton);

    //connect(editDataButton, &QPushButton::clicked, this, &onEditDataButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &onBackButtonClicked);

    loadOHData(login);

    setLayout(layout);
    setWindowTitle("Order History Form");
    resize(800, 600);
}

OrderHistoryForm::~OrderHistoryForm() {
    delete welcomeLabel;
    delete layout;
    delete backButton;
    delete tableView;
    delete model;
}
void OrderHistoryForm::closeEvent(QCloseEvent *event) {
    event->accept();
    //delete buttonLayout;
}
void OrderHistoryForm::onBackButtonClicked() {
    this->close();
}



int OrderHistoryForm::getClientId(const QString &login) {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT ID_Client FROM Clients WHERE FIO = :login", {login});
    if (!query.next()) {
        QMessageBox::warning(this, "Error", "Client not found in the database!");
        return -1;
    }
    return query.value(0).toInt();
}

void OrderHistoryForm::loadOHData(const QString &login) {
    int clientid = getClientId(login);
    if (clientid == -1) {
        return;
    }


    model->setTable("Honey_Collections");
    model->setFilter("ID_Client = " + QString::number(clientid));
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "No HCollections found for the client!");
    }
}
