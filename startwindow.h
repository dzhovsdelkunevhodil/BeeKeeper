#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QTimer>

class StartWindow : public QWidget {
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void showLoginForm();
private:
    QLabel *label;
   // QMovie *movie;
    QLabel *waitlabel;
};

#endif // STARTWINDOW_H
