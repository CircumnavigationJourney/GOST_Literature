#include "mergelitlists.h"
#include "ui_mergelitlists.h"
using namespace Biblio;
MergeLitLists::MergeLitLists(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MergeLitLists)
{
    ui->setupUi(this);
    QString placeHolderText = "Объеденить два списка - это значит создать новый список,\nвключающий все элементы из Списка 1 и Списка 2\nкроме повторяющихся\n(Результат автоматически копируется в буфер обмена после нажатия на кнопку ";
    placeHolderText.append(ui->pushButton->text()).append(")");
    ui->resultText->setPlaceholderText(placeHolderText);
    ui->pushButton->setToolTip(placeHolderText);
    ui->horizontalSlider->setRange(40, 100);
    ui->horizontalSlider->setValue(75);

    ui->progressBar->hide();
    litera = new Biblio::Literature;
    //connect(litera, SIGNAL(progress(int)), ui->progressBar,SLOT(setValue(int)));
    connect(litera, SIGNAL(progress(int, Biblio::Literature::Stage)), SLOT(set_progress(int,Biblio::Literature::Stage)));
    highlightTextColor.setRgb(153, 255, 153);

    QPalette pal = ui->pushButton_3->palette();
    pal.setColor(QPalette::Button, highlightTextColor);
    ui->pushButton_3->setPalette(pal);
    ui->pushButton_3->update();
    currStage = Biblio::Literature::Stage::Initial;
}

MergeLitLists::~MergeLitLists()
{
    delete ui;
}

void MergeLitLists::on_pushButton_clicked()
{
    if(ui->list1Text->toPlainText().size() < MINIMUM_INPUT_TEXT_SIZE ||
            ui->list2Text->toPlainText().size() < MINIMUM_INPUT_TEXT_SIZE)
        return;
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    QString list1 = ui->list1Text->toHtml();
    QString list2 = ui->list2Text->toHtml();
    result = litera->getMergeList(list1, list2);
    output = result.resultList.data()->join("\n");
    ui->resultText->document()->setPlainText(output);

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(output);
    //Подсветка новых элементов в объединенном тексте
    highlightText();

    ui->progressBar->hide();
    //сообщение об результатах объединения
    report = new QMessageBox;
    QIcon winIcon(":images/windowIcon.png");
    report->setWindowTitle("Детали Объединения");
    report->setWindowIcon(winIcon);
    report->setText(result.report);
    report->setModal(true);
    report->show();
    report->setDefaultButton(QMessageBox::Yes);
    if(report->exec() == QMessageBox::Yes){
        report->deleteLater();
    }
    else report->deleteLater();
    ui->progressLabel->setText("");
}

void MergeLitLists::on_pushButton_2_clicked()
{
    ui->list1Text->clear();
    ui->list2Text->clear();
    ui->resultText->clear();
}

//Изменение процента соответствия строк (названия в случае если удается его определить)
void MergeLitLists::on_horizontalSlider_valueChanged(int value)
{
    Biblio::COMPARISON_PRECISION = value;
    ui->precision->setText(QString(QString::number(value) +"%"));
}

void MergeLitLists::on_pushButton_3_clicked()
{


    ColorSelect *sel = new ColorSelect(highlightTextColor);
    sel->setWindowIcon(QIcon(":images/windowIcon.png"));
    //colorDialog = QSharedPointer<ColorSelect>(sel);
    //connect(colorDialog.data(), SIGNAL(setColor(QColor)), this, SLOT(on_highlight_Color_Changed(QColor)));
    connect(sel, SIGNAL(setColor(QColor)), this, SLOT(on_highlight_Color_Changed(QColor)));
    //    colorDialog.data()->show();
    sel->show();
}

void MergeLitLists::on_highlight_Color_Changed(QColor newColor){
    highlightTextColor = newColor;
    QPalette pal = ui->pushButton_3->palette();
    pal.setColor(QPalette::Button, highlightTextColor);
    ui->pushButton_3->setPalette(pal);
    ui->pushButton_3->update();

    highlightText();
}

void MergeLitLists::highlightText(){
    if(output.isEmpty()) return;
    //На случай, если текст браузер будет заменен на текст эдит, при изменении цвета подсветки нужно учитывать его размер
    if(output.size() != ui->resultText->toPlainText().size()){

        QString err("Текст в котором используется подсветка был %1\nхотите его вернуть?");
        QString property;
        if(ui->resultText->toPlainText().size() < MINIMUM_INPUT_TEXT_SIZE)
            property = "удален";
        else property = "изменен";
        err = err.arg(property);
        QMessageBox *mess = new QMessageBox;
        mess->setWindowTitle("Внимание");
        QIcon icon(":images/windowIcon.png");
        mess->setWindowIcon(icon);
        mess->setText(err);
        mess->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        if(mess->exec() == QMessageBox::Yes){
            ui->resultText->document()->setPlainText(output);
            mess->deleteLater();
        }
        else {
            mess->deleteLater();
            return;
        }
    }
    QTextDocument * currentDoc = ui->resultText->document();
    QTextCursor highlightCursor(currentDoc);
    //QTextCursor redoCursor(currentDoc);

    //redoCursor.beginEditBlock();
    highlightCursor.setPosition(output.size() - result.newElements.data()->join("\n").size(), QTextCursor::MoveAnchor);
    highlightCursor.setPosition(output.size(), QTextCursor::KeepAnchor);
    QTextCharFormat plainFormat(highlightCursor.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setBackground(highlightTextColor);
    highlightCursor.mergeCharFormat(colorFormat);

    // redoCursor.endEditBlock();
}

void MergeLitLists::set_progress(int value, Biblio::Literature::Stage stage){

    if(currStage != stage){
        currStage = stage;
        switch(currStage){
        case Literature::Stage::ListCheck_1:
            ui->progressLabel->setText(QString("%1 Идет обработка...").arg(ui->list1Name->text())); break;
        case Literature::Stage::ListCheck_2:
            ui->progressLabel->setText(QString("%1 Идет обработка...").arg(ui->list2Name->text())); break;
        case Literature::Stage::MergeLists:
            ui->progressLabel->setText(QString("%1 и %2 Идет объединение...").arg(ui->list1Name->text()).arg(ui->list2Name->text())); break;
        case Literature::Stage::Initial:
            ui->progressLabel->setText(""); break;
        default: ui->progressLabel->setText("");
        }

    }
ui->progressBar->setValue(value);
}
