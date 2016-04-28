#ifndef ARTICLESMODEL_H
#define ARTICLESMODEL_H
#include <QAbstractItemModel>
#include <QSharedPointer>

#include "article.h"

class ArticlesModel : public QAbstractItemModel
{
private:
    int COLUMN_COUNT = 1;
    QSharedPointer<QList<Biblio::Article>> articlesList;

    public:
    void setData(QSharedPointer<QList<Biblio::Article>> dataSource) {articlesList = dataSource;}
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    void append(const Biblio::Article &article);
    bool isAlreadyExists(const Biblio::Article& article);

    ArticlesModel();
    ~ArticlesModel();
};

#endif // ARTICLESMODEL_H
