#ifndef BOOK_H
#define BOOK_H

#include <QObject>

struct Book {
    int id;
    QString title {""};
    QString author {""};
};

#endif // BOOK_H
