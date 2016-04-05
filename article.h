#ifndef ARTICLE_H
#define ARTICLE_H
#include "biblio.h"
#include <QDateTime>
//#include "Item_class.h"
//#include <QObject>
#include <QList>
//#include <QRegularExpression>
//#include <QRegExp>
//#include <QMessageBox>
#include "author.h"
namespace Biblio {


class Article
{

public:
    QList<Author> authors;
    QString title;
    QString journal;
    QString year;
    QString vol;
    QString number;
    QString pages;
    QDateTime additionDate = QDateTime::currentDateTime();
    QString GOST;
    //methods
private:
    int authors_count();
    //сборка элемента списка литературы из кусочков (функции коррекции ввода)
    void author_input_correction(QString &sourceString);
    void title_input_correction(QString &title);
    void year_input_correction(QString &year);
    void volume_input_correction(QString &vol);
    void number_input_correction(QString &number);
    void pages_input_correction(QString &pages);
    void journal_input_correction(QString &jurnal);
    //определение языка
    bool is_eng(QString &undefLangString) const;
    //заполнение входящими данными
    bool getAuthors(QString &rawAuthorsString);
    void getTitle(QString &rawTitle);
    void getJournal(QString &rawJournal);
    void getVolume(QString &rawVolume);
    void getYear(QString &rawYear);
    void getNumber(QString &rawNumber);
    void getPages(QString &rawPages);

public:
    friend QDataStream & operator<<(QDataStream &out, const Article &article);
    friend QDataStream & operator>>(QDataStream &in, Article &article);
    Article();
    Article(QString &_authors, QString &_title, QString &_year, QString &_volume, QString &_number, QString &_pages, QString &_journal);
    ~Article();
    QString generate_GOST();
    bool isEmpty(){return (authors.isEmpty() || title.isEmpty() || journal.isEmpty() || year.isEmpty() || pages.isEmpty() || (vol.isEmpty() || number.isEmpty()));}

};
}
#endif // ARTICLE_H
