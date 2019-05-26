#include "landwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LandWidget w;
    w.show();

    return a.exec();
}
