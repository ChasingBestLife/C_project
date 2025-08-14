#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <QMainWindow>
#include "mainwindow.h"

class SelectScene : public MainWindow
{
    Q_OBJECT
public:
    explicit SelectScene(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event);

signals:
    void backBtnClicked();
};

#endif // SELECTSCENE_H
