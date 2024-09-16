#ifndef ORDERHISTORYFORM_H
#define ORDERHISTORYFORM_H

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
#include "databasemanager.h"

class OrderHistoryForm : public QWidget {
    Q_OBJECT

public:
    explicit OrderHistoryForm(const QString &login, QWidget *parent = nullptr);
    ~OrderHistoryForm();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    //void onEditDataButtonClicked();
    void onBackButtonClicked();

private:
    int getClientId(const QString &login);
    void loadOHData(const QString &login);

    QLabel *welcomeLabel;
    //QPushButton *editDataButton;
    QPushButton *backButton;
    QTableView *tableView;
    QSqlTableModel *model;
    QString login;
    QVBoxLayout *layout;
};
#endif // ORDERHISTORYFORM_H
