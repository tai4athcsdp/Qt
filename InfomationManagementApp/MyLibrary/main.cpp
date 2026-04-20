#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath(":/qt/qml");

    DatabaseManager testDb;
    if (testDb.openDatabase("bookstore"))
    {
    } else {
    }

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LibraryApp", "Main");

    return app.exec();
}
