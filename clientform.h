#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include "databasemanager.h"

class ClientForm : public QWidget {
    Q_OBJECT

public:
    ClientForm(const QString &login, QWidget *parent = nullptr);
    ~ClientForm();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void showOrderHistory(const QString &login);
    void editData(const QString &login);
    void buy(const QString &login);

private:
    QVBoxLayout *layout;
    QPushButton *orderHistoryButton;
    QPushButton *editDataButton;
    QPushButton *buyButton;
};

#endif // CLIENTFORM_H
