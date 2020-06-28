#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include<QPaintEvent>
#include"playsecne.h"
class Chooselevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit Chooselevel(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    PlaySecne * play = NULL;
signals:
    //写一个自定义信号，告诉主场景，点击了返回
    void choosesecbe();



public slots:
};

#endif // CHOOSELEVEL_H
