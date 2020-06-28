#include "chooselevel.h"
#include<qmenubar.h>
#include<QPainter>
#include"mypushbutton.h"
#include<QLabel>
#include<qdebug.h>
Chooselevel::Chooselevel(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(400,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡");

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

    //返回按钮
    myPushButton * backbtn = new myPushButton(":/res/BackButton.png"
     ,":/res/BackButtonSelected.png");

    backbtn->setParent(this);
    backbtn->move((this->width()-backbtn->width()),this->height()-backbtn->height());

    //点击返回
    connect(backbtn,&myPushButton::clicked,[=](){

        //告诉主场景 我返回了,主场景监听chooselevel的返回安妮
        emit this->choosesecbe();

    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        myPushButton *menubtn = new myPushButton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(70+i%4 *70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(menubtn,&myPushButton::clicked,
                [=](){
            this->hide();//选关场景隐藏
            play =new PlaySecne(i+1);//创建游戏场景
            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());
            play->show();//显示游戏场景
            connect(play,&PlaySecne::choosesecbe,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(70+i%4 *70,130+i/4*70);

        //设置label 上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter |  Qt::AlignCenter );
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
void Chooselevel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    pix.load(":res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);









}
