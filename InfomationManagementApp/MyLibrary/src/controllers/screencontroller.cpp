#include "screencontroller.h"

ScreenController *ScreenController::instance()
{
    static ScreenController inst;
    return &inst;
}

ScreenController *ScreenController::create(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return instance();
}

ScreenController::ScreenController(QObject *parent)
{

}

ScreenController::ScreenId ScreenController::currentScreen() const
{
    return mCurrentScreen;
}

void ScreenController::changeCurrentScreen(ScreenController::ScreenId newScreenId)
{
    if (mCurrentScreen == newScreenId) {
        return;
    }
    mCurrentScreen = newScreenId;
    emit currentScreenChanged();
}


