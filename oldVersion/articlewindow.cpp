#include "articlewindow.h"
#include "ui_mainwindow.h"

QString emptyField = "Нужно заполнить поле %1";

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  litera = new Literature;
  mBox = new QMessageBox;

  //  if (litera->Load_data_from_file(QString("infile.txt")))
  //      litera->main_string_normalization((*litera->main_string_data));
  //   add_items();
  //else litera->main_string_normalization(ui->input_text->toPlainText());
  //qDebug() << litera->temp_string_list->size();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked() //Кнопка генерации ГОСТа
{

  QString t_author;
  QString t_title;
  QString t_year;
  QString t_pages;
  QString t_jurnal;
  QString t_volume;
  QString t_number;
  //ui->listWidget->addItem(litera->author_normalization(ui->author->text()));
  if (ui->author->text().isEmpty()){
      mBox->setText(emptyField.arg("\"Авторы\" (первое)"));
      mBox->exec();
      return;
    }
  else
    t_author = ui->author->text();
  if (ui->nazva->text().isEmpty()){
      mBox->setText(emptyField.arg("\"Название\" (второе)"));
      mBox->exec();
      return;
    }
  else
    t_title = ui->nazva->text();
  if (ui->jurnal->text().isEmpty()){
      mBox->setText(emptyField.arg("\"Назавание Журнала\" (третье)"));
      mBox->exec();
      return;
    }
  else
    t_jurnal = ui->jurnal->text();

  if (ui->year->text().isEmpty()){
      mBox->setText(emptyField.arg("\"Год издательства\" (шестое)"));
      mBox->exec();
      return;
    }
  else if (!ui->year->text().contains(QRegExp("\\d{4,}"))){
      mBox->setText("Не корректно введен год издательства");
      mBox->exec();
      return;
    }
  else
    t_year = ui->year->text();
  if (ui->pages->text().isEmpty()){
      mBox->setText(emptyField.arg("\"Страницы\" (седьмое)"));
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

  QString str = litera->generate_GOST(t_author, t_title, t_year, t_volume, t_number, t_pages, t_jurnal);
  ui->input_text->clear();
  ui->input_text->setText(str);
}

void MainWindow::on_pushButton_3_clicked()
{
  litera->main_string_normalization(QString(ui->input_text->toPlainText()));
  add_items();

}

void MainWindow::add_items(){
  QString spisok;
  for (int i = 0; i < litera->temp_string_list->size(); i++){

      ui->listWidget->addItem(litera->temp_string_list->at(i));
      spisok.push_back((*litera->temp_string_list)[i] + "\n");
    }

  ui->textEdit->clear();
  ui->textEdit->setText(spisok);
}

void MainWindow::on_pushButton_2_clicked() //clear lineEdits
{
  ui->author->clear();
  ui->jurnal->clear();
  ui->nazva->clear();
  ui->year->clear();
  ui->pages->clear();
  ui->T->clear();
  ui->number->clear();
}
