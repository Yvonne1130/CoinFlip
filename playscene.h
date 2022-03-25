#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QPainter>
#include"mycoin.h"
#include<QSound>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene (int levelNum);
    void paintEvent(QPaintEvent *);

    int gameArray[4][4];
    MyCoin * coinBtn[4][4];
    int levelIndex;//内部成员属性 记录关数

    //是否胜利的标志
    bool isWin;
signals:
    void backtochoose();
};

#endif // PLAYSCENE_H
