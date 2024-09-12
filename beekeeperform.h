#ifndef BEEKEEPERFORM_H
#define BEEKEEPERFORM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
class BeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit BeekeeperForm(const QString &login, QWidget *parent = nullptr);
    ~BeekeeperForm();
    void showEditBform(const QString &login);

private:
    QLabel *welcomeLabel;
    QPushButton *editBDataButton;
};

#endif // BEEKEEPERFORM_H
