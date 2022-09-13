#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);

    //参数代表 传入的是金币路径 还是银币路径
    MyCoin(QString btnImg);

    //加载图片 并隐藏边框
    void LoadPix(QString img);
    //重写 按下
    void mousePressEvent(QMouseEvent *e);
    //该表标志 执行翻转操作
    void ChangeFlag();
    //金币翻转
   void CoinFlip();


public:

    //成员属性
    //金币属性
    int posX;  // x坐标
    int posY;  // y坐标
    bool flag; // 正反标记
    //定时器
    QTimer* timer1;  //正面 翻 反面
    QTimer* timer2;  //反面 翻 正面
    int min = 1; //最小图片
    int max = 8; //最大图片
    //执行动画
    bool isAnimation = false;  

    // 坑：这里必须初始化false 不然时而可以点击金币 时而不行
    bool isWin = false; //是否胜利  true 胜利

signals:

public slots:
};

#endif // MYCOIN_H
