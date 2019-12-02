#include "widget.h"
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;                                        // create the QWidget for this application
    w.show();                                        // show the QWidget (UI will be displayed from now on)

    return a.exec();
}
