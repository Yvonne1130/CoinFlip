#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H

#include <QPushButton>

class myPushBotton : public QPushButton
{
    Q_OBJECT
public:
    //explicit myPushBotton(QWidget *parent = nullptr);
    myPushBotton(QString normalImag,QString pressImag="");

    void zoom1();
    void zoom2();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QString normalImgPath;
    QString pressImagPath;

signals:

};

#endif // MYPUSHBOTTON_H
