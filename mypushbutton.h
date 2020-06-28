#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit myPushButton(QWidget *parent = nullptr);
    //构造函数   参数1 正常显示图片的路径 参数2 按下按钮的图片路径
    myPushButton(QString normalimg,QString pressimg ="");
    //保存用户传入的默认显示路径 以及按下后显示图片路径
    QString normalimgPath;
    QString pressimgPath;

    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
