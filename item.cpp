#include "item.h"
namespace Biblio {
Item::Item(int _ID, int _type, int _language, QList<QPair<QString, QString>> _authors, QString _title, QString _year,
     QString _pages, QString _journal, QString _number, QString _volume,
     QString _publisher,  QString _chapter, QString _booktitle, QString _edition):
    ID(_ID), type(_type), language(_language),
    authors(_authors), title(_title), year(_year), pages(_pages),
    journal(_journal), number(_number),volume(_volume), publisher(_publisher), chapter(_chapter), booktitle(_booktitle), edition(_edition)
{

}

Item::~Item()
{

}

}
