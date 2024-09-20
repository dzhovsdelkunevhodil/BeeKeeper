#ifndef BEEKEEPERFORM_H
#define BEEKEEPERFORM_H
#include "databasemanager.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSqlTableModel>
#include <QTableView>
class BeekeeperForm : public QWidget {
    Q_OBJECT

public:
    BeekeeperForm(const QString &login, QWidget *parent = nullptr);
    ~BeekeeperForm();

private slots:
    void showEditBform(const QString &login);
    void showManageHform(const QString &login);
    void showManageCform(const QString &login);
    void showManageHCform(const QString &login);

private:
    QLabel *welcomeLabel;
    QPushButton *editBeekeeperButton;
    QPushButton *manageHivesButton;
    QPushButton *manageColoniesButton;
    QPushButton *manageHCButton;
    QVBoxLayout *mainLayout;
    QVBoxLayout *buttonLayout;
};

#endif // BEEKEEPERFORM_H

