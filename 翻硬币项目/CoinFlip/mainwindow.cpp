#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题
    this->setWindowTitle("翻金币");
    // 设置窗口icon
    this->setWindowIcon(QIcon("://res/Coin0001.png"));
    // 设置窗口大小
    this->setFixedSize(320, 588);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // 绘制背景图片
    QPainter painter(this);
    QPixmap pix("://res/MenuSceneBg.png");

    painter.drawPixmap(0,0, this->width(), this->height(), pix);
}
