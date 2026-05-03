#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTimer>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 加载图片
    pigImg.load("C:/Users/houyu/Desktop/GG_Bond/res/pig.png");
    foodImg.load("C:/Users/houyu/Desktop/GG_Bond/res/food.png");
    bombImg.load("C:/Users/houyu/Desktop/GG_Bond/res/bomb.png");

    initItems();

    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=]() {

        int pigY = height() - 100;

        for (int i = 0; i < items.size(); i++)
        {
            items[i].y += speed;

            // 碰撞检测
            if (items[i].x + 50 > pigX &&
                items[i].x < pigX + 100 &&
                items[i].y + 50 > pigY &&
                items[i].y < pigY + 50)
            {
                if (items[i].isBomb)
                {
                    score -= 1; // 炸弹扣分
                }
                else
                {
                    score += 1; // 食物加分
                }

                // 重置
                items[i].y = 0;
                items[i].x = rand() % width();
            }

            // 掉出屏幕
            if (items[i].y > height())
            {
                items[i].y = 0;
                items[i].x = rand() % width();
            }
        }

        // 难度提升
        speed = 10 + score / 5;

        update();
    });

    timer->start(80);//调速
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initItems()
{
    for (int i = 0; i < 5; i++)
    {
        Item item;
        item.x = rand() % 400;
        item.y = rand() % 300;
        item.isBomb = (rand() % 5 == 0); // 20%概率炸弹
        items.push_back(item);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        pigX -= 20;
    else if (event->key() == Qt::Key_Right)
        pigX += 20;

    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 背景
    painter.fillRect(rect(), Qt::black);

    // 画猪
    painter.drawPixmap(pigX, height() - 100, 100, 100, pigImg);

    // 画物品
    for (auto item : items)
    {
        if (item.isBomb)
            painter.drawPixmap(item.x, item.y, 50, 50, bombImg);
        else
            painter.drawPixmap(item.x, item.y, 50, 50, foodImg);
    }

    // 分数
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(10, 30, QString("Score: %1").arg(score));
}