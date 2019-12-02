#include "widget.h"                                                             // include the header file for this project
#include "ui_widget.h"                                                          // include header file with QT Designer elements
#include <QDebug>                                                               // include QDebug for debug messages
#include <QFileDialog>                                                          // include QFileDialog to enable user choice of file/directory
#include <QFile>                                                                // inlcude QFile to enable read/write to files
#include <QTextStream>                                                          // include QTextStream to stream text to/from the destination/source

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);                                                          // set up the UI for this application
    ui->SaveFileButton->setDisabled(true);                                      // disable SaveFileButton (will be renabled once file chosen or new one created)
    ui->textEdit->tabChangesFocus();                                            // toggles whether pressing tab key removes focus from QTextEdit (now false)
}

Widget::~Widget()                                                               // destructor for this widget application
{
    delete ui;
}

void Widget::on_LoadFileButton_clicked()                                        // definition for loadFileButton_clicked() slot
{
    QString fileContent;                                                        // create QString for containing the content of a file
    QString filename = QFileDialog::getOpenFileName(this, "Open File...");      // create QString to store the filename using getOpenFileName()

    if (filename.isEmpty()) return;                                             // if the filename is empty then return from function
    currentFile = filename;                                                     // store filename into currentFile (this is then used for Save Button)
    qDebug() << currentFile;                                                    // use QDebug to output the currentFile to the console

    QFile file(filename);                                                       // create QFile object using the filename
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;               // if opening the file with ReadOnly and Text doesn't work, return from function

    QTextStream in(&file);                                                      // create QTextStream object for reading from the file
    QString line = in.readLine();                                               // create QString object to store the first line from the file

    while (!line.isNull()) {                                                    // while the line read from the file is not empty:
        fileContent.append(line);                                               //    append line to fileContent
        line = in.readLine();                                                   //    read the next line
    }

    file.close();                                                               // close the connection to the file

    ui->textEdit->clear();                                                      // clear the QTextEdit contents
    ui->textEdit->setText(fileContent);                                         // set file's text as text within the QTextEdit
    ui->SaveFileButton->setDisabled(false);                                     // enable the Save File button
}

void Widget::on_SaveFileButton_clicked()                                        // definition for saveFileButton_clicked() slot
{
    QFile file(currentFile);                                                    // create QFile object using the current filepath

    file.remove();                                                              // remove the current file

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;              // if the file cannot be opened in WriteOnly and Text modes then cancel

    QTextStream out(&file);                                                     // create a QTextStream object to stream into QFile
    out << ui->textEdit->toHtml() << "\n";                                      // send all of the textEdits content to the file

    file.close();                                                               // close the connection to the file
}

void Widget::on_SaveAsButton_clicked()                                          // definition for SaveAsButton_clicked() slot
{
    QString filename = QFileDialog::getSaveFileName(this, "Save As...");        // create QString for the filename of the file to be saved (retrieved via QFileDialog)
    if (filename.isEmpty()) return;                                             // if the filename is empty then cancel the operation

    QFile file(filename);                                                       // create a QFile object using the QString filename

    if (file.exists()) file.remove();                                           // if the file exists then remove it so the new content can be written as new

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) return;  // if the file cannot be opened in WriteOnly/Text/Append mode then cancel

    QTextStream out(&file);                                                     // create a QTextStream object to write content to the file
    out << ui->textEdit->toHtml() << "\n";                                      // write the content of the textEdit to the file

    file.close();                                                               // close the connection to the file
}

void Widget::on_fontSizeSB_valueChanged(int) {                                  //
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
