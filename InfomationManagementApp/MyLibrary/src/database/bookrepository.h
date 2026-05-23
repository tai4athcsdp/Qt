#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <QObject>
#include <QSqlQuery>

#include "book.h"

class BookRepository : public QObject
{
    Q_OBJECT
public:
    explicit BookRepository(QObject *parent = nullptr);

    QList<Book> findAll();
    Book mapToBook(const QSqlQuery& query);

signals:
};

#endif // BOOKREPOSITORY_H
