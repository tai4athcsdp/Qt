#include "bookmanager.h"

#include <QtConcurrent/QtConcurrent>
#include <QDebug>

#include "bookrepository.h"

static BookManager* mInst = nullptr;


BookManager::BookManager(QObject *parent)
    : QObject{parent}, mBookModel {new BookModel(this)}
{
    QObject::connect(this, &BookManager::currentPageChanged, this, &BookManager::loadPage);
}

BookManager *BookManager::instance()
{
    qDebug() << __PRETTY_FUNCTION__ << mInst;
    if (!mInst) {
        mInst = new BookManager();
        mInst->updateTotalBooks();
        mInst->loadPage(1);
    }
    return mInst;
}

BookManager *BookManager::create(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return instance();
}

void BookManager::loadPage(int page)
{
    qDebug() << __PRETTY_FUNCTION__ << " page: " << page;
    int numOfPage = mTotalBooks + 10 - 1 / 10;
    if (page > numOfPage || page < 1) {
        qDebug() << __PRETTY_FUNCTION__ << " cannot load page: " << page;
    } else {
        qDebug() << __PRETTY_FUNCTION__ << " loading page: " << page;
        if (mIsLoading) return;
        setIsLoading(true);
        // Sử dụng QtConcurrent::run để chạy việc lấy dữ liệu ở luồng phụ
        // Tránh làm treo giao diện chính (Main Thread)
        QtConcurrent::run([this, page]() {
            // 1. Khởi tạo Repository để làm việc với DB
            BookRepository repo;

            // 2. Thực thi lấy dữ liệu
            QList<Book> results = repo.findAll(page);

            // // 3. Đẩy kết quả về luồng chính để cập nhật UI an toàn
            QMetaObject::invokeMethod(this, [this, results]() {

                qDebug() << __PRETTY_FUNCTION__ << " results.count " << results.count();

                mBookModel->updateBooks(results);
                setIsLoading(false);
            }, Qt::QueuedConnection);
        });
    }
}

void BookManager::updateTotalBooks()
{
    qDebug() << __PRETTY_FUNCTION__ << QThread::currentThreadId();
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

void BookManager::setCurrentPage(int newCurrentPage)
{
    if (mCurrentPage == newCurrentPage)
        return;
    mCurrentPage = newCurrentPage;
    emit currentPageChanged(newCurrentPage);
}
