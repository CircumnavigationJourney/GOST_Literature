#include "popularmistakesui.h"
#include "ui_popularmistakesui.h"
#include "biblio.h"
PopularMistakesUI::PopularMistakesUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopularMistakesUI)
{
    ui->setupUi(this);
    ui->inputText->setPlaceholderText(tr("Вставить текст для исправления сюда"));
}

PopularMistakesUI::~PopularMistakesUI()
{
    delete ui;
}

void PopularMistakesUI::on_MistakesCorrectionButton_clicked()
{
    if(ui->inputText->toPlainText().isEmpty()) return;

    QString inputText = ui->inputText->toHtml();
    Biblio::Literature::deleteExcessControlSymbols(inputText);
    QStringList *result = Biblio::main_string_normalization(inputText);
    QString resultStr = result->join("\n");
    delete result;
    ui->outputText->setText(resultStr);
}
