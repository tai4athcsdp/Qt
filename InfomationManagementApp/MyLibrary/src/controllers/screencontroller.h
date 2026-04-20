#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QObject>
#include <QtQml/qqmlengine.h>
#include <QtQml/QJSEngine>



class ScreenController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ScreenId currentScreen READ currentScreen NOTIFY currentScreenChanged FINAL)
    QML_ELEMENT
    QML_SINGLETON
public:
    enum class ScreenId : uint8_t {
        Home,
        AllBook,
        Setting,
    };
    Q_ENUM(ScreenId)
    static ScreenController* instance();
    static ScreenController* create(QQmlEngine *engine, QJSEngine *scriptEngine);

    ScreenId currentScreen() const;
    Q_INVOKABLE void changeCurrentScreen(ScreenController::ScreenId newScreenId);

signals:
    void currentScreenChanged();

private:
    explicit ScreenController(QObject *parent = nullptr);
    ~ScreenController() = default;
    ScreenController(const ScreenController&) = delete;
    ScreenController& operator=(const ScreenController&) = delete;
    //move constructor
    ScreenController(ScreenController&&) = delete;
    //move assignment operator
    ScreenController& operator=(ScreenController&&) = delete;
    ScreenController::ScreenId mCurrentScreen {ScreenController::ScreenId::Home};
};

#endif // SCREENCONTROLLER_H
