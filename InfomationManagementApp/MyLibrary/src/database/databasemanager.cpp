#include "databasemanager.h"

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
// Khởi tạo các biến tĩnh
QString DatabaseManager::mHostName = "localhost";
int DatabaseManager::mPort = 5432;
QString DatabaseManager::mDBName = "bookstore";
QString DatabaseManager::mUserName = "postgres";
QString DatabaseManager::mPassWord = "1";

static QMutex dbMutex;

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
    qDebug() << __PRETTY_FUNCTION__ << "currentThreadId:" << QThread::currentThreadId();
    QString connName = QString("Conn_Thread_%1").arg(quintptr(QThread::currentThreadId()));
    qDebug() << __PRETTY_FUNCTION__ << " connName: " << connName;
    QMutexLocker locker(&dbMutex);
    if (QSqlDatabase::contains(connName)) {
        qDebug() << __PRETTY_FUNCTION__ << " connName is exist in db, return!";
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
    } else {
        qDebug() << __PRETTY_FUNCTION__ << " create new db successfully! db: " << db;
    }
    return db;
}

void DatabaseManager::closeConnectionForCurrentThread()
{
    qDebug() << __PRETTY_FUNCTION__ << "currentThreadId:" << QThread::currentThreadId();
    QString connName = QString("Conn_Thread_%1").arg(quintptr(QThread::currentThreadId()));
    qDebug() << __PRETTY_FUNCTION__ << " connName: " << connName;
    if (QSqlDatabase::contains(connName)) {
        qDebug() << __PRETTY_FUNCTION__ << " close and remove database, connName: " << connName;
        QSqlDatabase::database(connName).close();
        QSqlDatabase::removeDatabase(connName);
    }
}
