#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include "mainwindow.h"
#include "selectscene.h"

class StartScene : public MainWindow
{
    Q_OBJECT
public:
    explicit StartScene(QWidget *parent = nullptr);

private:
    SelectScene mSelectScene;

signals:
};

#endif // STARTSCENE_H
