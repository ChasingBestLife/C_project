#include "mypushbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImag, QString pressedImag, QWidget *parent)
    :QPushButton(parent)
    ,mNormalImg(normalImag)
    ,mPressedImg(pressedImag)
{

}

void MyPushButton::paintEvent(QPaintEvent *event)
{
    // 绘制按钮的图片
    QPainter painter(this);
    QPixmap pix;

    // 按下与松开两种按钮图片
    if(mStat == Normal)
    {
        pix.load(mNormalImg);
    }
    if(mStat == Pressed)
    {
        pix.load(mPressedImg);
    }
    // 绘制背景图片
    painter.drawPixmap(0,0, this->width(),this->height(), pix);

    // 绘制按钮文字
    painter.drawText(0,0, this->width(), this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}

void MyPushButton::mousePressEvent(QMouseEvent *ev)
{
    // 鼠标按下的时候，状态改为pressed
    this->mStat = Pressed;
    update();
    // 保证信号和槽的功能
    QPushButton::mousePressEvent(ev);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *ev)
{
    // 鼠标松开的时候，状态改为normal
    this->mStat = Normal;
    update();
    // 保证信号和槽的功能
    QPushButton::mouseReleaseEvent(ev);
}

void MyPushButton::moveDown()
{
    // 1位置大小属性发生变化
    // 2给定开始的位置大小属性
    // 3给定结束的位置大小属性
    // 4给定速度，给定动画时长

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::moveUp()
{
    // 1位置大小属性发生变化
    // 2给定开始的位置大小属性
    // 3给定结束的位置大小属性
    // 4给定速度，给定动画时长

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y()-10, this->width(), this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
