#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbotton.h"
#include<QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币");

    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮
    myPushBotton *starBtn=new myPushBotton(":/res/MenuSceneStartButton.png");
    starBtn->setParent(this);
    starBtn->move(this->width()*0.5-starBtn->width()*0.5,this->height()*0.7);


    chooseScene=new ChooseLevelScene;
    connect(chooseScene,&ChooseLevelScene::ChooseSceneBack,this,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });


//    connect(chooseScene,&ChooseLevelScene::ChooseSceneBack,this,[=](){
//        chooseScene->hide();
//    }

    connect(starBtn,&myPushBotton::clicked,[=](){

        startSound->play();
        //动画
        starBtn->zoom1();
        starBtn->zoom2();
        QTimer::singleShot(300,this,[=](){
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();

            this->hide();
        });

    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);


}
MainScene::~MainScene()
{
    delete ui;
}

