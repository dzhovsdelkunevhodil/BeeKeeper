#include "loginform.h"
#include "clientform.h"
#include "beekeeperform.h"
#include "adminform.h"
LoginForm::LoginForm(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    roleLabel = new QLabel("Role:", this);
    roleComboBox = new QComboBox(this);
    roleComboBox->addItem("Client");
    roleComboBox->addItem("Beekeeper");
    roleComboBox->addItem("Admin");

    loginLabel = new QLabel("Login:", this);
    loginLineEdit = new QLineEdit(this);

    passwordLabel = new QLabel("Password:", this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);

    layout->addWidget(roleLabel);
    layout->addWidget(roleComboBox);
    layout->addWidget(loginLabel);
    layout->addWidget(loginLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginForm::onLoginButtonClicked);
}

LoginForm::~LoginForm() {
    delete roleComboBox;
    delete loginLineEdit;
    delete passwordLineEdit;
    delete model;
    delete roleLabel;
    delete loginLabel;
    delete passwordLabel;
    delete loginButton;

}

void LoginForm::onLoginButtonClicked() {
    QString role = roleComboBox->currentText();
    QString login = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    if (checkCredentials(role, login, password)) {
        QMessageBox::information(this, "Correct", "Correct login and password!");
        // connectDB(login, password);
        QString role = roleComboBox->currentText();
        if (role == "Client") {
            ClientForm *clientForm = new ClientForm();
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

// void LoginForm::connectDB(){
//     db = QSqlDatabase::addDatabase("QODBC");
//     db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ =C:/BD/BD1.accdb");

//     if(db.open()){
//         QMessageBox::information(this, "Correct", "open");
//     }else{
//         QMessageBox::warning(this, "Error", "no open");
//         qDebug() << db.lastError();
//     }

// }
