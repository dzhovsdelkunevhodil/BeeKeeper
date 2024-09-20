#include "allclientform.h"

AllClientForm::AllClientForm(QWidget *parent) : QWidget(parent) {

    setStyleSheet("QWidget { background-color: #000000; }"
                  "QLineEdit { background-color: #000000; color: #FFA500; }"
                  "QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }"
                  "QPushButton:hover { background-color: #FFD700; }");

    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Clients", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFA500;");

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);
    tableView->setStyleSheet("QTableView { background-color: #000000; color: #FFA500; }"
                             "QTableView::item { background-color: #000000; color: #FFA500; }"
                             "QHeaderView::section { background-color: #FFA500; color: #000000; }");

    buttonLayout = new QVBoxLayout();

    editDataButton = new QPushButton("Save Data", this);
    editDataButton->setFixedWidth(200);

    addDataButton = new QPushButton("Add Data", this);
    addDataButton->setFixedWidth(200);

    deleteDataButton = new QPushButton("Delete Data", this);
    deleteDataButton->setFixedWidth(200);

    backButton = new QPushButton("Back", this);
    backButton->setFixedWidth(200);

    phoneDelegate = new PhoneDelegate(this);
    emailDelegate = new EmailDelegate(this);

    buttonLayout->addWidget(editDataButton);
    buttonLayout->addWidget(addDataButton);
    buttonLayout->addWidget(deleteDataButton);
    buttonLayout->addWidget(backButton);

    mainLayout->addWidget(welcomeLabel);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    connect(editDataButton, &QPushButton::clicked, this, &AllClientForm::onEditButtonClicked);
    connect(addDataButton, &QPushButton::clicked, this, &AllClientForm::onAddButtonClicked);
    connect(deleteDataButton, &QPushButton::clicked, this, &AllClientForm::onDeleteButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &AllClientForm::onBackButtonClicked);

    loadClientsData();

    setLayout(mainLayout);
    setWindowTitle("Clients");
    resize(800, 600);
}


void AllClientForm::closeEvent(QCloseEvent *event) {
    event->accept();
}

AllClientForm::~AllClientForm() {
    delete backButton;
    delete editDataButton;
    delete addDataButton;
    delete deleteDataButton;
    delete buttonLayout;
    delete welcomeLabel;
    delete tableView;
    delete mainLayout;
    delete model;
    delete phoneDelegate;
    delete emailDelegate;
}

void AllClientForm::onEditButtonClicked() {
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

void AllClientForm::onBackButtonClicked() {
    this->close();
}

void AllClientForm::onAddButtonClicked() {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT MAX(ID_Client) FROM Clients");
    if (query.next()) {
        int maxId = query.value(0).toInt();
        int newId = maxId + 1;

        int row = model->rowCount();
        model->insertRow(row);
        model->setData(model->index(row, 0), newId);
        tableView->setCurrentIndex(model->index(row, 0));
    } else {
        showMessageBox("Error", "Failed to get the maximum ID_Client!", QMessageBox::Warning);
    }
}

void AllClientForm::onDeleteButtonClicked() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        model->submitAll();
    } else {
        showMessageBox("Error", "No row selected!", QMessageBox::Warning);
    }
}

void AllClientForm::loadClientsData() {
    model->setTable("Clients");
    model->select();

    if (model->rowCount() == 0) {
        showMessageBox("Error", "No clients found!", QMessageBox::Warning);
    }
    int phoneColumn = model->fieldIndex("Phone");
    if (phoneColumn != -1) {
        tableView->setItemDelegateForColumn(phoneColumn, phoneDelegate);
    }

    int emailColumn = model->fieldIndex("Email");
    if (emailColumn != -1) {
        tableView->setItemDelegateForColumn(emailColumn, emailDelegate);
    }
}

void AllClientForm::showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon) {
    QMessageBox messageBox;
    messageBox.setIcon(icon);
    messageBox.setText(message);
    messageBox.setWindowTitle(title);
    messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                             "QMessageBox QLabel { color: #FFA500; }"
                             "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
    messageBox.exec();
}
