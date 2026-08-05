#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QThread>

#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Basic");
    QQmlApplicationEngine engine;

    DatabaseManager::init("localhost", 5432, "bookstore", "postgres", "1");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LibraryApp", "Main");

    qDebug() << "MainThread id : " <<QThread::currentThreadId();
    return app.exec();
}
