#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    enum MyPushButtonStat
    {
        Normal,
        Pressed
    };

    explicit MyPushButton(QString normalImag, QString pressedImag, QWidget *parent = nullptr);

    // 播放动画
    void moveDown();
    void moveUp();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

private:
    // 正常状态的图片和按按钮后的图片
    QString mNormalImg;
    QString mPressedImg;
    // 按钮状态
    MyPushButtonStat mStat;

signals:
};

#endif // MYPUSHBUTTON_H
