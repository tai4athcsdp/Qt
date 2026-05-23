#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    DatabaseManager::init("localhost", 5432, "bookstore", "postgres", "1");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LibraryApp", "Main");

    return app.exec();
}
