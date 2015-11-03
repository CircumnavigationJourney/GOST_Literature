#include "biblio.h"
#include <QElapsedTimer>

using namespace Biblio;

Literature::Literature()
{

}

Literature::~Literature()
{

}

Literature::MergeResult Literature::getMergeList(QString &list1, QString &list2){
    int L1size = 0, L2size = 0, L1innerRepetition = 0, L2innerRepetition = 0, LresultSize = 0, titleProblem = 0, repetition = 0;
    //процент сопоставления двух названий при котором считается, что названия схожи
    //при разной длине названий в основной список помещается более длинное
    double comparisonPrecision = Biblio::COMPARISON_PRECISION;
    deleteExcessControlSymbols(list1);
    deleteExcessControlSymbols(list2);

    QStringList *L1 = main_string_normalization(list1);
    QStringList *L2 = main_string_normalization(list2);
    //QSharedPointer<QStringList> List1()

    for(int i = 0; i < L1->size(); ){
        if(L1->at(i).isEmpty()){
            L1->removeAt(i); continue;
        }
        ++i;
    }
    for(int i = 0; i < L2->size(); ){
        if(L2->at(i).isEmpty()){
            L2->removeAt(i); continue;
        }
        ++i;
    }
    L1size = L1->size();
    L2size = L2->size();

    QStringList L1_Titles;
    QStringList L2_Titles;


    for(int i = 0; i < L1->size(); ++i){
        L1_Titles.append(getArticleTitle((*L1)[i]));
        //deleteExcessSeparators(L1_Titles.last());
        if (!L1->at(i).contains(Biblio::titleControlPoint)){
            ++titleProblem;
           // qDebug() << L1->at(i);
        }
        //        qDebug() << L1_Titles.last();
    }

    for(int i = 0; i < L2->size(); ++i){
        L2_Titles.append(getArticleTitle((*L2)[i]));
        //deleteExcessSeparators(L2_Titles.last());
        if (!L2->at(i).contains(Biblio::titleControlPoint)){
            ++titleProblem;
           // qDebug() << L2->at(i);
        }
        //        qDebug() << L2_Titles.last();
    }

    if ( L1_Titles.size() != L1->size() || L2_Titles.size() != L2->size()){
        QString err("Something WRONG: Critical ERROR!\nКритическая ошибка, программа будет закрыта\nТакого не должно было случиться! Вселенная просит прощения");
        QMessageBox *mess = new QMessageBox;
        mess->setText(err);
        mess->setWindowIcon(QIcon("images:/windowIcon.png"));
        mess->setStandardButtons(QMessageBox::Ok);
        if(mess->exec() == QMessageBox::Ok)
            QApplication::quit();
        exit(1);
    }
    for(int i = 0; i < L1->size(); ++i){
        for(int n = i+1; n < L1->size();){
            double comparisonPercent = compareTitles(L1_Titles[i], L1_Titles[n]);
            if(comparisonPercent >= comparisonPrecision){
                ++L1innerRepetition;
                if(L1_Titles.at(i).size() < L1_Titles.at(n).size())
                    (*L1)[i] = (*L1)[n];

                L1_Titles.removeAt(n);
                L1->removeAt(n); continue;
            }
            ++n;
        }
        emit progress(i*100/L1->size(), Stage::ListCheck_1);
    }
    for(int i = 0; i < L2->size(); ++i){
        for(int n = i+1; n < L2->size();){
            double comparisonPercent = compareTitles(L2_Titles[i], L2_Titles[n]);
            if(comparisonPercent >= comparisonPrecision){
                ++L2innerRepetition;
                if(L2_Titles.at(i).size() < L2_Titles.at(n).size())
                    (*L2)[i] = (*L2)[n];

                L2_Titles.removeAt(n);
                L2->removeAt(n); continue;
            }
            ++n;
        }
        emit progress(i*100/L2->size(), Stage::ListCheck_2);
    }
#ifdef TEST
    QElapsedTimer *timer = new QElapsedTimer;
    timer->start();
    int TEST = 20;
    for(int i = TEST; i >= 0; --i)
#endif
        for(int i = 0; i < L1->size(); ++i){
            for(int n = 0; n < L2->size();){
                //qDebug() << int(L1_Titles[i] == L2_Titles[n]);
                // if( L1_Titles[i] == L2_Titles[n]){
                double comparisonPercent = compareTitles(L1_Titles[i], L2_Titles[n]);
//                            qDebug() << L1_Titles[i] << "\n" << L2_Titles[n];
//                            qDebug() << comparisonPercent;
//                            qDebug() << "_________________________________________________________";
                if( comparisonPercent >= comparisonPrecision){
                    ++repetition;
                    if(L2_Titles.at(n).size() > L1_Titles.at(i).size())
                        (*L1)[i] = (*L2)[n];

                    L2_Titles.removeAt(n);
                    L2->removeAt(n); continue;
                }
                ++n;
            }
             emit progress(i*100/L1->size(), Stage::MergeLists);
        }
#ifdef TEST
    qDebug() << timer->nsecsElapsed()/TEST;
#endif
    for(int i = 0; i < L2->size(); ++i){
        L1->append(L2->at(i));
    }
    LresultSize = L1->size();

    //QString result = L1->join("\n");
    QString report = QString("Элементов в Списке 1 : ") + QString::number(L1size) + QString("\n") +
            QString ("Элементов в Списке 2 : ") + QString::number(L2size) + QString("\n") +
            QString ("Повторяющихся внутри Списка 1 : ") + QString::number(L1innerRepetition) + QString("\n") +
            QString ("Повторяющихся внутри Списка 2 : ") + QString::number(L2innerRepetition) + QString("\n") +
            QString ("Не удалось распознать название элемента : ") + QString::number(titleProblem) + QString("\n") +
            QString ("Совпадающих элементов : ") + QString::number(repetition) + QString("\n") +
            QString ("Элементов в конечном списке : ") + QString::number(LresultSize);


    Literature::MergeResult result;
    result.resultList = QSharedPointer<QStringList>(L1);
    result.newElements = QSharedPointer<QStringList>(L2);
    result.report = report;

    //    QTextDocument resultDoc;
    //    QString s = L1->join("\n");
    //    resultDoc.setPlainText(s);
    //    s = resultDoc.toHtml();
    //qDebug() << s;
    return result;


}


QString Literature::getArticleTitle( QString& articleItem){
    if (articleItem.isEmpty()) {
        qDebug() << "Empty String";
        return articleItem;
    }
    //qDebug() << articleItem;
    //QRegExp textPoint("(?:\\[Text\\]) | (?:\\[Текст\\])");
    // qDebug() << "Contains textPoint : " << articleItem.contains(Biblio::titleControlPoint);
    if (!articleItem.contains(Biblio::titleControlPoint)){
        return articleItem;
    }
    //articleItem.replace(QChar(0xa0), QChar(0x20));
    QRegExp authorFirstName("(?:\\w+,(?:[\\s0xa0]\\w\\.){1,3})");
    int authorIndex = authorFirstName.indexIn(articleItem);
    // qDebug() << authorIndex;
    //на случай, если перед первым автором вставлен номер или еще что-то
    //иначе индекс должен быть равным 0
    if(authorIndex > 10 || authorIndex == -1){
        QString title = articleItem.left(articleItem.indexOf(Biblio::titleControlPoint));
        return title;
    }
    QString title = articleItem.mid(authorFirstName.cap(0).size()+1, articleItem.indexOf(Biblio::titleControlPoint) - authorFirstName.cap(0).size()-1);
    return title;


    //qDebug() << authorFirstName.cap(0);

    //    QRegExp afterAuthor("");
    //    int index = articleItem.indexOf(".");
    //    if(index == -1) {
    //        qDebug() << ""
    //        return QString();
    //    }
    //    QString author = articleItem.left();

}
void Literature::deleteExcessControlSymbols(QString &source){

    //qDebug() << source;
    if(source.contains("DOCTYPE HTML")){
        QRegExp htmlLineBreaks("(?:<br />)(?!</p>)");
        source = source.remove(htmlLineBreaks);
        QTextDocument doc;
        doc.setHtml(source);
        source = doc.toPlainText();


        //        QRegExp Html("(?:<[^>]*>)");
        //        source = source.remove(Html);
    }

    QRegExp multipleNewLines("(?:\\n{2,})|(?: \\n)");
    QRegExp multipleSpaces(" {2,}");
    //        source.replace("0xa", "\n"); |(?: \\n)

    source = source.replace(multipleNewLines, "\n");
    source = source.replace(multipleSpaces, " ");
    source = source.replace(" \n", "\n");
}
void Literature::deleteExcessSeparators(QString &stringForWordSeparation){
    QRegExp multipleSeparators("\\s{2,}");
    stringForWordSeparation.replace(multipleSeparators, " ");
}

double Literature::compareTitles(const QString& title1, const QString& title2)
{
    //допустимый процент различия названий по количеству слов
    //также влияет на сложность вычислений, чем выше процент тем чаще вызывается функция обработки названий с разным размером
    double allowedPercentOfWordCountDistinction = 100.0 - Biblio::COMPARISON_PRECISION;
    QRegExp wordSeparator("\\s");
    QStringList title1List = title1.split(wordSeparator);
    QStringList title2List = title2.split(wordSeparator);
    int TLSize1 = title1List.size();
    int TLSize2 = title2List.size();

    //    qDebug() << "Title 1 size : " << TLSize1;
    //    for(int i = 0; i < TLSize1; ++i){
    //        qDebug() << title1List.at(i);
    //    }
    //    qDebug() << "Title 2 size : " << TLSize2;
    //    for(int i = 0; i < TLSize2; ++i){
    //        qDebug() << title2List.at(i);
    //    }
    int similarity;
    double alreadyWrong;
    double percentOfUnlikeness;
    if(TLSize1 == TLSize2)
    {
        similarity = 0;
        for(int i = 0, entryIndex, lastEntry = 0; i < TLSize1;){
           // entryIndex = title2List.indexOf(title1List.at(i), lastEntry);
            entryIndex = index(title2List, title1List.at(i), lastEntry);
            if(entryIndex != -1){
                //сколько слов между entryIndex и i == entryIndex - i - 1
                percentOfUnlikeness = (entryIndex - i - 1)/TLSize1*100;
                if( percentOfUnlikeness > allowedPercentOfWordCountDistinction) return 100.0 - percentOfUnlikeness;
                else{
                    ++similarity;
                    //проверять со следующего индекса
                    lastEntry = entryIndex + 1;
                    ++i;
                }
            }
            else {
            ++i;
            alreadyWrong = (i-similarity)/TLSize1*100;
            if(alreadyWrong > allowedPercentOfWordCountDistinction)
                return 100.0 - alreadyWrong;
            }
        }
        return ((double(similarity)/TLSize1) * 100);
//        similarity = 0;
//        for(int i = 0; i < TLSize1; ++i)
//        {
//            if(title2List.contains(title1List.at(i)))
//                ++similarity;
//            alreadyWrong = (i-similarity)/TLSize1*100;
//            if( alreadyWrong > allowedPercentOfWordCountDistinction)
//            {
//                return 0;
//            }
//        }
//        return (double(similarity)/TLSize1) * 100;
    }
    else if(TLSize1 != TLSize2)
    {
        int sizeDif = abs(TLSize1 - TLSize2);
        double percentOfWordCountDistinction = (double(sizeDif*1.0)/
                                                (TLSize1 > TLSize2 ? TLSize1 : TLSize2))*100;
        if(percentOfWordCountDistinction > allowedPercentOfWordCountDistinction) return 0;
        QStringList *lowList;
        QStringList *largeList;
        if(TLSize1 > TLSize2)
        {
            largeList = &title1List;
            lowList = &title2List;
        }
        else
        {
            largeList = &title2List;
            lowList = &title1List;
        }

        int largeSize = largeList->size();
        //int lowSize = lowList->size();
        similarity = 0;

        for(int i = 0, entryIndex, lastEntry = 0; i < largeSize;){
           // entryIndex = lowList->indexOf(largeList->at(i), lastEntry);
            entryIndex = index(*lowList, largeList->at(i), lastEntry);
            if(entryIndex != -1){
                //сколько слов между entryIndex и i == entryIndex - i - 1
                percentOfUnlikeness = (entryIndex - i - 1)/largeSize*100;
                if( percentOfUnlikeness > allowedPercentOfWordCountDistinction) return 100.0 - percentOfUnlikeness;
                else{
                    ++similarity;
                    //проверять со следующего индекса
                    lastEntry = entryIndex + 1;
                    ++i;
                }
            }
            else {
            ++i;
            alreadyWrong = (i-similarity)/largeSize*100;
            if(alreadyWrong > allowedPercentOfWordCountDistinction)
                return 100.0 - alreadyWrong;
            }
        }
        return ((double(similarity)/largeSize) * 100);
        //--------------------------------------------------------------------
        //плохой алгоритм, лучше зависеть от пар слов или последовательности
        //        for(int i = 0; i < llSize; ++i){
        //            if(lowList->contains(largeList->at(i)))
        //                ++similarity;
        //             alreadyWrong = (i-similarity)/llSize*100;
        //            if(alreadyWrong > allowedPercentOfWordCountDistinction)
        //                return 0;
        //        }
        //        return ((double(similarity)/largeList->size()) * 100);
        //--------------------------------------------------------------------
    }
    return 0;
}

int Literature::index(const QStringList &list1, const QString &str, int entry){

    if(entry < 0)
        entry = 0;
    while(entry < list1.size()){
        if (list1.at(entry) == str)
            return  entry;
        ++entry;
    }
    return -1;

//    if (from < 0)
//        from = qMax(from + p.size(), 0);
//    if (from < p.size()) {
//        Node *n = reinterpret_cast<Node *>(p.at(from -1));
//        Node *e = reinterpret_cast<Node *>(p.end());
//        while (++n != e)
//            if (n->t() == t)
//                return int(n - reinterpret_cast<Node *>(p.begin()));
//    }
//    return -1;

}
