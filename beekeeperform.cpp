#include "editbeekeeperform.h"
#include "managehivesform.h"
#include "beekeeperform.h"
#include "managecoloniesform.h"

BeekeeperForm::BeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent) {
    if (!DatabaseManager::getInstance().connectToDatabase()) {
        return;
    }
    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Welcome, " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(welcomeLabel);

    buttonLayout = new QHBoxLayout();

    // Инициализация кнопок
    editBeekeeperButton = new QPushButton("Edit Data", this);
    manageHivesButton = new QPushButton("Manage Hives", this);
    manageColoniesButton = new QPushButton("Manage Colonies", this);
    //manageHarvestsButton = new QPushButton("Manage Harvests", this);
    //viewAllButton = new QPushButton("View All", this);

    // Добавление кнопок в горизонтальный макет
    buttonLayout->addWidget(editBeekeeperButton);
    buttonLayout->addWidget(manageHivesButton);
    buttonLayout->addWidget(manageColoniesButton);
    //buttonLayout->addWidget(manageHarvestsButton);
    //buttonLayout->addWidget(viewAllButton);

    // Добавление горизонтального макета в вертикальный макет
    mainLayout->addLayout(buttonLayout);

    // Подключение сигналов к слотам
    connect(editBeekeeperButton, &QPushButton::clicked, this, [this, login]() { showEditBform(login); });
    connect(manageHivesButton, &QPushButton::clicked, this, [this, login]() { showManageHform(login); });
    // Подключение остальных кнопок (если есть соответствующие слоты)
    connect(manageColoniesButton, &QPushButton::clicked, this, [this, login]() { showManageCform(login); });
    // connect(manageHarvestsButton, &QPushButton::clicked, this, [this, login]() { showManageHform(login); });
    // connect(viewAllButton, &QPushButton::clicked, this, [this, login]() { showViewAllForm(login); });

    setLayout(mainLayout);
    setWindowTitle("Beekeeper Form");
    resize(800, 600); // Увеличиваем размер окна
}



BeekeeperForm::~BeekeeperForm(){
    delete welcomeLabel;
    delete editBeekeeperButton;
    delete manageHivesButton;
    delete manageColoniesButton;
    delete buttonLayout;
    delete mainLayout;
    DatabaseManager::getInstance().closeDatabase();

}

void BeekeeperForm::showEditBform(const QString &login) {
    EditBeekeeperForm *editBform = new EditBeekeeperForm(login);
    editBform->show();
    //this->close();
}



void BeekeeperForm::showManageHform(const QString &login) {
    ManageHivesForm *manageHform = new ManageHivesForm(login);
    manageHform->show();
    //this->close();
}

// Добавьте остальные слоты для других кнопок, если они есть
void BeekeeperForm::showManageCform(const QString &login) {
    ManageColoniesForm *manageCform = new ManageColoniesForm(login);
    manageCform->show();
   // this->close();
}

// void BeekeeperForm::showManageHform(const QString &login) {
//     ManageHarvestsForm *manageHform = new ManageHarvestsForm(login);
//     manageHform->show();
//     this->close();
// }

// void BeekeeperForm::showViewAllForm(const QString &login) {
//     ViewAllForm *viewAllForm = new ViewAllForm(login);
//     viewAllForm->show();
//     this->close();
// }
