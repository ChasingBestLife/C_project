#include "selectscene.h"
#include "mypushbutton.h"
#include "playscene.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QMenuBar>

SelectScene::SelectScene(QWidget *parent)
    : MainWindow{parent}
{
    // 返回按钮
    MyPushButton* btnBack = new MyPushButton("://res/BackButton.png", "://res/BackButtonSelected.png", this);
    btnBack->resize(72, 32);
    btnBack->move(this->width()-btnBack->width(), this->height()-btnBack->height());

    connect(btnBack, &QPushButton::clicked, this, &SelectScene::backBtnClicked);

    const int colWidth = 70;
    const int rowHeight = 70;

    // x，y偏移
    const int x0ffset = 25;
    const int y0ffset = 130;

    for(int i = 0; i < 20; i++)
    {
        MyPushButton* btn = new MyPushButton("://res/LevelIcon.png", "://res/LevelIcon.png", this);
        btn->setText(QString::number(i+1));
        btn->resize(57,57);

        // 排列
        // 行 i/4
        // 列 i % 4
        int row = i /4;
        int col = i % 4;
        // x坐标 = 列数*列宽colWidth + x偏移
        // y坐标 = 行数*行高rowHeight + y偏移
        int x = col*colWidth + x0ffset;
        int y = row*rowHeight + y0ffset;
        btn->move(x,y);

        // 按钮实现功能
        connect(btn, &MyPushButton::clicked, [=](){
            // 点击关卡按钮后打开一个新的场景
            PlayScene *playscene = new PlayScene(i+1);
            playscene->move(this->pos());
            playscene->show();
            // 设置playscene关闭的时候自动释放
            playscene->setAttribute(Qt::WA_DeleteOnClose);
            this->hide();

            connect(playscene, &PlayScene::backBtnClicked, [=](){
                this->move(playscene->pos());
                this->show();
                playscene->hide();
            });
        });
    }
}

void SelectScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(0, this->menuBar()->height());
    // 绘制背景图
    QPixmap pix("://res/OtherSceneBg.png");
    painter.drawPixmap(0,0, this->width(),this->height(), pix);
    // 绘制logo
    pix.load("://res/Title.png");
    painter.drawPixmap(0, 0, pix);
}
