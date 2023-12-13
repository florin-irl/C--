#include "TwixtUI.h"
#include <QtWidgets/QApplication>
#include "IGame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TwixtUI w;
    w.show();
    return a.exec();
}
