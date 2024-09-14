#ifndef EDITBEEKEEPERFORM_H
#define EDITBEEKEEPERFORM_H
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

class EditBeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit EditBeekeeperForm(const QString &login, QWidget *parent = nullptr);
    ~EditBeekeeperForm();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onEditDataButtonClicked();
    void onBackButtonClicked(const QString &login);

private:
    void loadBeekeeperData(const QString &login);

    QLabel *welcomeLabel;
    QPushButton *editDataButton;
    QPushButton *backButton;
    QTableView *tableView;
    QSqlTableModel *model;
    QString login;
    QVBoxLayout *layout;
};

#endif // EDITBEEKEEPERFORM_H
