#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"chooselevel.h"
namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    //重写paintevent事件
    void paintEvent(QPaintEvent *);

    Chooselevel * chooseScene =NULL;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
