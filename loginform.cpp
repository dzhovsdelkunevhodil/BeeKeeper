#include "loginform.h"

LoginForm::LoginForm(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    roleLabel = new QLabel("Role:", this);
    roleComboBox = new QComboBox(this);
    roleComboBox->addItem("Beekeeper");
    roleComboBox->addItem("Client");
    roleComboBox->addItem("Admin");

    loginLabel = new QLabel("Login:", this);
    loginLineEdit = new QLineEdit(this);

    passwordLabel = new QLabel("Password:", this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);
    registerButton = new QPushButton("Register", this);
    registerButton->setVisible(false); // Скрываем кнопку регистрации по умолчанию

    layout->addWidget(roleLabel);
    layout->addWidget(roleComboBox);
    layout->addWidget(loginLabel);
    layout->addWidget(loginLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginForm::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginForm::onRegisterButtonClicked);
    connect(roleComboBox, &QComboBox::currentTextChanged, this, &LoginForm::onRoleChanged);
}

LoginForm::~LoginForm() {
    delete roleComboBox;
    delete loginLineEdit;
    delete passwordLineEdit;
    delete roleLabel;
    delete loginLabel;
    delete passwordLabel;
    delete loginButton;
    delete registerButton;
}

void LoginForm::onLoginButtonClicked() {
    QString role = roleComboBox->currentText();
    QString login = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    if (checkCredentials(role, login, password)) {
        QMessageBox::information(this, "Correct", "Correct login and password!");
        if (role == "Client") {
            ClientForm *clientForm = new ClientForm(login);
            clientForm->show();
        } else if (role == "Beekeeper") {
            BeekeeperForm *beekeeperForm = new BeekeeperForm(login);
            beekeeperForm->show();
        } else if (role == "Admin") {
            AdminForm *adminForm = new AdminForm();
            adminForm->show();
        }

        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Invalid login or password!");
    }
}

void LoginForm::onRegisterButtonClicked() {
    RegisterClientForm *registerClientForm = new RegisterClientForm();
    registerClientForm->show();
}

void LoginForm::onRoleChanged(const QString &role) {
    if (role == "Client") {
        registerButton->setVisible(true);
    } else {
        registerButton->setVisible(false);
    }
}

bool LoginForm::checkCredentials(const QString &role, const QString &login, const QString &password) {
    QFile file("C:/BD/persons.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(":");
        if (parts.size() == 3 && parts[0] == role && parts[1] == login && parts[2] == password) {
            return true;
        }
    }
    file.close();
    return false;
}
