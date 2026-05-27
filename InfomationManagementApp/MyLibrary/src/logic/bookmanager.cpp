#include "bookmanager.h"

#include <QtConcurrent/QtConcurrent>

#include "bookrepository.h"


BookManager::BookManager(QObject *parent)
    : QObject{parent}, mBookModel {new BookModel(this)}
{
    this->updateTotalBooks();
    this->loadPage(1);
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

void BookManager::loadPage(int page)
{
    if (mIsLoading) return;
    setIsLoading(true);
    // Sử dụng QtConcurrent::run để chạy việc lấy dữ liệu ở luồng phụ
    // Tránh làm treo giao diện chính (Main Thread)
    QtConcurrent::run([this, page]() {
        // 1. Khởi tạo Repository để làm việc với DB
        BookRepository repo;

        // 2. Thực thi lấy dữ liệu
        QList<Book> results = repo.findAll(page);

        // 3. Đẩy kết quả về luồng chính để cập nhật UI an toàn
        QMetaObject::invokeMethod(this, [this, results]() {
            mBookModel->updateBooks(results);
            setIsLoading(false);
        }, Qt::QueuedConnection);
    });
}

void BookManager::updateTotalBooks()
{
    QtConcurrent::run([this]() {
        BookRepository repo;

        // Thực thi câu lệnh đếm một cách an toàn tuyệt đối với luồng chính
        auto countResult = repo.countAll();

        // Đóng gói kết quả gửi về lại Main Thread
        QMetaObject::invokeMethod(this, [this, countResult]() {
            if (mTotalBooks != countResult) {
                mTotalBooks = countResult;
                emit totalBooksChanged();
            }
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

int BookManager::currentPage() const
{
    return mCurrentPage;
}

int BookManager::totalBooks() const
{
    return mTotalBooks;
}
