#ifndef BEEKEEPERFORM_H
#define BEEKEEPERFORM_H

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

class BeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit BeekeeperForm(const QString &login, QWidget *parent = nullptr);
    ~BeekeeperForm();

private slots:
    void onEditDataButtonClicked();

private:
    void loadBeekeeperData(const QString &login);

    QLabel *welcomeLabel;
    QPushButton *editDataButton;
    QPushButton *button4;
    QPushButton *button5;

    QTableView *tableView;
    QSqlTableModel *model;
    QSqlDatabase db;
    QString login;
};

#endif // BEEKEEPERFORM_H
