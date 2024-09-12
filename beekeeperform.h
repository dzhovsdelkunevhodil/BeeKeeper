#ifndef BEEKEEPERFORM_H
#define BEEKEEPERFORM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class BeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit BeekeeperForm(const QString &login, QWidget *parent = nullptr);
    ~BeekeeperForm();

private:
    QLabel *welcomeLabel;
};

#endif // BEEKEEPERFORM_H
