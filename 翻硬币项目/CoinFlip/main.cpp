#include "mainwindow.h"
#include "startscene.h"
#include "selectscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // MainWindow w;
    // w.show();

    // 开始场景
    StartScene sc;
    sc.show();

    // // 选择场景
    // SelectScene ss;
    // ss.show();


    return a.exec();
}
