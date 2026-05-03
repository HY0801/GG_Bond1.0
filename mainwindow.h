#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QVector>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Item
{
    int x;
    int y;
    bool isBomb;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;

    int pigX = 200;
    int score = 0;
    int speed = 10;

    QVector<Item> items;

    // 图片
    QPixmap pigImg;
    QPixmap foodImg;
    QPixmap bombImg;

    void initItems();
};

#endif // MAINWINDOW_H