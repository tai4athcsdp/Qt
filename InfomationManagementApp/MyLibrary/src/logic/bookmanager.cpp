#include "bookmanager.h"

BookManager::BookManager(QObject *parent)
    : QObject{parent}
{

    mBookModel = new BookModel(this);
    QList<Book> listBook;
    listBook.append(Book{0, "Tôi thấy hoa vàng trên cỏ xanh", "Nguyễn Nhật Ánh"});
    listBook.append(Book{0, "Truyện Kiều", "Nguyễn Du"});
    listBook.append(Book{0, "Cây Bàng Lá Đỏ", "Lê Văn Ba"});
    mBookModel->updateBooks(listBook);
}

BookManager *BookManager::instance()
{
    static BookManager inst;
    return &inst;
}

BookManager *BookManager::create(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return instance();
}

void BookManager::fetchAllBooks()
{

}

BookModel *BookManager::bookModel() const
{
    return mBookModel;
}
