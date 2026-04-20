#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{}

bool DatabaseManager::openDatabase(const QString &dbName)
{
    mDb = QSqlDatabase::addDatabase("QPSQL");
    mDb.setHostName("localhost");
    mDb.setPort(5432);
    mDb.setDatabaseName(dbName);
    mDb.setUserName("postgres");
    mDb.setPassword("1");
    bool ok = mDb.open();
    return ok;

}
