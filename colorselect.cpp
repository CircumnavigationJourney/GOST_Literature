#include "colorselect.h"
#include "ui_colorselect.h"

ColorSelect::ColorSelect(QColor color, QWidget *parent) :
    QDialog(0,  Qt::WindowTitleHint),
    m_color(color),
    ui(new Ui::ColorSelect)
{
    this->setModal(true);
    ui->setupUi(this);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui->spinBoxR->setValue(m_color.red());
    ui->spinBoxG->setValue(m_color.green());
    ui->spinBoxB->setValue(m_color.blue());
    connect(ui->spinBoxR, SIGNAL(valueChanged(int)), this, SLOT(onColorChanged()));
    connect(ui->spinBoxG, SIGNAL(valueChanged(int)), this, SLOT(onColorChanged()));
    connect(ui->spinBoxB, SIGNAL(valueChanged(int)), this, SLOT(onColorChanged()));
    onColorChanged();

}

ColorSelect::~ColorSelect()
{

    delete ui;
}

void ColorSelect::onColorChanged(){
    m_color.setRgb(ui->spinBoxR->value(), ui->spinBoxG->value(), ui->spinBoxB->value());

    QPalette pal = ui->displayWidget->palette();
    pal.setColor(QPalette::Window, m_color);
    ui->displayWidget->setPalette(pal);
    emit colorChanged(m_color);

}

void ColorSelect::on_pushButton_clicked()
{
    emit setColor(m_color);
    this->deleteLater();
}

void ColorSelect::on_pushButton_2_clicked()
{
    this->deleteLater();
}
 void ColorSelect::closeEvent(QCloseEvent *event){
     //Q_UNUSED(event)
   this->deleteLater();
 }
