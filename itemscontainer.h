#ifndef ITEMSCONTAINER_H
#define ITEMSCONTAINER_H

#include "item.h"
namespace Biblio{
class ItemsContainer
{
    QSharedPointer <QList<Item>> itemsData;
    QString fileExt;
public:
    enum class Type{
        JournalArticle,
        Book,
        Patent
    };
    enum class Language{
        English,
        Russian,
        French,
        German,
        Spanish

    };
    //bool addItem;
    ItemsContainer();
    ~ItemsContainer();
};
}
#endif // ITEMSCONTAINER_H
