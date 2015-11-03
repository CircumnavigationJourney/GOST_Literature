#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    LitTypeWidgetsContainer = new QTabWidget(this);
    journalArctileUI = new JournalArticleWidget(LitTypeWidgetsContainer);
    patentUI = new PatentWidget(LitTypeWidgetsContainer);
    mistakesUI = new PopularMistakesUI(LitTypeWidgetsContainer);
    mergeListsUI = new MergeLitLists(LitTypeWidgetsContainer);

//добавление юзер интерфейсов для работы с различными типами библиографии
    LitTypeWidgetsContainer->addTab(journalArctileUI, tr("Статья из Журнала"));
    LitTypeWidgetsContainer->addTab(patentUI, tr("Патент"));
    LitTypeWidgetsContainer->addTab(mistakesUI, tr("Исправление Ошибок Форматирования"));
    LitTypeWidgetsContainer->addTab(mergeListsUI, tr("Объединить Списки"));
    this->setCentralWidget(LitTypeWidgetsContainer);
    LitTypeWidgetsContainer->setCurrentWidget(mergeListsUI);
    QIcon windowIcon(":images/windowIcon.png");
    setWindowIcon(windowIcon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

