#include "playscene.h"
#include "mypushbutton.h"
#include "coinbutton.h"
#include "dataconfig.h"
#include <QPainter>
#include <QPixmap>
#include <QMenuBar>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QPropertyAnimation>

PlayScene::PlayScene(int level, QWidget *parent)
    : MainWindow{parent}
{
    mHasWin = false;
    // 返回按钮
    MyPushButton* btnBack = new MyPushButton("://res/BackButton.png", "://res/BackButtonSelected.png", this);
    btnBack->resize(72, 32);
    btnBack->move(this->width()-btnBack->width(), this->height()-btnBack->height());

    connect(btnBack, &QPushButton::clicked, this, &PlayScene::backBtnClicked);

    // 添加左下角的level
    QLabel* label = new QLabel(this);
    label->setText(QString("Level: %1").arg(level));
    label->resize(120, 50);
    // 设置字体
    label->setFont(QFont("华文新魏", 20));
    // 移动到左下角
    label->move(30, this->height()-label->height());


    // 设置按钮
    const int colWidth = 50;
    const int rowHeight = 50;
    // x，y偏移
    const int x0ffset = 57;
    const int y0ffset = 200;

    // 取出第几关的二位数组数据
    DataConfig data;
    QVector<QVector<int>> dataArray = data.mData[level];

    // 16个硬币按钮
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            CoinButton* btn = new CoinButton(this);
            // 存储按钮到数组对应的位置
            mCoins[row][col] = btn;

            // x坐标 = 列数*列宽colWidth + x偏移
            // y坐标 = 行数*行高rowHeight + y偏移
            int x = col*colWidth + x0ffset;
            int y = row*rowHeight + y0ffset;
            // 设置按钮位置和大小
            btn->setGeometry(x, y, 50,50);

            btn->setStat(dataArray[row][col]);

            connect(btn, &CoinButton::clicked, [=](){
                // btn->filp();
                this->flip(row, col);
            });
        }
    }

}

void PlayScene::flip(int row, int col)
{
    if(mHasWin)
    {
        return;
    }
    this->mCoins[row][col]->filp();

    // 延迟翻动上下左右其他硬币
    QTimer::singleShot(200,[=](){
        // 翻动上下左右的硬币
        // 下一行的硬币
        if(row+1 < 4)
        {
            this->mCoins[row+1][col]->filp();
        }
        // 上一行的硬币
        if(row-1 >= 0)
        {
            this->mCoins[row-1][col]->filp();
        }
        // 左边列的硬币
        if(col+1 < 4)
        {
            this->mCoins[row][col+1]->filp();
        }
        // 右边列的硬币
        if(col-1 >= 0)
        {
            this->mCoins[row][col-1]->filp();
        }

        // 判断游戏是否胜利
        this->judgeWin();
    });
}

void PlayScene::judgeWin()
{
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            // 判断某个银币是银币
            if(!this->mCoins[row][col]->stat())
            {
                // 只要有一个是银币，就返回继续游戏
                return;
            }
        }
    }

    // 所有都是金币的情况下游戏结束
    // QMessageBox::information(this, "恭喜！", "您已经胜利了");
    // 播放胜利动画
    QLabel* labelWin = new QLabel(this);
    QPixmap pix("://res/LevelCompletedDialogBg.png");
    labelWin->resize(pix.width(), pix.height());
    labelWin->setPixmap(pix);
    labelWin->move((this->width()-labelWin->width())/2, -labelWin->height());
    labelWin->show();

    QPropertyAnimation* animation = new QPropertyAnimation(labelWin,"geometry", this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(), labelWin->y()+100, labelWin->width(), labelWin->height()));
    animation->setDuration(1000);
    // 设置动画的运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 动画播放完自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    mHasWin = true;
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(0, this->menuBar()->height());
    // 绘制背景图
    QPixmap pix("://res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0, this->width(),this->height(), pix);
    // 绘制logo
    // 将logo播放百分之50
    pix.load("://res/Title.png");
    pix = pix.scaled(pix.width()/2, pix.height()/2);
    painter.drawPixmap(0, 0, pix);
}
