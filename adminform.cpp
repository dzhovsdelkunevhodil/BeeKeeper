#include "adminform.h"

AdminForm::AdminForm(QWidget *parent) : QWidget(parent) {
    if (!DatabaseManager::getInstance().connectToDatabase()) {
        return;
    }


    setFixedSize(800, 600);

    layout = new QVBoxLayout(this);

    allBeekeepers = new QPushButton("Beekeepers", this);
    allHives = new QPushButton("Hives", this);
    allHCollections = new QPushButton("Honey Collections", this);
    allClients = new QPushButton("Clients", this);
    allColonies = new QPushButton("Bee Colonies", this);


    welcomeLabel = new QLabel("Welcome, Admin!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);



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
