#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>

class LoginForm : public QWidget {
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void onLoginButtonClicked();

private:
    bool checkCredentials(const QString &role, const QString &login, const QString &password);
    // void connectDB(const QString &login, const QString &password);
    QComboBox *roleComboBox;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // LOGINFORM_H

