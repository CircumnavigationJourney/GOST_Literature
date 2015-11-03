#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QGridLayout>

#include "patentwidget.h"
#include "journalarticlewidget.h"
#include "popularmistakesui.h"
#include "mergelitlists.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
QGridLayout *mainWindowGridLayout;
QTabWidget *LitTypeWidgetsContainer;
JournalArticleWidget *journalArctileUI;
PatentWidget *patentUI;
PopularMistakesUI *mistakesUI;
MergeLitLists *mergeListsUI;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
