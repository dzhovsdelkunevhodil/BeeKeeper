#ifndef BEEKEEPERFORM_H
#define BEEKEEPERFORM_H
#include "databasemanager.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
class BeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit BeekeeperForm(const QString &login, QWidget *parent = nullptr);
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
    QPushButton *manageHCButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *manageColoniesButton;
};

#endif // BEEKEEPERFORM_H
