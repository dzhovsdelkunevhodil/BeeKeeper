#ifndef BUYFORM_H
#define BUYFORM_H

#include "databasemanager.h"
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
#include <QInputDialog>


class BuyForm : public QWidget {
    Q_OBJECT

public:
    explicit BuyForm(const QString &login, QWidget *parent = nullptr);
    ~BuyForm();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void onBuyButtonClicked(const QString &login);
    void onBackButtonClicked();

private:
    void loadProductsData();
    int getClientId(const QString &login);


    QLabel *welcomeLabel;
    QPushButton *buyButton;
    QPushButton *backButton;
    QTableView *tableView;
    QSqlTableModel *model;
    QString login;
    QVBoxLayout *layout;
};

#endif // BUYFORM_H
