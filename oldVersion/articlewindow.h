#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "literature.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    QMessageBox *mBox;
  Literature *litera;
  void add_items();
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
