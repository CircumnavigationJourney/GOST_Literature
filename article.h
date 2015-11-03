#ifndef ARTICLE_H
#define ARTICLE_H
#include "biblio.h"
//#include "Item_class.h"
//#include <QObject>
//#include <QList>
//#include <QRegularExpression>
//#include <QRegExp>
//#include <QMessageBox>
namespace Biblio {
class Article
{
private:

    int authors_count(QString &authors);
    //сборка элемента списка литературы из кусочков (функции коррекции ввода)
    void author_input_correction(QString &sourceString);
    void title_input_correction(QString &title);
    void year_input_correction(QString &year);
    void volume_input_correction(QString &vol);
    void number_input_correction(QString &number);
    void pages_input_correction(QString &pages);
    void jurnal_input_correction(QString &jurnal);
    //определение языка
    bool is_eng(QString &undefLangString) const;

public:
    Article();
    ~Article();

    QString author_normalization(QString &author);

    QList<QStringList> *Main_list;
    QStringList *temp_string_list;
    // Bib_item *temp_item;
    QString *main_string_data;
    //  bool Load_data_from_file(QString &filepath);
    //  void Save_data_to_file(QString &filepath);
    QString generate_GOST(QString &authors, QString &name,QString &year,QString &T,QString &number, QString &pages,QString &jurnal);
private:

    void operate_str(QString &temp_str);

};
}
#endif // ARTICLE_H
