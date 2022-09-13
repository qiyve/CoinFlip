#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QMouseEvent>


//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    //初始化
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    //加载图片
    this->LoadPixmap(normalImg);

}

void MyPushButton::Zoom1()
{
    //创建动画对象
    QPropertyAnimation* anlimation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔 毫秒
    anlimation->setDuration(200);
    //创建开始位置
    anlimation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    anlimation->setEndValue(QRect(this->x(),this->y()+ 10,this->width(),this->height()));
    //设置缓和曲线
    anlimation->setEasingCurve(QEasingCurve::InOutBounce);
    //开始执行动画
    anlimation->start();

}

void MyPushButton::Zoom2()
{
    //创建动画对象
    QPropertyAnimation* anlimation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔 毫秒
    anlimation->setDuration(200);
    //创建开始位置
    anlimation->setStartValue(QRect(this->x(),this->y() +10,this->width(),this->height()));
    //创建结束位置
    anlimation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    anlimation->setEasingCurve(QEasingCurve::InOutBounce);
    //开始执行动画
    anlimation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //传入的按下图片 不为空 说明需要有按下状态 切换图片
    if(this->pressImgPath != "")
    {
        this->LoadPixmap(this->pressImgPath);
    }
    //qDebug()<<"按下按钮";
    //让父类执行其他的内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //传入的按下图片 不为空 说明需要有按下状态 切换成初始图片
    if(this->pressImgPath != "")
    {
        this->LoadPixmap(this->normalImgPath);
    }

    //qDebug()<<"释放按钮";
    //让父类执行其他的内容
    return QPushButton::mouseReleaseEvent(e);
}

void MyPushButton::LoadPixmap(QString normalImg,QString pressImg )
{
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败！";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(QSize(pix.width(),pix.height()));
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    // 设置图标
    this->setIcon(pix);
    //设置大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
