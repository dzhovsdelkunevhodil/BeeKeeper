#ifndef ALLHIVEFORM_H
#define ALLHIVEFORM_H

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
class AllHiveForm : public QWidget {
    Q_OBJECT

public:
    explicit AllHiveForm(QWidget *parent = nullptr);
    ~AllHiveForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked();
    void onBackButtonClicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void loadHivesData();
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

#endif // ALLHIVEFORM_H
