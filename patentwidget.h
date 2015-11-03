#ifndef PATENTWIDGET_H
#define PATENTWIDGET_H

#include <QWidget>

namespace Ui {
class PatentWidget;
}

class PatentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PatentWidget(QWidget *parent = 0);
    ~PatentWidget();

private:
    Ui::PatentWidget *ui;
};

#endif // PATENTWIDGET_H
