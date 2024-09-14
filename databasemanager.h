#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class DatabaseManager {
public:
    static DatabaseManager& getInstance();

    bool connectToDatabase();
    void closeDatabase();
    QSqlQuery executeQuery(const QString &query, const QVariantList &bindValues = {});

private:
    DatabaseManager();
    ~DatabaseManager();

    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
