#include "chooselevelscene.h"
#include"mypushbotton.h"
#include<QTimer>
#include<QLabel>
#include<QDebug>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu * startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回关卡音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    myPushBotton * backBtn=new myPushBotton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&myPushBotton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(500,this,[=](){
              emit this->ChooseSceneBack();
        });
    });
    //选择关卡按钮音效
    QSound * choosescene = new QSound(":/res/TapButtonSound.wav",this);

    //创建选择关卡的按钮
    for(int i = 0 ;i < 20 ;i++){
        myPushBotton * menu=new myPushBotton(":/res/LevelIcon.png");
        menu->setParent(this);
        menu->move(25+i%4 * 70,130+i/4 * 70 );

        //监听每个按钮
        connect(menu,&myPushBotton::clicked,[=](){
//            QString str = QString("第%1关").arg(i+1);
//            qDebug()<<str;
            choosescene->play();


            this->hide();
            //进入游戏时场景
            play = new PlayScene(i+1);
            play->setGeometry(this->geometry());
            play->show();
            connect(play,&PlayScene::backtochoose,this,[=](){
                //游戏场景置空
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });

        });



        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menu->width(),menu->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4 * 70,130+i/4 * 70);

        //设置对齐方式
        label->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
        //设置让鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}
void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
