#include "loginwidget.h"
#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWidget w;
    w.show();

    return a.exec();
}

void startMainWidget(user* userPtr)
{
    MainWidget w(userPtr);
    w.show();

    w.exec();
}
