#include "beekeeperform.h"

BeekeeperForm::BeekeeperForm(const QString &login, QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Welcome, Beekeeper " + login + " !", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(welcomeLabel);

    setLayout(layout);
    setWindowTitle("Beekeeper Form");
}

BeekeeperForm::~BeekeeperForm() {
    delete welcomeLabel;
}
