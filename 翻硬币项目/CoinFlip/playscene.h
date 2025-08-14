#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mainwindow.h"
#include "coinbutton.h"
#include <QMainWindow>

class PlayScene : public MainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int level, QWidget *parent = nullptr);
    // 翻动row行，col列的硬币
    void flip(int row, int col);
    // 判断游戏胜利
    void judgeWin();

protected:
    void paintEvent(QPaintEvent* event);

signals:
    void backBtnClicked();

private:
    // 硬币按钮数组
    CoinButton *mCoins[4][4];
    bool mHasWin;

};

#endif // PLAYSCENE_H
