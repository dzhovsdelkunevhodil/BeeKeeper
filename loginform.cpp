#include "loginform.h"

LoginForm::LoginForm(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->setAlignment(Qt::AlignCenter);

    roleLabel = new QLabel("Role:", this);
    roleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    roleComboBox = new QComboBox(this);
    roleComboBox->addItem("Beekeeper");
    roleComboBox->addItem("Client");
    roleComboBox->addItem("Admin");
    roleComboBox->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    roleComboBox->setFixedWidth(200);

    loginLabel = new QLabel("Login:", this);
    loginLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    loginLineEdit = new QLineEdit(this);
    loginLineEdit->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    loginLineEdit->setFixedWidth(200);
    loginLineEdit->setMaxLength(55);

    passwordLabel = new QLabel("Password:", this);
    passwordLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFA500;");
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setStyleSheet("background-color: #000000; color: #FFA500; border: 1px solid #FFA500;");
    passwordLineEdit->setFixedWidth(200);
    passwordLineEdit->setMaxLength(55);

    loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    loginButton->setFixedWidth(200);
    registerButton = new QPushButton("Register", this);
    registerButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    registerButton->setFixedWidth(200);
    registerButton->setVisible(false);

    centralLayout->addWidget(roleLabel);
    centralLayout->addWidget(roleComboBox);
    centralLayout->addWidget(loginLabel);
    centralLayout->addWidget(loginLineEdit);
    centralLayout->addWidget(passwordLabel);
    centralLayout->addWidget(passwordLineEdit);
    centralLayout->addWidget(loginButton);
    centralLayout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginForm::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginForm::onRegisterButtonClicked);
    connect(roleComboBox, &QComboBox::currentTextChanged, this, &LoginForm::onRoleChanged);

    setStyleSheet("QWidget { background-color: #000000; }");

    resize(800, 600);


    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap("C:/BD/image.jpg"));
    imageLabel->setGeometry(10, 10, 80, 40);
    imageLabel->setAlignment(Qt::AlignBottom | Qt::AlignLeft);


    mainLayout->addLayout(centralLayout);
    mainLayout->addWidget(imageLabel);


    setLayout(mainLayout);


    animation = new QPropertyAnimation(imageLabel, "geometry");
    animation->setDuration(5000);
    animation->setStartValue(QRect(10, this->height() - imageLabel->pixmap().height() - 10, imageLabel->pixmap().width(), imageLabel->pixmap().height()));
    animation->setEndValue(QRect(this->width() - imageLabel->pixmap().width() - 10, this->height() - imageLabel->pixmap().height() - 10, imageLabel->pixmap().width(), imageLabel->pixmap().height()));
    animation->setLoopCount(1); //-1
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    connect(animation, &QPropertyAnimation::finished, this, &LoginForm::reverseAnimation);

    animation->start();

}
void LoginForm::reverseAnimation() {
    animation->setDirection(animation->direction() == QAbstractAnimation::Forward ? QAbstractAnimation::Backward : QAbstractAnimation::Forward);
    animation->start();
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
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText("Correct login and password!");
        messageBox.setWindowTitle("Correct");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
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
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Invalid login or password!");
        messageBox.setWindowTitle("Error");
        messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                                 "QMessageBox QLabel { color: #FFA500; }"
                                 "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
        messageBox.exec();
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
