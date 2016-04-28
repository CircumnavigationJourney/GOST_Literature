#ifndef AUTHOR_H
#define AUTHOR_H
#include <QString>
#include <QDataStream>


struct Author {

    QString surname;
    QString initials;
    bool operator==(const Author &author) const {
        return (surname == author.surname && initials == author.initials) ? true : false;
    }

    friend QDataStream& operator<<(QDataStream &out, const Author &author);
    friend QDataStream& operator>>(QDataStream &in, Author &author);
};

#endif // AUTHOR_H
