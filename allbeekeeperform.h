#ifndef ALLBEEKEEPERFORM_H
#define ALLBEEKEEPERFORM_H
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
class AllBeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit AllBeekeeperForm(QWidget *parent = nullptr);
    ~AllBeekeeperForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked();
    void onBackButtonClicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void loadBeekeepersData();
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
#endif // ALLBEEKEEPERFORM_H
