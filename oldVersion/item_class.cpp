#include "Item_class.h"

Bib_item::Bib_item(){


  QString ID        ("");          //1
  QString Type      ("");          //2
  QString Address   ("");          //3
  QString Annotel   ("");          //4
  QString Author    ("");          //5
  QString Booktitle ("");          //6
  QString Chapter   ("");          //7
  QString Edition   ("");          //8
  QString Howpublish("");          //9
  QString Institut  ("");          //10
  QString Jurnal    ("");          //11
  QString Month     ("");          //12
  QString Note      ("");          //13
  QString Number    ("");          //14
  QString Organizat ("");          //15
  QString Pages     ("");          //16
  QString Publisher ("");          //17
  QString School    ("");          //18
  QString Series    ("");          //19
  QString Title     ("");          //20
  QString Reptype   ("");          //21
  QString Volume    ("");          //22
  QString Year      ("");          //23
  QString URL       ("");          //24
  QString Cust_1    ("");          //25
  QString Cust_2    ("");          //26
  QString Cust_3    ("");          //27
  QString Cust_4    ("");          //28
  QString Cust_5    ("");          //29
  QString ISBN      ("");          //20
}
Bib_item::~Bib_item(){}
void Bib_item::setItem(QString &authors, QString &name, QString &year, QString &T, QString &number, QString &pages, QString &jurnal){

  Author = authors;
  Title = name;
  Year = year;
  Volume = T;
  Number = number;
  Pages = pages;
  Jurnal = jurnal;
}
