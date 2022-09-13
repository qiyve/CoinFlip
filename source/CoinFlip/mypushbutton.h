#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = 0);

    //构造函数 参数1 正常显示图片路径  参数2 按下显示的图片路径
    MyPushButton(QString normalImg,QString pressImg = "");

    //加载图片
    void LoadPixmap(QString normalImg,QString pressImg = "");

    //实现单击 弹跳效果
    void Zoom1(); //向下跳
    void Zoom2(); //向上跳

    //重写按钮 按下
    void mousePressEvent(QMouseEvent *e);
    //重写按钮 释放
    void mouseReleaseEvent(QMouseEvent *e);

public:
    //成员属性 保存用户传入的图片路径 以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
