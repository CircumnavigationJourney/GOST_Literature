#ifndef JOURNALARTICLEWIDGET_H
#define JOURNALARTICLEWIDGET_H

#include <QWidget>
#include "article.h"

namespace Ui {
class JournalArticleWidget;
}

class JournalArticleWidget : public QWidget
{
    Q_OBJECT
 private:
    QList<Biblio::Article> articlesList;
    Biblio::Article* article;
    QMessageBox *mBox;
public:

    QString *emptyField;
    explicit JournalArticleWidget(QWidget *parent = 0);
    ~JournalArticleWidget();
    //void add_items();

private slots:
    void on_pushButton_2_clicked();
   // void on_pushButton_3_clicked();
    void on_pushButton_clicked();

private:
    Ui::JournalArticleWidget *ui;
};

#endif // JOURNALARTICLEWIDGET_H
