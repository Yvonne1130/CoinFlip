#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include"mypushbotton.h"
#include<QTimer>
#include<QLabel>
#include"dataconfig.h"
#include<QPropertyAnimation>


//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum){
    QString str=QString("进入了%1").arg(levelNum);
    qDebug()<<str;
    levelIndex=levelNum;
    //窗口设置
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setFixedSize(320,588);
    this->setWindowTitle("游戏场景");
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu * startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);


    //返回按钮
    myPushBotton * backBtn=new myPushBotton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //点击返回
    connect(backBtn,&myPushBotton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(500,this,[=](){
              emit this->backtochoose();
        });
    });
    //显示关卡数
    QLabel * label = new QLabel(this);

    //设置字体及字号
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str2 = QString("Level:%1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str2);
    label->setGeometry(30, this->height() - 50,120, 50);

    //初始化二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j = 0;j < 4;j++ )
            gameArray[i][j]=config.mData[this->levelIndex][i][j];
    }

    QLabel* winLabel = new QLabel;
        QPixmap tmpPix;
        tmpPix.load(":/res/LevelCompletedDialogBg.png");
        winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
        winLabel->setPixmap(tmpPix);
        winLabel->setParent(this);
        winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    //创建金币的背景图片
      for(int i = 0 ; i < 4;i++)
      {
          for(int j = 0 ; j < 4; j++)
          {
             //绘制背景图片
              QLabel* label = new QLabel;
              label->setGeometry(0,0,50,50);
              label->setPixmap(QPixmap(":/res/BoardNode.png"));
              label->setParent(this);
              label->move(57 + i*50,200+j*50);

              //创建金币
              QString str;
              if(this->gameArray[i][j]==1){
                  //显示金币
                  str =":/res/Coin0001.png";
              }
              else
                  str=":/res/Coin0008.png";
              MyCoin * coin = new MyCoin(str);
              coin->setParent(this);
              coin->move(59 + i*50,204+j*50);

              //给金币属性赋值
              coin->posX = i;
              coin->posY = j;
              coin->flag = gameArray[i][j];

              //将金币放入到 金币的二维数组里 以便以后的维护
              coinBtn[i][j] = coin;


              //点击金币，进行翻转
              connect(coin,&MyCoin::clicked,[=](){
                  //翻金币音效
                  flipSound->play();
                    for(int i =0; i<4;i++)
                       for(int j=0;j<4;j++)
                          coinBtn[i][j]->isWin = true;



                    coin->changeFlag();
                    this->gameArray[i][j]=this->gameArray[i][j]==0 ? 1 : 0;

                    //翻转周围硬币
                    QTimer::singleShot(300,this,[=](){
                        if(coin->posX + 1<=3){
                            coinBtn[coin->posX+1][coin->posY]->changeFlag();
                            gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                        }
                        if(coin->posX - 1>=0){
                            coinBtn[coin->posX-1][coin->posY]->changeFlag();
                            gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                        }
                        if(coin->posY + 1<=3){
                            coinBtn[coin->posX][coin->posY+1]->changeFlag();
                            gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX][coin->posY+1]== 0 ? 1 : 0;
                        }
                        if(coin->posY - 1>=0){
                            coinBtn[coin->posX][coin->posY-1]->changeFlag();
                            gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX][coin->posY-1]== 0 ? 1 : 0;
                        }
                        for(int i =0; i<4;i++)
                            for(int j=0;j<4;j++)
                                coinBtn[i][j]->isWin = false;


                        //判断是否胜利
                        this->isWin=true;
                        for(int i =0; i<4;i++)
                            for(int j=0;j<4;j++){
                                if(coinBtn[i][j]->flag==false){
                                    this->isWin = false;
                                    break;
                                }
                            }
                        if(isWin)
                        {
                            winSound->play();
                            for(int i =0; i<4;i++)
                                for(int j=0;j<4;j++)
                                    coinBtn[i][j]->isWin = true;
                            QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                            //时间间隔
                            animation->setDuration(1000);
                            //设置开始位置
                            animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                            animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start();
                        }
                    });


              });

          }
      }


}
void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}
