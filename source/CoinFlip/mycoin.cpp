#include "mycoin.h"
#include <QDebug>


//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{
//}
MyCoin::MyCoin(QString btnImg)
{
    //加载图片
    this->LoadPix(btnImg);
    //初始化计时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //金币翻转
    this->CoinFlip();
}

void MyCoin::CoinFlip()
{
    //监听正面 翻 反面的信号, 并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QString img1 = QString(":/Camera Roll/Coin000%1.png").arg(this->min++);
        this->LoadPix(img1);
        //qDebug()<<"点击了金币";

        //判断 如果翻完了 将min重置为1
        if(this->min > this->max)
        {
            this->min = 1;
            this->isAnimation = false; //做完动画
            timer1->stop();
        }
    });

    // 监听反面 翻 正面的信号， 并且翻转银币
    connect(timer2,&QTimer::timeout,[=](){
        QString img2 = QString(":/Camera Roll/Coin000%1.png").arg(this->max--);
        this->LoadPix(img2);

        //判断 如果翻完了 将max重置为 8
        if(this->max < this->min)
        {
            this->max = 8;
            this->isAnimation = false; //做完动画
            timer2->stop();
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{

    if(this->isAnimation || this->isWin )
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}


void MyCoin::ChangeFlag()
{
    if(this->flag == true) //如果是正面  执行下面代码
    {
        this->timer1->start(50);
        this->isAnimation = true; //开始做动画
        this->flag = false;
    }
    else
    {
        this->timer2->start(50);
        this->isAnimation = true; //开始做动画
        this->flag = true;
    }
}

void MyCoin::LoadPix(QString Img)
{
    QPixmap pix;
    bool ret = pix.load(Img);
    if(!ret)
    {
        QString str = QString("图片 %1 加载失败").arg(Img);
        qDebug()<<str;
        return;
    }

    //设置固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置风格
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(QIcon(pix));
    this->setIconSize(QSize(pix.width(),pix.height()));
}
