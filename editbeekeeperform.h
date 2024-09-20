#ifndef EDITBEEKEEPERFORM_H
#define EDITBEEKEEPERFORM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlTableModel>
#include <QMessageBox>
#include "allbeekeeperform.h"
#include "databasemanager.h"
#include <QCloseEvent>


class EditBeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit EditBeekeeperForm(const QString &login, QWidget *parent = nullptr);
    ~EditBeekeeperForm();

private slots:
    void onBackButtonClicked();
    void onEditDataButtonClicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void loadBeekeeperData(const QString &login);
    void showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon);

    QLabel *welcomeLabel;
    QPushButton *editDataButton;
    QPushButton *backButton;
    QVBoxLayout *layout;
    QTableView *tableView;
    QSqlTableModel *model;
    PhoneDelegate *phoneDelegate;
    EmailDelegate *emailDelegate;
};

#endif // EDITBEEKEEPERFORM_H

