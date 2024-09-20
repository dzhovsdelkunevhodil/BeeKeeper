#ifndef MANAGECOLONIESFORM_H
#define MANAGECOLONIESFORM_H
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
class ManageColoniesForm : public QWidget {
    Q_OBJECT

public:
    explicit ManageColoniesForm(const QString &login, QWidget *parent = nullptr);
    ~ManageColoniesForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked(const QString &login);
    void onBackButtonClicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon);
    void loadColoniesData(const QString &login);

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



#endif // MANAGECOLONIESFORM_H
