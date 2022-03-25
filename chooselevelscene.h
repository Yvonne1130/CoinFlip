#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include <QMainWindow>
#include<QMenuBar>
#include<QPainter>
#include"playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    PlayScene * play = NULL;
signals:
    //写一个自定义信号，告诉主场景点击了返回
   void ChooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
