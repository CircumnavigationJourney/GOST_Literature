#include "article.h"
using namespace Biblio;

const int MIN_AUTH = 3; // максимальное число авторов, из-за которого нужно первого автора выставлять перед названием
const int ALL_AUTH = 4; // минимальное число авторов, из-за которого нужно перечислять всех авторов после названия,
//но не выставлять первого перед названием
Article::Article()
{
    temp_string_list = new QStringList;
    Main_list = new QList<QStringList>;
    //temp_item = new Bib_item;
}

Article::~Article()
{

}

//bool Article::Load_data_from_file(QString &filepath){

//  QFile in(filepath);
//  if (!in.open(QIODevice::ReadOnly)){
//      qDebug() << "cant open file " << filepath << "\n";
//      return 0;
//    }
//  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//  QTextStream in_stream(&in);
//  in_stream.setCodec(codec);
//  main_string_data = new QString;
//  *main_string_data = in_stream.readAll();
//  //main_string_normalization((*temp_string_list));

//  //  for (int i = 0; i < temp_string_list->size(); i++){

//  //      qDebug() << ((*temp_string_list)).at(i);

//  //    }
//}

//void Article::Save_data_to_file(QString &filepath){


//}

void Article::operate_str(QString& temp_str){
  //Наш ГОСТ институтский, задача рассортировать элементы списка литературы по строкам в QList<QStringList> *Main_list;

  //if (authors_more_3(temp_str));
  //  for (int i = 0; i < temp_str.size(); ++i){

  //      //some logic operate string 0xa0

  //    }
  // if (!Main_list->isEmpty()) Main_list[Main_list->size()-1].push_back(&(*temp_string_list));
  // else Main_list

}

int Article::authors_count(QString &authors){
  //Если авторов > 3
  //  QString eng = "[e";
  //  QString ru = "[и";
  //  QString authors = main_str.split("//").first();
  //  authors = authors.split("/").last();
  //  if ((main_str.indexOf(eng,0) + 1)
  //      || (main_str.indexOf(ru,0) + 1)){
  //      qDebug() << authors << "\t 4 or more\n";
  //      return 1;
  //    }
  //  if (authors.count(',') >= 3){
  //      qDebug() << authors << "\t 4 or more\n";
  //      return 1;
  //    }
  //  else {
  //      qDebug() << authors << "\t less 4\n";
  //      return 0;
  //    }
  //else qDebug() << "ERROR\t" << authors << "\t";
  qDebug() << authors.count(',')+1 << " authors";
  return (authors.count(',')+1);
}



QString Article::author_normalization(QString &author){


  //if (author.count(',') > 3)//////////////////////////////////////////////////////////////
  //author = author.split(author.lastIndexOf(',')).first();
  // цикл начинается не с первого символа
  for (int i = 1; i < author.size(); ++i)
    {
      if (author[i].isUpper() && author[i-1].isUpper()){

          author.insert(i, '.');
          author.insert(i+1, QChar::Nbsp);
          if (author[i+3] != '.')
            author.insert(i+3, '.');
          i+=2;
        }
      if (author[i] == '.' && (i+1 < author.size()) && author[i+1].isUpper())
        author.insert(i+1, QChar::Nbsp);
      if (author[i].isUpper() && (i+1 < author.size()) && author[i+1] == ','){
          author.insert(i+1, '.');
        }
      if (author[i] == QChar::Space && (i+2) < author.size() && author[i+1].isUpper() && (author[i+2] == '.' || author[i+2] == ','))
        author[i] = QChar::Nbsp;
    }
  return author;
}


bool Article::is_eng(QString &undefLangString) const {
  //для точной проверки нужно закидывать список авторов, но не название статьи
  //т.к. названия русских статей могут содержать английские буквы
  qDebug() << "is_eng()";
  QRegExp engletters("[a-z]|[A-Z]");
  qDebug() << undefLangString.contains(engletters);
  if(undefLangString.contains(engletters))
    return true;
  else return false;
}

//============================================================================================================================================
QString Article::generate_GOST(QString &authors, QString &name,QString &year,QString &T,QString &number, QString &pages,QString &jurnal){
  qDebug() << "generate_GOST()";
  //создание копий строк, чтобы обрабатывать их в функциях по ссылке
  QString _authors(authors);
  QString _title(name);
  QString _year(year);
  QString _volume(T);
  QString _number(number);
  QString _pages(pages);
  QString _jurnal(jurnal);
  QString result;

  //приведение всех элементов в надлежащий вид
  author_input_correction(_authors);
  title_input_correction(_title);
  year_input_correction(_year);
  volume_input_correction(_volume);
  number_input_correction(_number);
  pages_input_correction(_pages);
  jurnal_input_correction(_jurnal);

  //оформление по правилам (статья)
  //определение языка статьи
  int eng = is_eng(_authors);
  int authors_number = authors_count(_authors);
  QStringList authors_list;
  if (authors_number > 1)
    authors_list = _authors.split(", ");
  else if (authors_number == 1)
    authors_list.append(_authors);
  else qDebug() << "ERROR authors number is " << authors_number; //Error добавить вылетающее окно с ошибкой
  qDebug() << authors_list;
  //result = _title +" / "+_authors +" / "+ _jurnal+" / " + _year+" / " + _volume+": " + _number+" / "+ _pages;
  if (authors_number <= MIN_AUTH){
      result = authors_list.at(0) + " " +
          _title + (eng ? QString(" [Text]") : QString(" [Текст]")) + QChar::Nbsp + QString("/ ");
      result += authors_list.join(", ");
    }
  else if (authors_number == ALL_AUTH){
      result += _title + (eng ? QString(" [Text]") : QString(" [Текст]")) + QChar::Nbsp + QString("/ ");
      result += authors_list.join(", ");
    }
  else {
      result += _title + (eng ? QString(" [Text]") : QString(" [Текст]")) + QChar::Nbsp + QString("/ ");
      for (int i = 0; i < (MIN_AUTH); ++i){
          result += authors_list.at(i);
          qDebug() << i << " ";
          if (i != (MIN_AUTH-1))
            result += ", ";
        }
      result += (eng ? QString(" [et al]") : QString(" [и др.]"));
    }
  result += QChar::Nbsp + QString("// ") +
      _jurnal + QChar::Nbsp + QChar(0x2013) + QChar::Space +
      _year + QChar::Nbsp + QChar(0x2013) + QChar::Space +
      (eng? QString("Vol."):QString("Т.")) + QChar::Nbsp + _volume + QString(", №") + QChar::Nbsp +
      _number + QChar::Nbsp + QChar(0x2013) + QChar::Space +
      (eng? QString("P. "):QString("С. ")) + _pages + QString(".");

  return result;
}
//bool GOST_authors_more_3(QString & authors){
//}


//Функция нужна чтобы удалить все дополнительные элементы из имен авторов
//привести их к виду: "Имя|Инициалы Фамилия, Имя|Инициалы Фамилия, ... Имя|Инициалы Фамилия"
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

  QString Specials("(?:PhD)|(?:MBBS)|(?:MSc)|(?:DMRT)|[");
  Specials.append(QChar(42));
  Specials.append(QChar(8270));
  Specials.append(QChar(8224));
  //Specials.append(QChar(8266));
  Specials.append(QChar('⇑'));
  Specials.append(QChar(8657));
  Specials.append(QString("\\d"));
  Specials.append("]");

  QRegExp regexp(Specials);
  sourceString.remove(regexp);
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
  //точки после инициалов (к инициалам относится любай одиночная буква верхнего регистра
  //либо две буквы верхнего регистра идущие друг за другом без разделителей)
  QRegExp initials1("[A-Z]{2}|[А-Я]{2}");
  QRegExp initials2("(?:[A-Z][,\\s])|(?:[А-Я][,\\s])");
  while (sourceString.contains(initials1)){
      int i = sourceString.indexOf(initials1);
      sourceString.insert(i + 1, QChar::Space);
      sourceString.insert(i + 3, QChar::Space);
    }
  while (sourceString.contains(initials2))
    sourceString.insert(sourceString.indexOf(initials2) + 1, QChar('.'));
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
  QRegExp upperLetter("(?:(?!^)[A-Z])|(?:(?!^)[А-Я])");// все заглавные буквы кроме той, с которой начинается строка
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


void Article::year_input_correction(QString &year){

  qDebug() << "year_input_correction()";
  //удалить все лишнее
  QRegExp regexpNotYear("(?:[\\s^\\D]\\d{1,3}[\\D&])");
  QRegExp regexp("(?:\\D)");
  year.remove(regexpNotYear);
  year.remove(regexp);
}


void Article::number_input_correction(QString &number){

  qDebug() << "number_input_correction()";
  QRegExp regexp("(?:\\D)");
  number.remove(regexp);
}


void Article::volume_input_correction(QString &vol){

  qDebug() << "volume_input_correction()";
  //  QRegExp regexp("(?:\\D)");
  //  vol.remove(regexp);
  number_input_correction(vol);
}


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


void Article::jurnal_input_correction(QString &jurnal){
  qDebug() << "jurnal_input_correction";
  title_input_correction(jurnal);
}
