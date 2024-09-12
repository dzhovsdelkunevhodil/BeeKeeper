#include "clientform.h"

ClientForm::ClientForm(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Welcome, Client!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(welcomeLabel);

    setLayout(layout);
    setWindowTitle("Client Form");
}

ClientForm::~ClientForm() {
    delete welcomeLabel;
}
