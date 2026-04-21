#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

struct Book {
    int id;
    QString title {""};
    QString author {""};
};

class BookModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum BookRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        AuthorRole,
    };

    explicit BookModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    // Hàm cập nhật dữ liệu từ tầng Logic (sử dụng QList chuẩn Qt 6)
    void updateBooks(const QList<Book> &newBooks);
private:
    QList<Book> mListBook;

};

#endif // BOOKMODEL_H
