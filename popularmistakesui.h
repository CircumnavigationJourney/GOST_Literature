#ifndef POPULARMISTAKESUI_H
#define POPULARMISTAKESUI_H

#include <QWidget>

namespace Ui {
class PopularMistakesUI;
}

class PopularMistakesUI : public QWidget
{
    Q_OBJECT

public:
    explicit PopularMistakesUI(QWidget *parent = 0);
    ~PopularMistakesUI();

private slots:
  void on_MistakesCorrectionButton_clicked();

private:
    Ui::PopularMistakesUI *ui;
};

#endif // POPULARMISTAKESUI_H
