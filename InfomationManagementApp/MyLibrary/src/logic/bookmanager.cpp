#include "bookmanager.h"

#include <QtConcurrent/QtConcurrent>

#include "bookrepository.h"


BookManager::BookManager(QObject *parent)
    : QObject{parent}, mBookModel {new BookModel(this)}
{

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
    if (mIsLoading) return;
    setIsLoading(true);
    // Sử dụng QtConcurrent::run để chạy việc lấy dữ liệu ở luồng phụ
    // Tránh làm treo giao diện chính (Main Thread)
    QtConcurrent::run([this]() {
        // 1. Khởi tạo Repository để làm việc với DB
        BookRepository repo;

        // 2. Thực thi lấy dữ liệu
        QList<Book> results = repo.findAll();

        // 3. Đẩy kết quả về luồng chính để cập nhật UI an toàn
        QMetaObject::invokeMethod(this, [this, results]() {
            mBookModel->updateBooks(results); // Giả định Model của bạn có hàm setBooks
            setIsLoading(false);
        }, Qt::QueuedConnection);
    });
}

BookModel *BookManager::bookModel() const
{
    return mBookModel;
}

bool BookManager::isLoading() const
{
    return mIsLoading;
}

void BookManager::setIsLoading(bool newIsLoading)
{
    if (mIsLoading == newIsLoading) return;
    mIsLoading = newIsLoading;
    emit isLoadingChanged();
}
