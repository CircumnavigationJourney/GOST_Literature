#ifndef BIBLIO_H
#define BIBLIO_H
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QList>
#include <QDebug>
#include <QRegExp>
#include <QTextDocument>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>
#include <QSharedPointer>
#include <QObject>
#include <QIcon>
namespace Biblio {
//extern QIcon windowIcon;
extern QString programmVersion;
extern double COMPARISON_PRECISION;
//extern QStringList *temp_string_list;
QStringList *main_string_normalization(QString &temp);
extern QRegExp titleControlPoint;
//класс содержащий общие функции и структуры для слияния списков
class Literature : public QObject
{
    Q_OBJECT
    static QString getArticleTitle(QString &articleItem);
    static double compareTitles(const QString &title1, const QString &title2);
    static void deleteExcessSeparators(QString &stringForWordSeparation);
    static int index(const QStringList& list, const QString& str, int entry);
public:
    struct MergeResult{
        QSharedPointer<QStringList> resultList;
        QSharedPointer<QStringList> newElements;
        QString report;
    };
    enum class Stage{
        ListCheck_1,
        ListCheck_2,
        MergeLists,
        Initial
    };
    static void deleteExcessControlSymbols(QString &source);
    MergeResult getMergeList(QString &list1, QString &list2);
    Literature();
    ~Literature();
    signals:
    void progress(int , Biblio::Literature::Stage);
};
class ItemsContainer;
class Article;
}

#endif // BIBLIO_H
