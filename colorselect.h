#ifndef COLORSELECT_H
#define COLORSELECT_H

#include <QWidget>
#include <QColor>
#include <QPalette>
#include <QDebug>
#include <QDialog>
#include <QDebug>
#include <QCloseEvent>
namespace Ui {
class ColorSelect;
}

class ColorSelect : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
public:
    explicit ColorSelect(QColor color, QWidget *parent = 0);
    ~ColorSelect();
    QColor color() {
        return m_color;
    }
signals:
    void colorChanged(QColor);
    void setColor(QColor);
private slots:
    void onColorChanged();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void closeEvent(QCloseEvent *event);
    QColor m_color;
    Ui::ColorSelect *ui;
};

#endif // COLORSELECT_H
