#include "editbeekeeperform.h"

EditBeekeeperForm::EditBeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent) {

    setStyleSheet("QWidget { background-color: #000000; }"
                  "QLineEdit { background-color: #000000; color: #FFA500; }"
                  "QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }"
                  "QPushButton:hover { background-color: #FFD700; }");

    layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Edit for " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");

    editDataButton = new QPushButton("Save Data", this);
    editDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    editDataButton->setFixedWidth(200);

    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    backButton->setFixedWidth(200);

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);
    tableView->setStyleSheet("QTableView { background-color: #000000; color: #FFA500; }"
                             "QTableView::item { background-color: #000000; color: #FFA500; }"
                             "QHeaderView::section { background-color: #FFA500; color: #000000; }");


    phoneDelegate = new PhoneDelegate(this);
    emailDelegate = new EmailDelegate(this);

    layout->addWidget(welcomeLabel);
    layout->addWidget(tableView);
    layout->addWidget(editDataButton);
    layout->addWidget(backButton);

    connect(editDataButton, &QPushButton::clicked, this, &EditBeekeeperForm::onEditDataButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &EditBeekeeperForm::onBackButtonClicked);

    loadBeekeeperData(login);

    setLayout(layout);
    setWindowTitle("Edit Beekeeper Form");
    resize(800, 600);
}

EditBeekeeperForm::~EditBeekeeperForm() {
    delete welcomeLabel;
    delete editDataButton;
    delete backButton;
    delete layout;
    delete tableView;
    delete model;
    delete phoneDelegate;
    delete emailDelegate;
}

void EditBeekeeperForm::onBackButtonClicked() {
    this->close();
}

void EditBeekeeperForm::onEditDataButtonClicked() {
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

void EditBeekeeperForm::loadBeekeeperData(const QString &login) {
    model->setTable("Beekeepers");
    model->setFilter("FIO = '" + login + "'");
    model->select();

    if (model->rowCount() == 0) {
        showMessageBox("Error", "Beekeeper not found in the database!", QMessageBox::Warning);
    }


    int phoneColumn = model->fieldIndex("Телефон");
    if (phoneColumn != -1) {
        tableView->setItemDelegateForColumn(phoneColumn, phoneDelegate);
    }

    int emailColumn = model->fieldIndex("Почта");
    if (emailColumn != -1) {
        tableView->setItemDelegateForColumn(emailColumn, emailDelegate);
    }
}

void EditBeekeeperForm::showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon) {
    QMessageBox messageBox;
    messageBox.setIcon(icon);
    messageBox.setText(message);
    messageBox.setWindowTitle(title);
    messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                             "QMessageBox QLabel { color: #FFA500; }"
                             "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
    messageBox.exec();
}

void EditBeekeeperForm::closeEvent(QCloseEvent *event) {
    event->accept();
}
