#include "clickablewidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    clickableWidget w;
    w.showFullScreen();
    w.show();
    return a.exec();
}
