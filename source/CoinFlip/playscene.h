#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class MyCoin;

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = 0);

    //选择关卡场景
    PlayScene(int levelNum);
    //重新paintEvent事件
    void paintEvent(QPaintEvent *event);
    //初始化场景及标题
    void InofScene(int levelNum);
    //显示关卡
    void showLevel();
    //设置返回按钮 并实现跳转到选关场景
    void BackToChoose();
    //设置金币数据 及 翻转实现
    void SetCoinData();

public:
    int LevelIndex; //内部成员属性 记录所选关卡
    int gameArray[4][4]; //二维数组 维护每个关卡的具体数据
    MyCoin* CoinBtn[4][4]; // 维护每一个金币的位置
    bool isWin; //胜利标志 true 胜利

signals:
        void ChooselevelBack();

public slots:
};

#endif // PLAYSCENE_H
