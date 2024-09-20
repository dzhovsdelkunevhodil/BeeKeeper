#ifndef MANAGEHIVESFORM_H
#define MANAGEHIVESFORM_H

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
#include "databasemanager.h"
#include <QCloseEvent>
class ManageHivesForm : public QWidget {
    Q_OBJECT

public:
    explicit ManageHivesForm(const QString &login, QWidget *parent = nullptr);
    ~ManageHivesForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked(const QString &login);
    void onBackButtonClicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void loadHivesData(const QString &login);
    int getBeekeeperId(const QString &login);
    void showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon);
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


#endif // MANAGEHIVESFORM_H
