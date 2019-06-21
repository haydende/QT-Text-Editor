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
    QString currentFile;
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_LoadFileButton_clicked();
    void on_SaveFileButton_clicked();
    void on_SaveAsButton_clicked();
    void on_fontSizeSB_valueChanged(int);
    void on_fontCB_currentFontChanged(const QFont &f);
    void on_boldButton_clicked();
    void on_underlineButton_clicked();
    void on_italicButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
