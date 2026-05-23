#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static void init(const QString& hostName, const int port, const QString& dbName, const QString& userName, const QString& passWord);
    static QSqlDatabase getConnectionForCurrentThread();
    static void closeConnectionForCurrentThread();

private:
    static QString mHostName;
    static int mPort;
    static QString mDBName;
    static QString mUserName;
    static QString mPassWord;
};

#endif // DATABASEMANAGER_H
