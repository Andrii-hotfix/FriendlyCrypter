#include "views.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FriendlyMain w;
    w.show();
    w.open_login();

    return a.exec();
}
