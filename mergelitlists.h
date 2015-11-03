#ifndef MERGELITLISTS_H
#define MERGELITLISTS_H

#include <QWidget>
#include "colorselect.h"
#include "biblio.h"
namespace Ui {
class MergeLitLists;
}

class MergeLitLists : public QWidget
{
    Q_OBJECT
    Biblio::Literature::Stage currStage;
    const int MINIMUM_INPUT_TEXT_SIZE = 5;
    Biblio::Literature::MergeResult result;
    QColor highlightTextColor;
    QSharedPointer<ColorSelect> colorDialog;
    QMessageBox *report;
    QString output;
    int outputSize;
    bool outputSizeChanged = false;
public:
    explicit MergeLitLists(QWidget *parent = 0);
    ~MergeLitLists();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_3_clicked();
    void on_highlight_Color_Changed(QColor newColor);
    void set_progress(int value, Biblio::Literature::Stage stage);
private:
    void highlightText();
    Biblio::Literature *litera;
    Ui::MergeLitLists *ui;
};

#endif // MERGELITLISTS_H
