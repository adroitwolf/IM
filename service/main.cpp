#include "view/mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    MainWidget w;

    w.show();

    return a.exec();
}
