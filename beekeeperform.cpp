#include "editbeekeeperform.h"
#include "managehivesform.h"
#include "beekeeperform.h"
#include "managecoloniesform.h"
#include "manageHCform.h"


BeekeeperForm::BeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent) {
    if (!DatabaseManager::getInstance().connectToDatabase()) {
        return;
    }

    setWindowTitle("Beekeeper Form");
    setFixedSize(800, 600);

    // Устанавливаем фон с картинкой
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap("C:/BD/background.png").scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());
    backgroundLabel->lower();

    // Создаем черный прямоугольник для кнопок
    QWidget *blackRect = new QWidget(this);
    blackRect->setStyleSheet("background-color: #000000;");
    blackRect->setGeometry(100, 100, 600, 400); // Установите размеры и положение прямоугольника

    mainLayout = new QVBoxLayout(blackRect);
    mainLayout->setAlignment(Qt::AlignCenter);

    welcomeLabel = new QLabel("Welcome, " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFA500;");

    mainLayout->addWidget(welcomeLabel);

    buttonLayout = new QVBoxLayout(); // Изменяем QHBoxLayout на QVBoxLayout

    editBeekeeperButton = new QPushButton("Edit Data", this);
    editBeekeeperButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    editBeekeeperButton->setFixedWidth(200);

    manageHivesButton = new QPushButton("Manage Hives", this);
    manageHivesButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    manageHivesButton->setFixedWidth(200);

    manageColoniesButton = new QPushButton("Manage Colonies", this);
    manageColoniesButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    manageColoniesButton->setFixedWidth(200);

    manageHCButton = new QPushButton("Manage Honey Collections", this);
    manageHCButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    manageHCButton->setFixedWidth(200);

    buttonLayout->addWidget(editBeekeeperButton);
    buttonLayout->addWidget(manageHivesButton);
    buttonLayout->addWidget(manageColoniesButton);
    buttonLayout->addWidget(manageHCButton);

    mainLayout->addLayout(buttonLayout);

    connect(editBeekeeperButton, &QPushButton::clicked, this, [this, login]() { showEditBform(login); });
    connect(manageHivesButton, &QPushButton::clicked, this, [this, login]() { showManageHform(login); });
    connect(manageColoniesButton, &QPushButton::clicked, this, [this, login]() { showManageCform(login); });
    connect(manageHCButton, &QPushButton::clicked, this, [this, login]() { showManageHCform(login); });

    blackRect->setLayout(mainLayout);
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


void BeekeeperForm::showManageCform(const QString &login) {
    ManageColoniesForm *manageCform = new ManageColoniesForm(login);
    manageCform->show();
   // this->close();
}

void BeekeeperForm::showManageHCform(const QString &login) {
    ManageHCForm *manageHCform = new ManageHCForm(login);
    manageHCform->show();
   // this->close();
}

// void BeekeeperForm::showViewAllForm(const QString &login) {
//     ViewAllForm *viewAllForm = new ViewAllForm(login);
//     viewAllForm->show();
//     this->close();
// }
