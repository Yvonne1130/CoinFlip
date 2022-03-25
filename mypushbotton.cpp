#include "mypushbotton.h"
#include<QDebug>
#include<QPropertyAnimation>
//myPushBotton::myPushBotton(QWidget *parent) : QWidget(parent)
//{

//}


myPushBotton::myPushBotton(QString normalImag,QString pressImag){
    normalImgPath=normalImag;
    pressImagPath=pressImag;
    QPixmap pixmap;
    bool ret=pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImag<<"图片加载失败";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());

    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
void myPushBotton::zoom1(){
    QPropertyAnimation *animation1=new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}
void myPushBotton::zoom2(){
    QPropertyAnimation *animation1=new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}
void myPushBotton::mousePressEvent(QMouseEvent *e){
    if(this->pressImagPath!=""){
        QPixmap pixmap;
        bool ret=pixmap.load(this->pressImagPath);
        if(!ret){
            qDebug()<<"图片加载失败";
        }
        this->setFixedSize(pixmap.width(),pixmap.height());

        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void myPushBotton::mouseReleaseEvent(QMouseEvent *e){
        if(this->pressImagPath!=""){
        QPixmap pixmap;
        bool ret=pixmap.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"图片加载失败";
        }
        this->setFixedSize(pixmap.width(),pixmap.height());

        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
