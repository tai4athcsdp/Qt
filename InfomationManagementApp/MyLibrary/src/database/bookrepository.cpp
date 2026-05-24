#include "bookrepository.h"
#include "databasemanager.h"

#include <QSqlError>

BookRepository::BookRepository(QObject *parent)
    : QObject{parent}
{}

QList<Book> BookRepository::findAll()
{
    QList<Book> books;

    {
        QSqlDatabase db = DatabaseManager::getConnectionForCurrentThread();

        if (!db.isOpen()) return books;

        // 2. Thực thi SQL
        QSqlQuery query(db);
        query.prepare("SELECT * FROM book");

        if (query.exec()) {
            while (query.next()) {
                books.append(mapToBook(query));
            }
        }
    }

    // 3. Giải phóng kết nối của luồng này một cách gọn gàng
    DatabaseManager::closeConnectionForCurrentThread();
    return books;
}

Book BookRepository::mapToBook(const QSqlQuery &query)
{    
    Book item;
    item.id = query.value("id").toInt();
    item.title = query.value("name").toString();
    item.author = query.value("author").toString();
    return item;
}
