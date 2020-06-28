#include"mypushbutton.h"
#include "playsecne.h"
#include<QDebug>
#include<QMenuBar>
#include<qpainter.h>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlaySecne::PlaySecne(QWidget *parent) : QMainWindow(parent)
//{

//}

PlaySecne::PlaySecne(int levelnum)
{
    QString str = QString("进入了第 %1 关").arg(levelnum);
    qDebug()<<str;
    this->levelIndex =levelnum;
    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
   //设置标题
    this->setWindowTitle("翻金币场景");
    //创建菜单栏
    QMenuBar * bar =menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startmenu= bar->addMenu("开始");

    //创建退出  菜单项
    QAction * quit = startmenu->addAction("退出");

    //退出
    connect(quit,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮音效
        QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //翻金币音效
       QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
       //胜利按钮音效
       QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    //返回按钮
    myPushButton * backbtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backbtn->setParent(this);
    backbtn->move((this->width()-backbtn->width()),this->height()-backbtn->height());

    //点击返回
    connect(backbtn,&myPushButton::clicked,[=](){
        //翻金币场景点击按钮
        qDebug()<<"click";
        backSound->play();
        //告诉主场景 我返回了,主场景监听chooselevel的返回安妮
        emit this->choosesecbe();

    });
    //显示当前关卡
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文魏松");
    font.setPointSize(15);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置放到标签中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);

    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gamearray[i][j]=dataconfig().mdata[this->levelIndex]
                    [i][j];
        }
    }

    QLabel *winlabel = new QLabel;
    QPixmap tmppix;
    tmppix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,tmppix.width(),tmppix.height());
    winlabel->setPixmap(tmppix);
    winlabel->setParent(this);
    winlabel->move((this->width()-tmppix.width())*0.5,-tmppix.height());
    //显示金币背景图片
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel *label =new QLabel;
            label->setGeometry(0,0,50,50);
            label->setParent(this);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gamearray[i][j]==1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            Mycoin * coin =new Mycoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            
            //给金币属性赋值
            coin->posx=i;
            coin->posy=j;
            coin->flag = this->gamearray[i][j];//1正面 2反面

            //奖金币放入数组中
            coinbtn[i][j] =coin;
            //点击金币 进行翻转
            connect(coin,&Mycoin::clicked,[=](){
                flipSound->play();
                for(int i=0;i<4;i++)
                {

                    for(int j=0;j<4;j++)
                    {
                        coinbtn[i][j]->iswin =true;
                    }
                }
               coin->changeflag();
               this->gamearray[i][j]=(this->gamearray[i][j]==0 ? 1: 0);

               QTimer::singleShot(300,this,[=](){

                //翻转金币周围
               if(coin->posx+1<=3)//右侧金币翻转条件
               {
                   coinbtn[coin->posx+1][coin->posy]->changeflag();;
                   this->gamearray[coin->posx+1][coin->posy]=(this->gamearray[coin->posx-1][coin->posy]==0 ? 1: 0);

               }

              if(coin->posx-1>=0)//左侧侧金币翻转条件
              {
                  coinbtn[coin->posx-1][coin->posy]->changeflag();;
                  this->gamearray[coin->posx-1][coin->posy]=(this->gamearray[coin->posx-1][coin->posy]==0 ? 1: 0);

              }
              //翻转金币周围
             if(coin->posy+1<=3)//上侧金币翻转条件
             {
                 coinbtn[coin->posx][coin->posy+1]->changeflag();;
                 this->gamearray[coin->posx][coin->posy+1]=(this->gamearray[coin->posx][coin->posy+1]==0 ? 1: 0);

             }
             if(coin->posy-1>=0)//shang侧侧金币翻转条件
             {
                 coinbtn[coin->posx][coin->posy-1]->changeflag();;
                 this->gamearray[coin->posx][coin->posy-1]=(this->gamearray[coin->posx-1][coin->posy]==0 ? 1: 0);

             }
             for(int i=0;i<4;i++)
             {

                 for(int j=0;j<4;j++)
                 {
                     coinbtn[i][j]->iswin =false;
                 }
             }

             //判断是否胜利
             this->iswin =true;
             for(int i=0;i<4;i++)
             {

                 for(int j=0;j<4;j++)
                 {
                     if(coinbtn[i][j]->flag == false)
                     {
                         this->iswin=false;
                         break;
                     }
                 }
             }
             if(this->iswin == true)
             {
                 winSound->play();
                 qDebug()<<"victory";
                 for(int i=0;i<4;i++)
                 {

                     for(int j=0;j<4;j++)
                     {
                         coinbtn[i][j]->iswin =true;
                     }
                 }
                 //将胜利图片移动下来
                 QPropertyAnimation * animation
                 =new QPropertyAnimation(winlabel,"geometry");

                 //设置时间间隔
                 animation->setDuration(1000);
                 //设置开始位置
                 animation->setStartValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                 //设置结束位置
                 animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                 animation->start();
             }

               });
            });
        }
    }

}

void PlaySecne::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);


}



























