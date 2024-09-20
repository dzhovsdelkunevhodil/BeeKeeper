#include "registerclientform.h"
#include "databasemanager.h"
RegisterClientForm::RegisterClientForm(QWidget *parent) : QWidget(parent) {
    if (!DatabaseManager::getInstance().connectToDatabase()) {
        return;
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->setAlignment(Qt::AlignCenter);

    fioLabel = new QLabel("FIO:", this);
    fioLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    fioLineEdit = new QLineEdit(this);
    fioLineEdit->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    fioLineEdit->setFixedWidth(200);
    fioLineEdit->setMaxLength(55);

    phoneLabel = new QLabel("Phone:", this);
    phoneLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    phoneLineEdit = new QLineEdit(this);
    phoneLineEdit->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    phoneLineEdit->setFixedWidth(200);
    phoneLineEdit->setMaxLength(55);

    emailLabel = new QLabel("Email:", this);
    emailLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    emailLineEdit = new QLineEdit(this);
    emailLineEdit->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    emailLineEdit->setFixedWidth(200);
    emailLineEdit->setMaxLength(55);

    addressLabel = new QLabel("Address:", this);
    addressLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    addressLineEdit = new QLineEdit(this);
    addressLineEdit->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    addressLineEdit->setFixedWidth(200);
    addressLineEdit->setMaxLength(55);

    passLabel = new QLabel("Password:", this);
    passLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    passLineEdit = new QLineEdit(this);
    passLineEdit->setEchoMode(QLineEdit::Password);
    passLineEdit->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    passLineEdit->setFixedWidth(200);
    passLineEdit->setMaxLength(55);

    registerButton = new QPushButton("Register", this);
    registerButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    registerButton->setFixedWidth(200);

    centralLayout->addWidget(fioLabel);
    centralLayout->addWidget(fioLineEdit);
    centralLayout->addWidget(phoneLabel);
    centralLayout->addWidget(phoneLineEdit);
    centralLayout->addWidget(emailLabel);
    centralLayout->addWidget(emailLineEdit);
    centralLayout->addWidget(addressLabel);
    centralLayout->addWidget(addressLineEdit);
    centralLayout->addWidget(passLabel);
    centralLayout->addWidget(passLineEdit);
    centralLayout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, &RegisterClientForm::onRegisterButtonClicked);

    setStyleSheet("QWidget { background-color: #000000; }");

    resize(800, 600);

    mainLayout->addLayout(centralLayout);

    setLayout(mainLayout);
    setWindowTitle("Register Client");
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
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("All fields must be filled!");
        messageBox.setWindowTitle("Error");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
        return;
    }

    QFile file("C:/BD/persons.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Failed to open file for writing!");
        messageBox.setWindowTitle("Error");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
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
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("Failed to register client!");
            messageBox.setWindowTitle("Error");
            messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                     "QMessageBox QLabel { color: #FFA500; }"
                                     "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
            messageBox.exec();
        } else {
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Information);
            messageBox.setText("Client registered successfully!");
            messageBox.setWindowTitle("Success");
            messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                     "QMessageBox QLabel { color: #FFA500; }"
                                     "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
            messageBox.exec();
            this->close();
        }
    } else {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Failed to get the maximum ID_Client!");
        messageBox.setWindowTitle("Error");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
    }
}
