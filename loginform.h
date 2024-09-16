#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "clientform.h"
#include "beekeeperform.h"
#include "adminform.h"
#include "registerclientform.h"

class LoginForm : public QWidget {
    Q_OBJECT

public:
    LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
    void onRoleChanged(const QString &role);

private:
    bool checkCredentials(const QString &role, const QString &login, const QString &password);

    QVBoxLayout *layout;
    QLabel *roleLabel;
    QComboBox *roleComboBox;
    QLabel *loginLabel;
    QLineEdit *loginLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
};

#endif // LOGINFORM_H
