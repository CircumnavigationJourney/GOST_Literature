#ifndef ITEM_H
#define ITEM_H
#include "biblio.h"
#include <QPair>

namespace Biblio {
class Item
{
public:
    //важные
    int ID;
    int type;
    int language;
    QList<QPair<QString, QString>> authors; // firstname, initials // authors.size() == author count
    QString title;
    QString year;
    QString pages;
    QString journal;
    QString number;
    QString volume;

    QString publisher;
    QString chapter;
    QString booktitle;
    QString edition;

    //QString institut;


    Item(int _ID, int _type, int _language, QList<QPair<QString, QString>> _authors, QString _title, QString _year,
         QString _pages, QString _journal = QString(), QString _number = QString(), QString _volume = QString(),
         QString _publisher = QString(),  QString _chapter = QString(), QString _booktitle = QString(), QString _edition = QString());
    ~Item();
};
}
#endif // ITEM_H
//class  Bib_item{
//  QString ID;                    //1
//  QString Type;                  //2
//  QString Address;               //3
//  QString Annotel;               //4
//  QString Author;                //5
//  QString Booktitle;             //6
//  QString Chapter;               //7
//  QString Edition;               //8
//  QString Howpublish;            //9
//  QString Institut;              //10
//  QString Jurnal;                //11
//  QString Month;                 //12
//  QString Note;                  //13
//  QString Number;                //14
//  QString Organizat;             //15
//  QString Pages;                 //16
//  QString Publisher;             //17
//  QString School;                //18
//  QString Series;                //19
//  QString Title;                 //20
//  QString Reptype;               //21
//  QString Volume;                //22
//  QString Year;                  //23
//  QString URL;                   //24
//  QString Cust_1;                //25
//  QString Cust_2;                //26
//  QString Cust_3;                //27
//  QString Cust_4;                //28
//  QString Cust_5;                //29
//  QString ISBN;                  //20

//  int Auth_count; // = count , at author + 1
//public:
//  Bib_item();
//  ~Bib_item();

//  void setItem(QString &authors, QString &name,QString &year,QString &T,QString &number, QString &pages,QString &jurnal);

//};
