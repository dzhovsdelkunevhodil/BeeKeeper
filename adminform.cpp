#include "adminform.h"

AdminForm::AdminForm(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Welcome, Admin!", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(welcomeLabel);

    setLayout(layout);
    setWindowTitle("Admin Form");
}

AdminForm::~AdminForm() {
    delete welcomeLabel;
}
