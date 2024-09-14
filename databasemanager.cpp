#include "databasemanager.h"

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        database = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        database = QSqlDatabase::addDatabase("QODBC");
        database.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:/BD/DB.accdb;");

    }

    if (!database.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"), database.lastError().text());
        return false;
    }
    return true;
}

void DatabaseManager::closeDatabase() {
    if (database.isOpen()) {
        database.close();
    }
}

QSqlQuery DatabaseManager::executeQuery(const QString &query, const QVariantList &bindValues) {
    QSqlQuery q(database);
    q.prepare(query);
    for (int i = 0; i < bindValues.size(); ++i) {
        q.bindValue(i, bindValues.at(i));
    }
    q.exec();
    return q;
}

