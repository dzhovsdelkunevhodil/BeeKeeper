#include "startwindow.h"
#include "loginform.h"
#include <QProgressBar>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    resize(1000, 800);
    setStyleSheet("background-color: #000000; border: 2px solid #000000;");

    label = new QLabel(this);
    // movie = new QMovie("C:/BD/bee.gif");
    // label->setMovie(movie);
    // movie->start();

    label->setPixmap(QPixmap("C:/BD/loading.jpg")); // Укажите путь к вашей картинке
    label->setGeometry(10, 10, 980, 740); // Установите размеры картинки

    waitlabel = new QLabel("Подождите, пожалуйста...", this);
    waitlabel->setGeometry(10, 750, 980, 30);
    waitlabel->setAlignment(Qt::AlignCenter);
    waitlabel->setStyleSheet("font-size: 16px; color: #FFFFFF;");

    QProgressBar *progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 780, 980, 20);
    progressBar->setRange(0, 0);
    progressBar->setStyleSheet("QProgressBar { background-color: #000000; border: 1px solid #FFFFFF; } QProgressBar::chunk { background-color: #FFFFFF; }");

    QTimer::singleShot(5000, this, &StartWindow::showLoginForm);
}

StartWindow::~StartWindow(){
    //delete movie;
    delete label;
    delete waitlabel;
}

void StartWindow::showLoginForm() {
    LoginForm *loginForm = new LoginForm();
    loginForm->show();
    this->close();
}
