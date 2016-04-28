#include "article.h"
using namespace Biblio;

const int MIN_AUTH = 3; // максимальное число авторов, из-за которого нужно первого автора выставлять перед названием
const int MAX_AUTH = 4; // минимальное число авторов, из-за которого нужно перечислять всех авторов после названия,
//но не выставлять первого перед названием

//*****************************************************************************************
Article::Article(QString &_authors, QString &_title,QString &_year,QString &_volume,QString &_number, QString &_pages,QString &_journal)
{
    //    temp_string_list = new QStringList;
    //    Main_list = new QList<QStringList>;
    //temp_item = new Bib_item;

    //приведение всех элементов в надлежащий вид
    //все эти методы модифицируют входящую строку и добавляют данные в класс Статья (Article)
    getAuthors(_authors);
    getTitle(_title);
    getYear(_year);
    getVolume(_volume);
    getNumber(_number);
    getJournal(_journal);
    getPages(_pages);
    GOST = generate_GOST();
}

//*****************************************************************************************
Article::Article()
{

}

//*****************************************************************************************
Article::~Article()
{

}

//*****************************************************************************************
//метод заполняет список авторов статьи, отделяя инициалы от фамилий
bool Article::getAuthors(QString &rawAuthorsString)
{
    author_input_correction(rawAuthorsString);
    QRegExp initials("([A-ZА-Я]\\.)"); //инициал автора
    QRegExp surname("\\w{3,}"); //имя автора если более 3 символов
    if(rawAuthorsString.contains(initials) && rawAuthorsString.contains(surname)){

        QString rawString = rawAuthorsString;
        int pos = 0;
        QList<Author> authors;
        qDebug() << rawAuthorsString;
        while(pos != -1){
            Author author;
            int initialsStart = rawString.indexOf(initials, pos);
            int surnameStart = rawString.indexOf(surname, pos);
            qDebug() << initialsStart << "initialsStart";
            qDebug() << surnameStart << "surnameStart";

            if(initialsStart < surnameStart && initialsStart != -1){
                qDebug() << " initialsStart < surnameStart";
                pos = initials.indexIn(rawString, pos);
                author.initials = initials.cap(0);
                int tempPosForInitial = pos;
                tempPosForInitial += initials.matchedLength();
                while((tempPosForInitial = initials.indexIn(rawString, tempPosForInitial)) < surnameStart && tempPosForInitial != -1)
                {
                    QString initial = initials.cap(0);
                    if(!initial.isEmpty())
                    {
                        author.initials += QChar::Nbsp;
                        author.initials += initial;
                        tempPosForInitial += initials.matchedLength();
                    }
                }
                pos = surname.indexIn(rawString, pos);
                author.surname = surname.cap(0);
                authors.append(author);
                pos += surname.matchedLength();
                int tempPos = pos;
                if((pos = (initials.indexIn(rawString, pos))) == -1){}
                else
                {
                    pos = tempPos;
                }
            }
            else if (initialsStart > surnameStart && surnameStart != -1)
            {
                qDebug() << " initialsStart > surnameStart";
                pos = surname.indexIn(rawString, pos);
                author.surname = surname.cap(0);
                pos = initials.indexIn(rawString, pos);
                if(pos != -1)
                {
                    author.initials = initials.cap(0);
                    int maxPos = surname.indexIn(rawString, pos);
                    pos += initials.matchedLength();
                    int tempPos = initials.indexIn(rawString, pos);
                    qDebug() << "tempPos=" << tempPos << " maxPos=" << maxPos;
                    if((maxPos != -1 && tempPos != -1 && tempPos < maxPos) || (maxPos == -1 && tempPos != -1))
                    {
                        qDebug () << "addition initial";
                        pos = initials.indexIn(rawString, pos);
                        author.initials += (QChar::Nbsp + initials.cap(0));
                        pos += initials.matchedLength();
                    }
                }
                authors.append(author);
            }
            else break;

        }
        qDebug () << "author count = " << authors.size();
        for(int i = 0; i < authors.size(); ++i){
            qDebug() << authors.at(i).surname << " " << authors.at(i).initials;
        }

        this->authors = authors;
        return true;
    }
    Author author;
    author.initials = "ОШИБКА ВВОДА ИМЕНИ АВТОРА";
    author.surname = "ОШИБКА ВВОДА ИМЕНИ АВТОРА";
    authors.append(author);
    return false;
}

//*****************************************************************************************
void Article::getTitle(QString &rawTitle)
{
    title_input_correction(rawTitle);
    title = rawTitle;
}

//*****************************************************************************************
void Article::getJournal(QString &rawJournal)
{
    journal_input_correction(rawJournal);
    journal = rawJournal;

}

//*****************************************************************************************
void Article::getYear(QString &rawYear)
{
    year_input_correction(rawYear);
    year = rawYear;
}


//*****************************************************************************************
void Article::getPages(QString &rawPages)
{
    pages_input_correction(rawPages);
    pages = rawPages;
}

//*****************************************************************************************
void Article::getNumber(QString &rawNumber)
{
    number_input_correction(rawNumber);
    qDebug () << "rawNumber" << rawNumber;
    if(!rawNumber.isEmpty())
    {
        number = rawNumber;
    }

}

//*****************************************************************************************
void Article::getVolume(QString &rawVolume)
{

    volume_input_correction(rawVolume);
    qDebug () << "rawVolume" << rawVolume;
    if(!rawVolume.isEmpty())
    {
        vol = rawVolume;
    }
}

//*****************************************************************************************
QDataStream& operator<<(QDataStream &out, const Article &article)
{
    return out << article.authors << article.title << article.journal << article.number << article.vol << article.year << article.pages << article.additionDate << article.GOST;
}

//*****************************************************************************************
QDataStream& operator>>(QDataStream &in, Article &article)
{
    return in >> article.authors >> article.title >> article.journal >> article.number >> article.vol >> article.year >> article.pages >> article.additionDate >> article.GOST;
}


//*****************************************************************************************
int Article::authors_count(){
    return authors.size();
}

//*****************************************************************************************
bool Article::is_eng(QString &undefLangString) const {
    //для точной проверки нужно закидывать список авторов, но не название статьи
    //т.к. названия русских статей могут содержать английские буквы
    qDebug() << "is_eng()";
    QRegExp engletters("[a-zA-Z]");
    qDebug() << undefLangString.contains(engletters);
    if(undefLangString.contains(engletters))
        return true;
    else return false;
}

//*****************************************************************************************
QString Article::generate_GOST(){
    qDebug() << "generate_GOST()";

    if(authors.isEmpty()){
        return QString();
    }
    //определение языка статьи
    int eng = is_eng(title);
    int authors_number = authors_count();

    //GOST = _title +" / "+_authors +" / "+ _jurnal+" / " + _year+" / " + _volume+": " + _number+" / "+ _pages;
    try{
        if(isEmpty()){
            throw "Элемент статьи не полный! Программа будет закрыта";
        }
    }
    catch(const char *){};

    if(!GOST.isEmpty()){
        GOST.clear();
    }

    //оформление по правилам (статья)
    if (authors_number <= MIN_AUTH){
        GOST = authors.at(0).surname + ", " + authors.at(0).initials + " " +
                title + (eng ? QString(" [Text]") : QString(" [Текст]")) + QChar::Nbsp + QString("/ ");
        for(int i = 0; i < authors.size(); ++i)
        {
            GOST += authors.at(i).initials + QChar::Nbsp + authors.at(i).surname + ((authors.size() == i+1) ? "" : ", ");
        }

    }
    else if (authors_number == MAX_AUTH){
        GOST = title + (eng ? QString(" [Text]") : QString(" [Текст]")) + QChar::Nbsp + QString("/ ");
        for(int i = 0; i < authors.size(); ++i)
        {
            GOST += authors.at(i).initials + QChar::Nbsp + authors.at(i).surname + ((authors.size() == i+1) ? "" : ", ");
        }
    }
    else {
        GOST = title + (eng ? QString(" [Text]") : QString(" [Текст]")) + QChar::Nbsp + QString("/ ");
        for (int i = 0; i < (MIN_AUTH); ++i){
            GOST += authors.at(i).initials + QChar::Nbsp + authors.at(i).surname;
            if (i != (MIN_AUTH-1))
                GOST += ", ";
        }
        GOST += (eng ? QString(" [et al]") : QString(" [и др.]"));
    }
    GOST += QChar::Nbsp + QString("// ") +
            journal + QChar::Nbsp + QChar(0x2013) + QChar::Space + year + QChar::Nbsp + QChar(0x2013) + QChar::Space;

    qDebug () << "vol.isEmpty() = " << vol.isEmpty() << " number.isEmpty() = " << number.isEmpty();

    if(!vol.isEmpty())
    {
        GOST  += (eng ? QString("Vol.") : QString("Т.")) + QChar::Nbsp + vol;
    }
    if(!number.isEmpty())
    {
        GOST +=  (vol.isEmpty() ? QString("№") : QString(", №")) + QChar::Nbsp + number;
    }

        GOST += QChar::Nbsp + QChar(0x2013) + QChar::Space + (eng ? QString("P.") : QString("С.")) + QChar::Nbsp + pages + QString(".");


    return GOST;
}

//*****************************************************************************************
//Приводит имена авторов к виду Фамилия И. О.
void Article::author_input_correction(QString &sourceString){
    qDebug() << "author_input_correction()";
    if (sourceString.isEmpty()) return;

    //энумераторы (цифрового либо буквенного типа) вставляются после имени автора и означают учреждение, которое тот представляет
    //специальные символы означают дополнительную информацию связанную с данным автором
    // к спец символам относятся:
    //QChar(42)     = *
    //QChar(124)    = |
    //QChar(8270)   = ⁎ (звездочка)
    //QChar(8224)   = †
    //QChar(8266) 0x2022   = • используется в некоторых статьях как разделитель вместо запятой
    sourceString.replace(QRegExp(QString(QChar(0x000A))), " ");
    //иногда в конце или между авторами в начале вставляют and
    //заменим все and на запятые
    QRegExp division("\\||[, ]and|•|[ ,][a-z]");
    while (sourceString.contains(division))
        sourceString.replace(division, ",");

    QString Specials("(?:PhD)|(?:MBBS)|(?:MSc)|(?:DMRT)");

    QRegExp spec(Specials);
    sourceString.remove(spec);

    //если имена с большой буквы, то нужно первую букву оставить заглавной
    //остальные перевести в нижний регистр
    QRegExp upperCaseName("[A-Z]{3,}|[А-Я]{3,}");
    QRegExp aA("[a-z][A-Z]|[а-я][А-Я]");
    while (sourceString.contains(upperCaseName)){
        sourceString.replace(sourceString.indexOf(upperCaseName) + 1, 1, sourceString.at(sourceString.indexOf(upperCaseName) + 1).toLower());
        while (sourceString.contains(aA))
            sourceString.replace(sourceString.indexOf(aA) + 1, 1, sourceString.at(sourceString.indexOf(aA) + 1).toLower());
        //sourceString.indexOf()
    }
    QRegExp garbage("[^\\s\\w]|[\\d]");
    sourceString.remove(garbage);
    //точки после инициалов (к инициалам относится любая одиночная буква верхнего регистра
    //либо две буквы верхнего регистра идущие друг за другом без разделителей)
    qDebug () << "sorceString before initials normalization " << sourceString;
    QRegExp initials1("[A-Z]{2}|[А-Я]{2}");
    QRegExp initials2("[A-ZА-Я]($|\\s)");
    while (sourceString.contains(initials1)){
        int i = sourceString.indexOf(initials1);
        sourceString.insert(i + 1, QChar::Space);
        sourceString.insert(i + 3, QChar::Space);
    }
    while (sourceString.contains(initials2))
        sourceString.insert(sourceString.indexOf(initials2) + 1, QChar('.'));
    qDebug () << "sorceString after initials normalization " << sourceString;
    //после всех замен в некоторых случаях должны остаться последовательно идущие запятые
    while(sourceString.contains(QRegExp("\\s{2,}")))
        sourceString.replace(QRegExp("\\s{2,}"), " ");
    while(sourceString.contains(QRegExp("[ ,],")))
        sourceString.replace(QRegExp("[ ,],"),",");
    while(sourceString.contains(QRegExp("[\\s,]$")))
        sourceString.remove(QRegExp("[\\s,]$"));
    while (sourceString.contains(QRegExp(",[A-Z]|,[А-Я]")))
        sourceString.insert(sourceString.indexOf(QRegExp(",[A-Z]|,[А-Я]")) + 1, QChar::Space);
    while (sourceString.contains(QRegExp("^\\W")))
        sourceString.remove(0, 1);

}

//*****************************************************************************************
void Article::title_input_correction(QString &title){
    qDebug() << "title_input_correction()";
    //заменить символ новой строки и множественные пробелы на 1 пробел
    title.replace(QRegExp(QString(QChar(0x000A))), " ");
    //удалить лишние пробелы
    title.replace(QRegExp("\\s{2,}"), " ");
    QRegExp regexpSpace("(?:^[ \\s])|(?:[ \\s]$)");
    title.remove(regexpSpace);

    //следующий блок функции нужен, чтобы заменять заглавные буквы на строчные
    //тк большинство названия на английском имеют заглавные буквы в начале каждого слова
    //нужно убедиться, не является ли это таким типом
    //названия бывают полностью из заглавных букв, бывает же что там присутствуют имена собственные, которые должны быть с заглавной буквы
    //нужно выяснить, к какому типу названий относится данное

    //типы
    QRegExp type_AAA("(?:[A-Z]|[А-Я]){4,}");
    QRegExp type_aaa("\\s(?:[a-z]|[а-я])");
    QRegExp upperLetter("(?!^)[A-ZА-Я]");// все заглавные буквы кроме той, с которой начинается строка
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //  продолжение типов Аавав Вввывы NADPH
    if (title.contains(type_AAA) && !title.contains(type_aaa)){
        while(title.contains(upperLetter))
            title.replace(title.indexOf(upperLetter), 1, title.at(title.indexOf(upperLetter)).toLower());
        qDebug() << QString ("Here");
    }

    else if (!title.contains(QRegExp("\\b[a-z]|\\b[а-я]"))){
        //все большие буквы английского или русского языка, идущие после пробела или дефиса
        QRegExp regexpBefore("(?:\\w)(?:[ -])(?:[A-Z]|[А-Я])(?![A-Z]|[А-Я])");
        int index = 0;

        while ((index = regexpBefore.indexIn(title, index)) != - 1){
            qDebug() << index;

            title.replace(index + 2, 1, QString(title.at(index + 2).toLower()));
            index += regexpBefore.matchedLength();
        }
    }
}

//*****************************************************************************************
void Article::year_input_correction(QString &year){

    qDebug() << "year_input_correction()";
    //удалить все лишнее
    QRegExp regexpNotYear("(?:[\\s^\\D]\\d{1,3}[\\D&])");
    QRegExp regexp("(?:\\D)");
    year.remove(regexpNotYear);
    year.remove(regexp);
}

//*****************************************************************************************
void Article::number_input_correction(QString &number){

    qDebug() << "number_input_correction()";
    QRegExp regexp("(?:\\D)");
    number.remove(regexp);
}

//*****************************************************************************************
void Article::volume_input_correction(QString &vol){

    qDebug() << "volume_input_correction()";
    //  QRegExp regexp("(?:\\D)");
    //  vol.remove(regexp);
    number_input_correction(vol);
}

//*****************************************************************************************
void Article::pages_input_correction(QString &pages){
    qDebug() << "pages_input_correction()";
    //404-6.
    //103–120

    while (pages.contains(QRegExp("\\s")))
        pages.remove(QRegExp("\\s"));
    QString tire("[");
    tire.append(QChar(0x2d));
    tire.append(QChar(0x2010));
    tire.append(QChar(0x2011));
    tire.append(QChar(0x2012));
    tire.append(QChar(0x2013));
    tire.append(QChar(0x2014));
    tire.append(QChar(0x2015));
    tire.append(QChar(']'));

    QRegExp regexp(QString("(\\d+)") + tire + QString("(\\d+)"));
    QString temp = pages;
    if (regexp.indexIn(temp) != -1) {
        pages.clear();
        pages.append(regexp.cap(1));
        pages.append(QChar(0x2011));
        pages.append(regexp.cap(2));
    }
}

//*****************************************************************************************
void Article::journal_input_correction(QString &jurnal){
    qDebug() << "jurnal_input_correction";
    title_input_correction(jurnal);
}
