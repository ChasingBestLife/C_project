#include "startscene.h"
#include "mypushbutton.h"
#include <QPushButton>
#include <QTimer>

StartScene::StartScene(QWidget *parent)
    : MainWindow{parent}
{
    this->setWindowTitle("开始场景");

    MyPushButton* btnStart = new MyPushButton("://res/MenuSceneStartButton.png","://res/MenuSceneStartButton.png", this);
    btnStart->resize(114, 114);
    btnStart->move((this->width()-btnStart->width())/2,
                   this->height()*3/4-btnStart->height()/2);

    connect(&this->mSelectScene, &SelectScene::backBtnClicked, [=](){
        // 当第二个窗口的返回按钮点击的时候，显示当前窗口，隐藏第二个窗口
        this->move(this->mSelectScene.pos());
        this->show();
        this->mSelectScene.hide();
    });

    connect(btnStart, &QPushButton::clicked, [=](){
        // 将按钮设置为不可用
        btnStart->setEnabled(false);

        // 播放向下的动画
        btnStart->moveDown();

        // 要等待之前的动画做完再做，否则会覆盖
        QTimer::singleShot(150, [=](){
            // 播放向上的动画
            btnStart->moveUp();
        });

        QTimer::singleShot(300, [=](){
            // 过300ms后，将按钮设置为可用
            btnStart->setEnabled(true);

            // 场景转换
            // 将窗口移动到当前窗口为止
            this->mSelectScene.move(this->pos());
            // 隐藏当前窗口
            this->hide();
            // 显示选择窗口
            this->mSelectScene.show();
        });
    });
}
