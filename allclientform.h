#ifndef ALLCLIENTFORM_H
#define ALLCLIENTFORM_H
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
class AllClientForm : public QWidget {
    Q_OBJECT

public:
    explicit AllClientForm(QWidget *parent = nullptr);
    ~AllClientForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked();
    void onBackButtonClicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void loadClientsData();
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

#endif // ALLCLIENTFORM_H
