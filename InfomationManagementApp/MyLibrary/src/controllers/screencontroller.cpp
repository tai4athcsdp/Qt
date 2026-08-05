#include "screencontroller.h"

static ScreenController* mInst = nullptr;

ScreenController *ScreenController::instance()
{
    if (!mInst) {
        mInst = new ScreenController();
    }
    return mInst;
}

ScreenController *ScreenController::create(QQmlEngine *engine, QJSEngine *scriptEngine)
{    
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return instance();
}

ScreenController::ScreenController(QObject *parent)
    : QObject(parent)
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


