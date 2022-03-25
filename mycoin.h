#ifndef MYCOIN_H
#define MYCOIN_H
#include<QTimer>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);


    //参数代表传入的是金币还是银币
    MyCoin(QString btnImg);

    //改变标志
    void changeFlag();
    QTimer* timer1;
    QTimer *timer2;
    int min=1;
    int max=8;

    int posX;
    int posY;
    bool flag;//正反标志

    //执行动画 标志
    bool isAnimation = false;

    //重写 按下
    void mousePressEvent(QMouseEvent *e);

    //是否胜利
    bool isWin=false;

signals:

};

#endif // MYCOIN_H
