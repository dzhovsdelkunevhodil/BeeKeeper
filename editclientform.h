#ifndef EDITCLIENTFORM_H
#define EDITCLIENTFORM_H
#include "allbeekeeperform.h"
//#include "databasemanager.h"
#include <QWidget>
#include <QLabel>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QCloseEvent>

class EditClientForm : public QWidget {
    Q_OBJECT

public:
    explicit EditClientForm(const QString &login, QWidget *parent = nullptr);
    ~EditClientForm();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onEditDataButtonClicked();
    void onBackButtonClicked();

private:
    void loadClientData(const QString &login);

    QLabel *welcomeLabel;
    QPushButton *editDataButton;
    QPushButton *backButton;
    QTableView *tableView;
    QSqlTableModel *model;
    QString login;
    QVBoxLayout *layout;
    PhoneDelegate *phoneDelegate;
    EmailDelegate *emailDelegate;
};

#endif // EDITCLIENTFORM_H
