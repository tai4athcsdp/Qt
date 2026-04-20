#include "bookmodel.h"

BookModel::BookModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int BookModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return mListBook.count();
}

QVariant BookModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= mListBook.count())
        return QVariant();
    const Book& book = mListBook.at(index.row());
    switch(role) {
    case IdRole:
        return book.id;
    case TitleRole:
        return book.title;
    case AuthorRole:
        return book.author;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BookModel::roleNames() const
{
    // Ánh xạ Role ID sang tên biến sẽ dùng trong QML
    QHash<int, QByteArray> roles;
    roles[IdRole] = "bookId";
    roles[TitleRole] = "title";
    roles[AuthorRole] = "author";
    return roles;
}

void BookModel::updateBooks(const QList<Book> &newBooks)
{
    beginResetModel();
    mListBook = newBooks;
    endResetModel();
}
