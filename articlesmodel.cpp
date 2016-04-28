#include "articlesmodel.h"

ArticlesModel::ArticlesModel()
{

}

ArticlesModel::~ArticlesModel()
{

}


QVariant ArticlesModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() ||
       index.row() < 0 ||
       index.row() >= articlesList.data()->size() ||
       index.column() >= COLUMN_COUNT ||
       index.column() < 0)
    {
        return QVariant();
    }

    if(role == Qt::DisplayRole){
        return articlesList.data()->at(index.row()).GOST;
    }
    return QVariant();
}

QModelIndex ArticlesModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid() ||
       row < 0 || row >= articlesList.data()->size() ||
       column != 0) return QModelIndex();
    return createIndex(row, column);
}

QModelIndex ArticlesModel::parent(const QModelIndex &child) const
{
    //(void)(child);
    return QModelIndex();
}

int ArticlesModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : articlesList.data()->size();
}

int ArticlesModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : COLUMN_COUNT;
}

void ArticlesModel::append(const Biblio::Article &article)
{
    if(!isAlreadyExists(article))
    {
        beginInsertRows(QModelIndex(), articlesList.data()->size(), articlesList.data()->size());
        articlesList.data()->append(article);
        endInsertRows();
        qDebug() << articlesList.data()->at(articlesList.data()->size()-1).GOST;
    }
}

bool  ArticlesModel::isAlreadyExists(const Biblio::Article& article)
{
    if(!articlesList.isNull() && !articlesList.data()->isEmpty()){
        for(int i = 0; i < articlesList.data()->size(); ++i)
        {
            if(article.title == articlesList.data()->at(i).title &&
               article.journal == articlesList.data()->at(i).journal &&
               article.authors.at(0) == articlesList.data()->at(i).authors.at(0) &&
                    article.year == articlesList.data()->at(i).year){
                return true;
            }
        }
    }
    return false;
}
