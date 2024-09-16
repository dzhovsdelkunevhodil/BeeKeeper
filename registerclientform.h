#ifndef REGISTERCLIENTFORM_H
#define REGISTERCLIENTFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "databasemanager.h"
#include <QFile>
#include <QTextStream>
class RegisterClientForm : public QWidget {
    Q_OBJECT

public:
    RegisterClientForm(QWidget *parent = nullptr);
    ~RegisterClientForm();

private slots:
    void onRegisterButtonClicked();

private:
    QVBoxLayout *layout;
    QLabel *fioLabel;
    QLineEdit *fioLineEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;
    QLabel *passLabel;
    QLineEdit *passLineEdit;
    QPushButton *registerButton;

};

#endif // REGISTERCLIENTFORM_H
