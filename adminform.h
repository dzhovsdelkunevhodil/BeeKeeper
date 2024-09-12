#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class AdminForm : public QWidget {
    Q_OBJECT

public:
    explicit AdminForm(QWidget *parent = nullptr);
    ~AdminForm();

private:
    QLabel *welcomeLabel;
};

#endif // ADMINFORM_H
