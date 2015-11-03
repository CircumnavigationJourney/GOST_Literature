#include "patentwidget.h"
#include "ui_patentwidget.h"

PatentWidget::PatentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatentWidget)
{
    ui->setupUi(this);
}

PatentWidget::~PatentWidget()
{
    delete ui;
}
