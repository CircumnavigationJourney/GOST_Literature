#ifndef BIB_ITEM


#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QList>
#include <QDebug>
// Identifier,C,254	Type,C,254	Address,C,254	Annote,M	Author,M	Booktitle,M	Chapter,C,254	Edition,C,254	Editor,M	Howpublish,C,254
// Institutn, M	Journal, M	Month, C, 254	Note, M	Number, C, 254	Organizat, M	Pages, C, 254	Publisher, M	School, M	Series, C, 254	
// Title, M	RepType, C, 254	Volume, C, 254	Year, C, 254	URL, M	Custom1, M	Custom2, M	Custom3, M	Custom4, M	Custom5, M	ISBN, C, 254
//typedef string wstring;
//Это айтем для опен офиса, чтобы интегрировать его в базу данных
class  Bib_item{
  QString ID;                    //1
  QString Type;                  //2
  QString Address;               //3
  QString Annotel;               //4
  QString Author;                //5
  QString Booktitle;             //6
  QString Chapter;               //7
  QString Edition;               //8
  QString Howpublish;            //9
  QString Institut;              //10
  QString Jurnal;                //11
  QString Month;                 //12
  QString Note;                  //13
  QString Number;                //14
  QString Organizat;             //15
  QString Pages;                 //16
  QString Publisher;             //17
  QString School;                //18
  QString Series;                //19
  QString Title;                 //20
  QString Reptype;               //21
  QString Volume;                //22
  QString Year;                  //23
  QString URL;                   //24
  QString Cust_1;                //25
  QString Cust_2;                //26
  QString Cust_3;                //27
  QString Cust_4;                //28
  QString Cust_5;                //29
  QString ISBN;                  //20

  int Auth_count; // = count , at author + 1
public:
  Bib_item();
  ~Bib_item();

  void setItem(QString &authors, QString &name,QString &year,QString &T,QString &number, QString &pages,QString &jurnal);

};

#endif // !1
