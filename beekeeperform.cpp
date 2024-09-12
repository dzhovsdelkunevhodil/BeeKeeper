#include "beekeeperform.h"
#include "editbeekeeperform.h"
BeekeeperForm::BeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Welcome, " + login + "!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(welcomeLabel);

    setLayout(layout);
    setWindowTitle("Beekeeper Form");

    editBDataButton = new QPushButton("Edit Data", this);
    connect(editBDataButton, &QPushButton::clicked, this, [this, login]() { showEditBform(login); });
}

BeekeeperForm::~BeekeeperForm() {
    delete welcomeLabel;
}

void BeekeeperForm::showEditBform(const QString &login) {
    EditBeekeeperForm *editBform = new EditBeekeeperForm(login);
    editBform->show();
    this->close();
};
