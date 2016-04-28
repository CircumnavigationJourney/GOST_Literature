#include "journalarticlewidget.h"
#include "ui_journalarticlewidget.h"
#include "article.h"



JournalArticleWidget::JournalArticleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JournalArticleWidget)
{
    ui->setupUi(this);
  emptyField = new QString("Нужно заполнить поле %1");
  //article = new Biblio::Article;
  mBox = new QMessageBox;

  articlesList = QSharedPointer<QList<Biblio::Article>> (new QList<Biblio::Article>) ;
  articlesModel.setData(articlesList);
   ui->listView->setModel(&articlesModel);
  //  if (article->Load_data_from_file(QString("infile.txt")))
  //      article->main_string_normalization((*article->main_string_data));
  //   add_items();
  //else article->main_string_normalization(ui->input_text->toPlainText());
  //qDebug() >> article->temp_string_list->size();
}

JournalArticleWidget::~JournalArticleWidget()
{
    delete ui;
    delete emptyField;
    //delete article;
    delete mBox;
}


void JournalArticleWidget::on_pushButton_clicked() //Кнопка генерации ГОСТа
{

  QString t_author;
  QString t_title;
  QString t_year;
  QString t_pages;
  QString t_jurnal;
  QString t_volume;
  QString t_number;
  //ui->listWidget->addItem(article->author_normalization(ui->author->text()));
  if (ui->author->text().isEmpty()){
      mBox->setText(emptyField->arg("\"Авторы\" (первое)"));
      mBox->exec();
      return;
    }
  else
    t_author = ui->author->text();
  if (ui->nazva->text().isEmpty()){
      mBox->setText(emptyField->arg("\"Название\" (второе)"));
      mBox->exec();
      return;
    }
  else
    t_title = ui->nazva->text();
  if (ui->jurnal->text().isEmpty()){
      mBox->setText(emptyField->arg("\"Назавание Журнала\" (третье)"));
      mBox->exec();
      return;
    }
  else
    t_jurnal = ui->jurnal->text();

  if (ui->year->text().isEmpty()){
      mBox->setText(emptyField->arg("\"Год издательства\" (шестое)"));
      mBox->exec();
      return;
    }
  else if (!ui->year->text().contains(QRegExp("\\d"))){
      mBox->setText("Не корректно введен год издательства");
      mBox->exec();
      return;
    }
  else
    t_year = ui->year->text();
  if (ui->pages->text().isEmpty()){
      mBox->setText(emptyField->arg("\"Страницы\" (седьмое)"));
      mBox->exec();
      return;
    }
  else  if (!ui->pages->text().contains(QRegExp("\\d"))){
      mBox->setText("Не корректные номера страниц");
      mBox->exec();
      return;
    }
  else
    t_pages = ui->pages->text();


  t_volume = ui->T->text();
  t_number = ui->number->text();

  //TEST
  //    QString t_author("Takeshi Sakurai2, Akira Amemiya3, Makoto Ishii, Ichiyo Matsuzaki4, Richard M Chemelli, Hirokazu Tanaka, S.Clay Williams, James A Richardson, Gerald P Kozlowski, Shelagh Wilson, Jonathan R.S Arch, Robin E Buckingham, Andrea C Haynes, Steven A Carr, Roland S Annan, Dean E McNulty, Wu-Schyong Liu, Jonathan A Terrett, Nabil A Elshourbagy, Derk J Bergsma, Masashi Yanagisawa");
  //    QString t_title("Orexins and Orexin Receptors: A Family of Hypothalamic Neuropeptides and G Protein-Coupled Receptors that Regulate Feeding Behavior");
  //    QString t_year("1998");
  //    QString t_pages("p573–585,");
  //    QString t_jurnal("Cell Press.");
  //    QString t_volume(" 92,");
  //    QString t_number("4,");

  Biblio::Article article(t_author, t_title, t_year, t_volume, t_number, t_pages, t_jurnal);
  articlesModel.append(article);
  QString str = article.generate_GOST();

  ui->input_text->clear();
  ui->input_text->setText(str);

}

//void JournalArticleWidget::on_pushButton_3_clicked()
//{
//  //article->main_string_normalization(QString(ui->input_text->toPlainText()));
//  //add_items();

//}

//void JournalArticleWidget::add_items(){
//  QString spisok;
//  for (int i = 0; i < article->temp_string_list->size(); i++){

//      ui->listWidget->addItem(article->temp_string_list->at(i));
//      spisok.push_back((*article->temp_string_list)[i] + "\n");
//    }

//  ui->textEdit->clear();
//  ui->textEdit->setText(spisok);
//}

void JournalArticleWidget::on_pushButton_2_clicked() //clear lineEdits
{
  ui->author->clear();
  ui->jurnal->clear();
  ui->nazva->clear();
  ui->year->clear();
  ui->pages->clear();
  ui->T->clear();
  ui->number->clear();
}

