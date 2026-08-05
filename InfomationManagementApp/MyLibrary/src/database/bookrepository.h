#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <QSqlQuery>

#include "book.h"

class BookRepository
{
public:
    explicit BookRepository();

    QList<Book> findAll(int pageNumber, int pageSize = 10);
    unsigned int countAll();
    Book mapToBook(const QSqlQuery& query);
};

#endif // BOOKREPOSITORY_H
