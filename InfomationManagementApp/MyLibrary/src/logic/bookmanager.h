#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <QObject>
#include <QQmlEngine>

#include "bookmodel.h"


class BookManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(BookModel* bookModel READ bookModel CONSTANT FINAL)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged FINAL)
public:
    static BookManager* instance();
    static BookManager* create(QQmlEngine* engine, QJSEngine* scriptEngine);
public:
    Q_INVOKABLE void fetchAllBooks();

    BookModel *bookModel() const;
    bool isLoading() const;
    void setIsLoading(bool newIsLoading);

signals:
    void isLoadingChanged();

private:
    explicit BookManager(QObject *parent = nullptr);
    ~BookManager() = default;
    BookManager(const BookManager&) = delete;
    BookManager& operator=(const BookManager&) = delete;
    BookManager(BookManager&&) = delete;
    BookManager& operator=(BookManager&&) = delete;
private:
    BookModel *mBookModel {nullptr};
    bool mIsLoading {false};
};

#endif // BOOKMANAGER_H
