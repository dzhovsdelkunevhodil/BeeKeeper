#include "orderhistoryform.h"
OrderHistoryForm::OrderHistoryForm(const QString &login, QWidget *parent) : QWidget(parent) {

    setStyleSheet("QWidget { background-color: #000000; }"
                  "QLineEdit { background-color: #000000; color: #FFA500; }"
                  "QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }"
                  "QPushButton:hover { background-color: #FFD700; }");

    layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Order History for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");

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
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &OrderHistoryForm::onBackButtonClicked);

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

}
void OrderHistoryForm::onBackButtonClicked() {
    this->close();
}



int OrderHistoryForm::getClientId(const QString &login) {
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

void OrderHistoryForm::loadOHData(const QString &login) {
    int clientid = getClientId(login);
    if (clientid == -1) {
        return;
    }

    model->setTable("Honey_Collections");
    model->setFilter("ID_Client = " + QString::number(clientid));
    model->select();

    if (model->rowCount() == 0) {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("No HCollections found for the client!");
        messageBox.setWindowTitle("Error");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
    }
}
