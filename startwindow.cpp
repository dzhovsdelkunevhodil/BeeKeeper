#include "startwindow.h"
#include "loginform.h"

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    resize(500, 390);
    //setStyleSheet("background-color: #F222FF;");

    label = new QLabel(this);
    movie = new QMovie("C:/BD/bee.gif");
    label->setMovie(movie);
    movie->start();
    waitlabel = new QLabel("Подождите, пожалуйста...", this);
    waitlabel->setGeometry(10, 350, 480, 30);
    waitlabel->setAlignment(Qt::AlignCenter);
    waitlabel->setStyleSheet("font-size: 16px; color: #000000;");
    //this->close();
    QTimer::singleShot(5000, this, &StartWindow::showLoginForm);
}


StartWindow::~StartWindow(){
    delete movie;
    delete label;
    delete waitlabel;
}

void StartWindow::showLoginForm() {
    LoginForm *loginForm = new LoginForm();
    loginForm->show();
    this->close();
}
