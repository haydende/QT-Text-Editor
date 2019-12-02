#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    QString currentFile;                                                    // QString for holding onto current filename
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_LoadFileButton_clicked();                                       // slot for the Load button being clicked
    void on_SaveFileButton_clicked();                                       // slot for the Save button being clicked
    void on_SaveAsButton_clicked();                                         // slot for the Save As button being clicked
    void on_fontSizeSB_valueChanged(int);                                   // slot for the Font Size being changed
    void on_fontCB_currentFontChanged(const QFont &f);                      // slot for the selected Font being changed
    void on_boldButton_clicked();                                           // slot for the Bold button being clicked
    void on_underlineButton_clicked();                                      // slot for the underline button being clicked
    void on_italicButton_clicked();                                         // slot for the italic button being clicked

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
