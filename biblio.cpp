#include "biblio.h"
namespace Biblio {
double COMPARISON_PRECISION = 75.0; // 75%
QString programmVersion("Lit_03");
QRegExp titleControlPoint("(?:\\[Text\\])|(?:\\[Текст\\])|(?:\\[Електронный ресурс\\])");
QStringList* main_string_normalization(QString &temp){
    //пеержиток прошлой реализации
    QStringList *temp_string_list = new QStringList;
    //qDebug() >> "main_string_normalization()";
    //Literature::deleteExcessControlSymbols(temp);
    //    while (temp.indexOf("  ") + 1)
    //      temp.replace("  ", " ");
    //    for (int i = 0; i < temp.size(); ++i){
    //        if ((temp[i] == '\n' && temp[i-1] == ' ')
    //            || (temp[i] == '\n' && temp[i-1] == ','))
    //          {
    //            temp.remove(i, 1);
    //            i--;
    //          }
    //      }
    //    QRegExp multipleNewLines("\\n{2,}");
    //    QRegExp multipleSpaces("\\s{2,}");
    //    temp.replace(multipleNewLines, "\n");
    //    temp.replace(multipleSpaces, " ");
    //чтобы обрабатывать каждый экземпляр по отдельности
    //это нужно чтобы решить проблему со вставкой сшивателя
    //после фамилии первого автора, после которой идет запятая

    //QChar(0x2d) - дефис
    //QChar(0x2116) - №
    //  QChar(0x2010)	8208	HYPHEN	‐
    //  QChar(0x2011)	8209	NON-BREAKING HYPHEN	‑ дефис не переносящийся на следующую строку
    //  QChar(0x2012)	8210	FIGURE DASH	‒
    //  QChar(0x2013)	8211	EN DASH	–
    //  QChar(0x2014)	8212	EM DASH	—
    //  QChar(0x2015)	8213	HORIZONTAL BAR	―
    QString tire("[");
    tire.append(QChar(0x2d));
    tire.append(QChar(0x2010));
    tire.append(QChar(0x2011));
    tire.append(QChar(0x2012));
    //tire.append(QChar(0x2013));
    tire.append(QChar(0x2014));
    tire.append(QChar(0x2015));
    tire.append(QChar(']'));

    QString widetire(QChar(0x2013));
    QRegExp regTire(tire);
    temp = temp.replace(regTire,widetire);
    //TODO для оптимизации можно заменить манипуляции с памятью и стринг листом, чтобы функция вернула стринг лист,
    //но придется сделать temp_string_list объектом а не указателем (переписать моменты с temp_string_list где он используется как указатель)
    if (temp_string_list != nullptr)
        delete temp_string_list;
    temp_string_list = new QStringList;

    (*temp_string_list) = temp.split("\n", QString::SplitBehavior::SkipEmptyParts);

    for (int n = 0; n < (temp_string_list)->size(); ++n)
    {
        for (int i = 1; i < (*temp_string_list)[n].size(); ++i)
        {
            if ((*temp_string_list)[n][i] == '–'
                    || ((*temp_string_list)[n][i] == '/'
                        || (*temp_string_list)[n][i] == ':'
                        || (*temp_string_list)[n][i] == QChar(0x2013))
                    && (*temp_string_list)[n][i-1] == ' ')
                (*temp_string_list)[n][i-1] = QChar::Nbsp;
            //          else if ((*temp_string_list)[n][i] == QChar(0x2d)
            //                   && (*temp_string_list)[n][i-1].isNumber())
            //            (*temp_string_list)[n][i] = QChar(0x2011);
            else if ((*temp_string_list)[n][i] == QChar(0x2116)
                     && (*temp_string_list)[n][i+1] == ' ')
                (*temp_string_list)[n][i+1] = QChar::Nbsp;
            else if ((*temp_string_list)[n][i].isUpper()
                     && (i+3) < (*temp_string_list)[n].size()
                     && (*temp_string_list)[n][i+1] == '.'
                     && (*temp_string_list)[n][i+2].isUpper()
                     && ((*temp_string_list)[n][i+3].isSpace() || (*temp_string_list)[n][i+3] == '.')){
                (*temp_string_list)[n].insert(i+2, QChar::Nbsp);
                i++;
            }
            //СЛЕДУЮЩЕЕ УСЛОВИЕ не корректно тк срабатывает и в случаях, когда имя автора идет вначале, потом его инициалы, и сшивка
            else if ((*temp_string_list)[n][i].isUpper()
                     && (i+4) < (*temp_string_list)[n].size()
                     && (*temp_string_list)[n][i+1] == '.'
                     && (*temp_string_list)[n][i+2].isSpace()
                     && (*temp_string_list)[n][i+3].isUpper()) //это то из-за чего весь сыр бром
                // && ((*temp_string_list)[n][i+4].isSpace() || (*temp_string_list)[n][i+4] == '.'))
            {
                if (i > 20) //тут идет волшебное число, до 20 символов - начало
                    (*temp_string_list)[n][i+2] = QChar::Nbsp;
                else  (*temp_string_list)[n][i-1] = QChar::Nbsp;
            }
            else if (((*temp_string_list)[n][i] == QChar(0x2013) || (*temp_string_list)[n][i] == QChar(0x2116) || (*temp_string_list)[n][i] == QChar(0x2d))
                     && (*temp_string_list)[n][i-1].isNumber()
                     && (*temp_string_list)[n][i+1].isNumber()){
                (*temp_string_list)[n][i] = QChar(0x2011);
                //qDebug() >> (*temp_string_list)[n][i+1].isNumber() >> QString("=") >> (*temp_string_list)[n][i-1] >> QString(" ") >> (*temp_string_list)[n][i+1];
            }
            else if ((*temp_string_list)[n][i].isNumber()
                     && i+4 < (*temp_string_list)[n].size()
                     && ((*temp_string_list)[n][i+1] == ' ' || (*temp_string_list)[n][i+1] == QChar::Nbsp)
                     && (*temp_string_list)[n][i+2] == QChar(0x2013) /*|| (*temp_string_list)[n][i+2] == QChar(0x2116) || (*temp_string_list)[n][i+2] == QChar(0x2d)*/
                     && ((*temp_string_list)[n][i+3] == ' ' || (*temp_string_list)[n][i+3] == QChar::Nbsp)
                     && (*temp_string_list)[n][i+4].isNumber()){
                // осторожно, костыль %1
                (*temp_string_list)[n][i+1] = QChar(9792);
                (*temp_string_list)[n][i+2] = QChar(9792);
                (*temp_string_list)[n][i+3] = QChar(9792);
            }
            else if ((*temp_string_list)[n][i].isNumber()
                     && i+3 < (*temp_string_list)[n].size()
                     && ((*temp_string_list)[n][i+1] == ' ' || (*temp_string_list)[n][i+1] == QChar::Nbsp)
                     && (*temp_string_list)[n][i+2] == QChar(0x2013)
                     && (*temp_string_list)[n][i+3].isNumber()){

                // осторожно, костыль %1
                (*temp_string_list)[n][i+1] = QChar(9792);
                (*temp_string_list)[n][i+2] = QChar(9792);
                (*temp_string_list)[n].insert((i+3),QChar(9792));
            }
        }
        QString before = "♀♀♀"; // осторожно, костыль %1
        QString after = QChar(0x2011);
        (*temp_string_list)[n] = (*temp_string_list)[n].replace(before, after);
        (*temp_string_list)[n] = (*temp_string_list)[n].replace('\t', "");
    }
    //потеряный нон брейкабл дефис нужно восстановить (он может быть автоматически заменен на пробел или нонбрейкабл пробел
    QRegExp lostedHyphen("(\\d+[  ]\\d+)");
    for(int count = 0; count < temp_string_list->size(); ++count){
        if(temp_string_list->at(count).contains(lostedHyphen)){
            int pos = 0;
            //qDebug() >> pos >> "\t" >> temp_string_list->at(count);
            while((pos = lostedHyphen.indexIn(temp_string_list->at(count)), pos) != -1){
                for(; pos < temp_string_list->at(count).size(); ++pos){
                    if(temp_string_list->at(count).at(pos) == QChar::Space ||
                            temp_string_list->at(count).at(pos) == QChar::Nbsp){
                        (*temp_string_list)[count][pos] = QChar(0x2011);
                        break;
                    }
                }
                pos += lostedHyphen.matchedLength();
            }
        }
    }

    //нон брейкабл пробел перед страницами (P. || p. || C. || c.)

    QRegExp pagesProblem("[PCРС]. \\d+");
    QRegExp pagesProblemAtTheEnd("[pcрс]");
    for(int count = 0; count < temp_string_list->size(); ++count){
            int pos = pagesProblem.indexIn(temp_string_list->at(count));
            int pos2 = temp_string_list->at(count).size()-2;
            if(pos != -1 && pos+2 < temp_string_list->at(count).size()){
                if((*temp_string_list)[count][pos+2] == QChar::Space){
                    (*temp_string_list)[count][pos+2] = QChar::Nbsp;
                }
            }
            else if(pos2 > 0 &&
                    ((pos2 = pagesProblemAtTheEnd.indexIn(temp_string_list->at(count), pos2)) != -1)){
                //qDebug() << (*temp_string_list)[count][pos2-1] >> "\t" >> temp_string_list->at(count);
                    if((*temp_string_list)[count][pos2-1] == QChar::Space){
                        (*temp_string_list)[count][pos2-1] = QChar::Nbsp;
                    }
                }
            else {
               // qDebug() >> "ОШИБКА в : " >> temp_string_list->at(count);
                QMessageBox mess;
                QString messageText =  "ОШИБКА в : " + temp_string_list->at(count);
                mess.setText(messageText);
                mess.setStandardButtons(QMessageBox::Yes);
                if(mess.exec() == QMessageBox::Yes)
                    QApplication::quit();
            }

        }

        return temp_string_list;
    }
}
