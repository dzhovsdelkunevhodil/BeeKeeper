#ifndef MANAGEHCFORM_H
#define MANAGEHCFORM_H

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
#include <QInputDialog>
#include <QCloseEvent>
class ManageHCForm : public QWidget {
    Q_OBJECT

public:
    explicit ManageHCForm(const QString &login, QWidget *parent = nullptr);
    ~ManageHCForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked(const QString &login);
    void onBackButtonClicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void loadHCData(const QString &login);
    int getBeekeeperId(const QString &login);
    QLabel *welcomeLabel;
    QPushButton *editDataButton;
    QPushButton *addDataButton;
    QPushButton *deleteDataButton;
    QVBoxLayout *mainLayout;
    QTableView *tableView;
    QSqlTableModel *model;
    QString login;
    QPushButton *backButton;

    QHBoxLayout *buttonLayout;
};

#endif // MANAGEHCFORM_H
