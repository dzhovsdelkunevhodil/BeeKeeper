#ifndef ALLBEEKEEPERFORM_H
#define ALLBEEKEEPERFORM_H
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
#include <QStyledItemDelegate>
#include <QLineEdit>
#include "databasemanager.h"
#include <QCloseEvent>

class PhoneDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    PhoneDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setInputMask("+000 000 000 000;_");
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEdit->text(), Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        editor->setGeometry(option.rect);
    }
};

class EmailDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    EmailDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QLineEdit *editor = new QLineEdit(parent);
        connect(editor, &QLineEdit::textChanged, this, [this, editor](const QString &text) {
            if (!isValidEmail(text)) {
                editor->setStyleSheet("border: 1px solid red;");
            } else {
                editor->setStyleSheet("");
            }
        });
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        if (isValidEmail(lineEdit->text())) {
            model->setData(index, lineEdit->text(), Qt::EditRole);
        }
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        editor->setGeometry(option.rect);
    }

private:
    bool isValidEmail(const QString &email) const {
        if (email.isEmpty()) {
            return true; // Пустое значение допустимо
        }
        if (email.contains(' ') || email.contains(',') || email.contains(';')) {
            return false; // Запрещенные символы
        }
        if (email.contains('@') && email.contains('.')) {
            return true; // Допустимый формат электронной почты
        }
        return false;
    }
};

class AllBeekeeperForm : public QWidget {
    Q_OBJECT

public:
    explicit AllBeekeeperForm(QWidget *parent = nullptr);
    ~AllBeekeeperForm();

private slots:
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onAddButtonClicked();
    void onBackButtonClicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon);
    void loadBeekeepersData();

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

    PhoneDelegate *phoneDelegate;
    EmailDelegate *emailDelegate;
};

#endif // ALLBEEKEEPERFORM_H
