#include "mycoin.h"
#include<QDebug>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片%1加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听正面翻反面信号，并且翻转金币
    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
       //判断 如果翻完了，讲min重置为1
        if(this->min>this->max){
            min = 1;
            isAnimation = false;
            timer1->stop();
        }

    });
    connect(timer2,&QTimer::timeout,this,[=](){
        QPixmap pixmap2;
        QString str2 = QString (":/res/Coin000%1.png").arg(max--);
        pixmap2.load(str2);
        this->setFixedSize(pixmap2.width(),pixmap2.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap2);
        this->setIconSize(QSize(pixmap2.width(),pixmap2.height()));
        if(this->max<this->min){
            max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}
//改变正反标志
void MyCoin::changeFlag(){
    //如果是正面 翻成反面
    if(this->flag){
        timer1->start(30);
        isAnimation = true;
        this->flag=false;

//        connect(timer1,&QTimer::timeout,this,[=](){
//            QPixmap pixmap;
//            QString str = QString(":/res/Coin000%1.png").arg(this->min++);
//            pixmap.load(str);
//            this->setFixedSize(pixmap.width(),pixmap.height() );
//            this->setStyleSheet("QPushButton{border:0px;}");
//            this->setIcon(pixmap);
//            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
//           //判断 如果翻完了，讲min重置为1
//            if(this->min>this->max){
//                min = 1;
//                timer1->stop();
//            }

//        });
    }
    else
    {
        timer2->start(30);
        isAnimation = true;
        this->flag=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||this->isWin){
        return;
    }
    else
        QPushButton::mousePressEvent(e);
}
