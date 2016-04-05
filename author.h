#ifndef AUTHOR_H
#define AUTHOR_H
#include <QString>
#include <QDataStream>


struct Author {

    QString surname;
    QString initials;

    friend QDataStream& operator<<(QDataStream &out, const Author &author);
    friend QDataStream& operator>>(QDataStream &in, Author &author);
};

#endif // AUTHOR_H
