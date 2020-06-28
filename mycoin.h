#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
#include<QEvent>
class Mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit Mycoin(QWidget *parent = nullptr);
    //参数代表 传入的金币路径 还是银币路径
    Mycoin(QString btnimg);
    
    //金币属性
    int posx;
    int posy;
    bool flag;
    
    //改变标志
    void changeflag();
    QTimer * time1;
    QTimer * time2;
    int min =1;
    int max =8;
    //执行动画 标志
    bool isanimation =false;

    bool iswin=false;

    void mousePressEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYCOIN_H
