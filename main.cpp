#include "views.h"
#include "controllers.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FriendlyMain w;
    w.show();

    return a.exec();
}
