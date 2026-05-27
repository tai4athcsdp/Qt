#include "bookrepository.h"
#include "databasemanager.h"

#include <QSqlError>

BookRepository::BookRepository(QObject *parent)
    : QObject{parent}
{}

QList<Book> BookRepository::findAll(int pageNumber, int pageSize)
{    
    // Tính toán vị trí bắt đầu bốc dữ liệu từ Postgres
    int offset = (pageNumber - 1) * pageSize;

    QList<Book> books;

    {
        QSqlDatabase db = DatabaseManager::getConnectionForCurrentThread();

        if (!db.isOpen()) return books;

        // 2. Thực thi SQL
        QSqlQuery query(db);
        // Sử dụng LIMIT và OFFSET để bốc trúng phân đoạn dữ liệu
        query.prepare("SELECT * FROM book ORDER BY id ASC LIMIT :limit OFFSET :offset");
        query.bindValue(":limit", pageSize);
        query.bindValue(":offset", offset);

        if (!query.exec()) {
            qDebug() << "Postgres Query Error:" << query.lastError().text();
            return books;
        }

        while (query.next()) {
            books.append(mapToBook(query));
        }
    }

    // 3. Giải phóng kết nối của luồng
    DatabaseManager::closeConnectionForCurrentThread();
    return books;
}

unsigned int BookRepository::countAll()
{
    unsigned int totalBooks = 0;

    {
        // 1. Lấy kết nối an toàn dành riêng cho luồng hiện tại
        QSqlDatabase db = DatabaseManager::getConnectionForCurrentThread();

        if (!db.isOpen()) return totalBooks;

        // 2. Thực thi SQL đếm tổng số dòng
        QSqlQuery query(db);

        // Vì bảng đã lên tới 500,000 dòng, dùng COUNT(*) kết hợp Index trên id
        // sẽ giúp Postgres trả về kết quả ngay lập tức
        if (!query.exec("SELECT COUNT(*) FROM book")) {
            qDebug() << "Postgres Count Query Error:" << query.lastError().text();
            return totalBooks;
        }

        // 3. Trích xuất con số tổng từ hàng kết quả đầu tiên
        if (query.next()) {
            totalBooks = query.value(0).toUInt();
        }
    }

    // 4. Giải phóng kết nối của luồng ngay sau khi scope đóng lại
    DatabaseManager::closeConnectionForCurrentThread();
    return totalBooks;
}

Book BookRepository::mapToBook(const QSqlQuery &query)
{    
    Book item;
    item.id = query.value("id").toInt();
    item.title = query.value("name").toString();
    item.author = query.value("author").toString();
    return item;
}
