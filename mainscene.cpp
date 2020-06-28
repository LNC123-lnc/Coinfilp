#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置主场景

    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    QSound *startsound =new QSound(":/res/TapButtonSound.wav");
    //startsound->setLoops(-1);//设置循环

    //开始按钮
    myPushButton *startbtn=new myPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5 - startbtn->width()*0.5,this->height()*0.7);
    //实例化选择关卡场景
    chooseScene =new Chooselevel;

    //监听选择关卡的信号
    connect(chooseScene,&Chooselevel::choosesecbe,[=](){
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();//重新显示主场景
    });

    connect(startbtn,&myPushButton::clicked,[=](){
        qDebug()<<"点击了开始";
        //做弹跳特效
        startsound->play();//播放音效
        startbtn->zoom1();
        startbtn->zoom2();

        //进入到选择关卡场景中
        ////延时进入到选择关卡中
        QTimer::singleShot(500,[=](){
            //自身隐藏
            this->hide();
            chooseScene->setGeometry(this->geometry());
            //显示选择关卡
            chooseScene->show();

        });

    });
}
 void MainScene::paintEvent(QPaintEvent *)
 {
     QPainter painter(this);
     QPixmap pix;
     pix.load(":/res/PlayLevelSceneBg.png");
     painter.drawPixmap(0,0,this->width(),this->height(),pix);


        //画背景上图标
        pix.load(":/res/Title.png");

        pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);//缩放

        painter.drawPixmap(10,30,pix);
















 }

MainScene::~MainScene()
{
    delete ui;
}
