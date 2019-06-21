#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->SaveFileButton->setDisabled(true);
    ui->textEdit->tabChangesFocus();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_LoadFileButton_clicked() {
    QString fileContent;
    QString filename = QFileDialog::getOpenFileName(this, "Open File...");

    if (filename.isEmpty()) return;
    currentFile = filename;
    qDebug() << currentFile;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    QString line = in.readLine();

    while (!line.isNull()) {
        fileContent.append(line);
        line = in.readLine();
    }

    file.close();

    ui->textEdit->clear();
    ui->textEdit->setPlainText(fileContent);
    ui->SaveFileButton->setDisabled(false);
}

void Widget::on_SaveFileButton_clicked() {
    QFile file(currentFile);

    file.remove();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out << ui->textEdit->toPlainText() << "\n";

    file.close();
}

void Widget::on_SaveAsButton_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save As...");
    if (filename.isEmpty()) return;

    QFile file(filename);

    if (file.exists()) file.remove();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) return;

    QTextStream out(&file);
    out << ui->textEdit->toPlainText() << "\n";

    file.close();
}

void Widget::on_fontSizeSB_valueChanged(int) {
    ui->textEdit->setFontPointSize(ui->fontSizeSB->value());
}

void Widget::on_fontCB_currentFontChanged(const QFont &f) {
    ui->textEdit->setFont(f);
}

void Widget::on_boldButton_clicked() {
    if (ui->textEdit->fontWeight() == QFont::Bold) ui->textEdit->setFontWeight(QFont::Normal);
    else ui->textEdit->setFontWeight(QFont::Bold);
}

void Widget::on_underlineButton_clicked() {
    if (ui->textEdit->fontUnderline()) ui->textEdit->setFontUnderline(false);
    else ui->textEdit->setFontUnderline(true);
}

void Widget::on_italicButton_clicked() {
    if (ui->textEdit->fontItalic()) ui->textEdit->setFontItalic(false);
    else ui->textEdit->setFontItalic(true);
}
