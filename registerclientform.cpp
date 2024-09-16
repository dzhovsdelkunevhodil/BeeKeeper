#include "registerclientform.h"
#include "databasemanager.h"
RegisterClientForm::RegisterClientForm(QWidget *parent) : QWidget(parent) {
    if (!DatabaseManager::getInstance().connectToDatabase()) {
        return;
    }
    layout = new QVBoxLayout(this);

    fioLabel = new QLabel("FIO:", this);
    fioLineEdit = new QLineEdit(this);

    phoneLabel = new QLabel("Phone:", this);
    phoneLineEdit = new QLineEdit(this);

    emailLabel = new QLabel("Email:", this);
    emailLineEdit = new QLineEdit(this);

    addressLabel = new QLabel("Address:", this);
    addressLineEdit = new QLineEdit(this);

    passLabel = new QLabel("Password:", this);
    passLineEdit = new QLineEdit(this);

    registerButton = new QPushButton("Register", this);

    layout->addWidget(fioLabel);
    layout->addWidget(fioLineEdit);
    layout->addWidget(phoneLabel);
    layout->addWidget(phoneLineEdit);
    layout->addWidget(emailLabel);
    layout->addWidget(emailLineEdit);
    layout->addWidget(addressLabel);
    layout->addWidget(addressLineEdit);
    layout->addWidget(passLabel);
    layout->addWidget(passLineEdit);
    layout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, &RegisterClientForm::onRegisterButtonClicked);

    setLayout(layout);
    setWindowTitle("Register Client");
    resize(300, 300);
}

RegisterClientForm::~RegisterClientForm() {
    delete fioLabel;
    delete fioLineEdit;
    delete phoneLabel;
    delete phoneLineEdit;
    delete emailLabel;
    delete emailLineEdit;
    delete addressLabel;
    delete addressLineEdit;
    delete passLabel;
    delete passLineEdit;
    delete registerButton;
    DatabaseManager::getInstance().closeDatabase();
}

void RegisterClientForm::onRegisterButtonClicked() {
    QString fio = fioLineEdit->text();
    QString phone = phoneLineEdit->text();
    QString email = emailLineEdit->text();
    QString address = addressLineEdit->text();
    QString pass = passLineEdit->text();

    if (fio.isEmpty() || phone.isEmpty() || email.isEmpty() || address.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled!");
        return;
    }

    QFile file("C:/BD/persons.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open file for writing!");
        return;
    }

    QTextStream out(&file);
    out << "Client:" << fio << ":" << pass << "\n";
    file.close();

    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT MAX(ID_Client) FROM Clients");
    if (query.next()) {
        int maxId = query.value(0).toInt();
        int newId = maxId + 1;


        query = DatabaseManager::getInstance().executeQuery("INSERT INTO Clients (ID_Client, FIO, Phone, Email, Address) VALUES (:id, :fio, :phone, :email, :address)",
                                                            {newId, fio, phone, email, address});

        if (query.lastError().isValid()) {
            QMessageBox::warning(this, "Error", "Failed to register client!");
        } else {
            QMessageBox::information(this, "Success", "Client registered successfully!");
            this->close();
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to get the maximum ID_Client!");
    }
}
