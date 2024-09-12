#ifndef EDITBEEKEEPERFORM_H
#define EDITBEEKEEPERFORM_H

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

class EditBeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit EditBeekeeperForm(const QString &login, QWidget *parent = nullptr);
    ~EditBeekeeperForm();

private slots:
    void onEditDataButtonClicked();

private:
    void loadBeekeeperData(const QString &login);

    QLabel *welcomeLabel;
    QPushButton *editDataButton;

    QTableView *tableView;
    QSqlTableModel *model;
    QSqlDatabase db;
    QString login;
};

#endif // EDITBEEKEEPERFORM_H
