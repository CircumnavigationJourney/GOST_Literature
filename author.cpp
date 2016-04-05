#include "author.h"

//*****************************************************************************************
QDataStream& operator<<(QDataStream &out, const Author &author)
{
    return out << author.initials << author.surname;
}

//*****************************************************************************************
QDataStream& operator>>(QDataStream &in, Author &author)
{
    return in >> author.initials >> author.surname;
}
