#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class ClientForm : public QWidget {
    Q_OBJECT

public:
    explicit ClientForm(QWidget *parent = nullptr);
    ~ClientForm();

private:
    QLabel *welcomeLabel;
    QVBoxLayout *layout;
};

#endif // CLIENTFORM_H
