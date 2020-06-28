#include "mycoin.h"
//Mycoin::Mycoin(QWidget *parent) : QPushButton(parent)
//{

//}

#include<QDebug>

Mycoin::Mycoin(QString btnimg)
{
    QPixmap pix;
    bool ret =pix.load(btnimg);
    if(!ret)
    {
       qDebug()<<"图片加载失败";
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton(border::0px)");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    
    //初始化
    time1 =new QTimer(this);
    time2 =new QTimer(this);

    //监听正面翻反面的信号
    connect(time1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1")
                .arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton(border::0px)");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 翻完了，将min置1
        if(this->min >this->max)
        {
            this->min =1;
            isanimation=false;
            time1->stop();
        }
    });

    //监听反面翻反面的信号
    connect(time2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1")
                .arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton(border::0px)");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 翻完了，将min置1
        if(this->max <this->min)
        {
            this->max =8;
            isanimation=false;
            time2->stop();
        }
    });
}
void Mycoin::changeflag()
{
    
    //如果是正面  翻成反面
    if(this->flag)
    {
        //开始正面翻反面的定时器
        time1->start(30);
        isanimation=true;
        this->flag =false;

    }
    else
    {
        //开始正面翻反面的定时器
        time2->start(30);
        isanimation=true;
        this->flag =true;
    }

}
void Mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isanimation  || this->iswin)
    {
        return;
    }
    else
    {
       QPushButton::mousePressEvent(e);
    }
}




