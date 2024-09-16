#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLabel>
#include "databasemanager.h"
#include "allbeekeeperform.h"
#include "allhiveform.h"
#include "allcolonyform.h"
#include "allclientform.h"
#include "allHCform.h"

class AdminForm : public QWidget {
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event) override;
public:
    explicit AdminForm(QWidget *parent = nullptr);
    ~AdminForm();
private slots:
    void showAllBeekeepersform();
    void showAllColoniesform();
    void showAllHivesform();
    void showAllHCform();
    void showAllClientsform();
private:
    QLabel *welcomeLabel;
    QVBoxLayout *layout;
    QPushButton *allBeekeepers;
    QPushButton *allHives;
    QPushButton *allHCollections;
    QPushButton *allClients;
    QPushButton *allColonies;
};

#endif // ADMINFORM_H


