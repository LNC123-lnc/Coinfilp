#ifndef PLAYSECNE_H
#define PLAYSECNE_H

#include <QMainWindow>
#include"mycoin.h"
class PlaySecne : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlaySecne(QWidget *parent = nullptr);

    PlaySecne(int levelnum);

    void paintEvent(QPaintEvent *);

    int levelIndex;

    int gamearray[4][4];

    Mycoin * coinbtn[4][4];

    bool iswin ;
signals:

     void choosesecbe();
public slots:
};

#endif // PLAYSECNE_H
