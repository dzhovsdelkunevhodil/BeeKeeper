#ifndef ALLCOLONYFORM_H
#define ALLCOLONYFORM_H
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
class AllColonyForm : public QWidget {
    Q_OBJECT

public:
    explicit AllColonyForm(QWidget *parent = nullptr);
    ~AllColonyForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked();
    void onBackButtonClicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon);
    void loadColoniesData();
    QLabel *welcomeLabel;
    QPushButton *editDataButton;
    QPushButton *addDataButton;
    QPushButton *deleteDataButton;
    QVBoxLayout *mainLayout;
    QTableView *tableView;
    QSqlTableModel *model;
    QString login;
    QPushButton *backButton;

    QVBoxLayout *buttonLayout;
};
#endif // ALLCOLONYFORM_H
