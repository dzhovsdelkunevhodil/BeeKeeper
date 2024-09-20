#include "adminform.h"

AdminForm::AdminForm(QWidget *parent) : QWidget(parent) {
    if (!DatabaseManager::getInstance().connectToDatabase()) {
        return;
    }
    setStyleSheet("QWidget { background-color: #000000; }"
                  "QLineEdit { background-color: #000000; color: #FFA500; }"
                  "QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }"
                  "QPushButton:hover { background-color: #FFD700; }");
    setFixedSize(800, 600);

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap("C:/BD/background.png").scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());
    backgroundLabel->lower();


    QWidget *blackRect = new QWidget(this);
    blackRect->setStyleSheet("background-color: #000000;");
    blackRect->setGeometry(100, 100, 600, 400);

    layout = new QVBoxLayout(blackRect);
    layout->setAlignment(Qt::AlignCenter);

    welcomeLabel = new QLabel("Welcome, Admin!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFA500;");

    allBeekeepers = new QPushButton("Beekeepers", this);
    allBeekeepers->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    allBeekeepers->setFixedWidth(200);

    allHives = new QPushButton("Hives", this);
    allHives->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    allHives->setFixedWidth(200);

    allHCollections = new QPushButton("Honey Collections", this);
    allHCollections->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    allHCollections->setFixedWidth(200);

    allClients = new QPushButton("Clients", this);
    allClients->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    allClients->setFixedWidth(200);

    allColonies = new QPushButton("Bee Colonies", this);
    allColonies->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    allColonies->setFixedWidth(200);


    QLabel *profilePictureLabel = new QLabel(blackRect);
    profilePictureLabel->setPixmap(QPixmap("C:/BD/profile.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    profilePictureLabel->setGeometry(10, 10, 150, 150);

    connect(allBeekeepers, &QPushButton::clicked, this, &AdminForm::showAllBeekeepersform);
    connect(allColonies, &QPushButton::clicked, this, &AdminForm::showAllColoniesform);
    connect(allHives, &QPushButton::clicked, this, &AdminForm::showAllHivesform);
    connect(allClients, &QPushButton::clicked, this, &AdminForm::showAllClientsform);
    connect(allHCollections, &QPushButton::clicked, this, &AdminForm::showAllHCform);

    layout->addWidget(welcomeLabel);
    layout->addWidget(allBeekeepers);
    layout->addWidget(allHives);
    layout->addWidget(allHCollections);
    layout->addWidget(allClients);
    layout->addWidget(allColonies);

    setLayout(layout);

    setWindowTitle("Admin Form");
}


AdminForm::~AdminForm() {
    delete welcomeLabel;
    delete layout;
    delete allBeekeepers;
    delete allHives;
    delete allHCollections;
    delete allClients;
    delete allColonies;
    DatabaseManager::getInstance().closeDatabase();
}


void AdminForm::closeEvent(QCloseEvent *event) {

    event->accept();
}


//пчеловода
void AdminForm::showAllBeekeepersform() {
    AllBeekeeperForm *allBform = new AllBeekeeperForm();
    allBform->show();
}

//пч семьи
void AdminForm::showAllColoniesform() {
    AllColonyForm *allCform = new AllColonyForm();
    allCform->show();
}

//ульи
void AdminForm::showAllHivesform() {
    AllHiveForm *allHform = new AllHiveForm();
    allHform->show();
}

//сборы меда
void AdminForm::showAllHCform() {
    AllHCForm *allHCform = new AllHCForm();
    allHCform->show();
}

//клиента
void AdminForm::showAllClientsform() {
    AllClientForm *allClform = new AllClientForm();
    allClform->show();
}
