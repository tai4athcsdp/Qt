#include "databasemanager.h"

#include <QThread>
// Khởi tạo các biến tĩnh
QString DatabaseManager::mHostName = "localhost";
int DatabaseManager::mPort = 5432;
QString DatabaseManager::mDBName = "bookstore";
QString DatabaseManager::mUserName = "postgres";
QString DatabaseManager::mPassWord = "1";

void DatabaseManager::init(const QString &hostName, const int port, const QString &dbName, const QString &userName, const QString &passWord)
{
    mHostName = hostName;
    mPort = port;
    mDBName = dbName;
    mUserName = userName;
    mPassWord = passWord;
}

QSqlDatabase DatabaseManager::getConnectionForCurrentThread()
{
    QString connName = QString("Conn_Thread_%1").arg(quintptr(QThread::currentThreadId()));
    if (QSqlDatabase::contains(connName)) {
        return QSqlDatabase::database(connName);
    }

    // Nếu luồng này chưa có kết nối, tạo mới dựa trên cấu hình tập trung
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connName);
    db.setHostName(mHostName);
    db.setPort(mPort);
    db.setDatabaseName(mDBName);
    db.setUserName(mUserName);
    db.setPassword(mPassWord);

    if (!db.open()) {
        qCritical() << "DatabaseManager: Lỗi mở kết nối cho luồng" << connName;
    }
    return db;
}

void DatabaseManager::closeConnectionForCurrentThread()
{
    QString connName = QString("Conn_Thread_%1").arg(quintptr(QThread::currentThreadId()));
    if (QSqlDatabase::contains(connName)) {
        QSqlDatabase::database(connName).close();
    }
}
