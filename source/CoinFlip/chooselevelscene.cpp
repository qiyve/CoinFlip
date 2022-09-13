#include "chooselevelscene.h"
#include <QPainter>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

#include "playscene.h"

ChooselevelScene::ChooselevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置场景配置
    this->setFixedSize(350,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/Camera Roll/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");
    //创建工具栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    //创建菜单
    QMenu* startMenu = bar->addMenu("开始");
    //创建退出 菜单项
    QAction* quitAction = startMenu->addAction("退出");

    //单击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //准备退出音效
    QSound* backSoud = new QSound(":/Camera Roll/BackButtonSound.wav",this);
    //准备选关音效
    QSound* chooseSoud = new QSound(":/Camera Roll/TapButtonSound.wav",this);

    //返回按钮
    MyPushButton* backBtn = new MyPushButton(":/Camera Roll/BackButton.png", ":/Camera Roll/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()- backBtn->width() ,this->height()- backBtn->height()*1.5);


    //单击返回
    connect(backBtn,&QPushButton::clicked, [=](){
        //qDebug()<<"点击了返回按钮";

        //播放音效
        backSoud->play();

        //延迟返回  主场景监听 ChooselevelScene 的返回按钮
        QTimer::singleShot(500,this,[=](){
            emit this->ChooselevelBack();
        });
    });

    //创建一个选择关卡
    for(int i = 0; i < 20; i++)
    {

        MyPushButton* menuBtn = new MyPushButton(":/Camera Roll/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(50 + (i%4) * 70, 150 + (i/4) * 70);

        //监听每一个按钮的事件
        connect(menuBtn,&QPushButton::clicked,[=](){
            //QString str = QString("你选择的是第 %1 关").arg(i+1);
            //qDebug()<<str;

            //播放选关音效
            chooseSoud->play();

            //进入到游戏场景
            this->hide(); //将选关场景隐藏
            play = new PlayScene(i+1); //创建游戏场景

            //设置 游戏场景位置
            play->setGeometry(this->geometry());

            play->show();  //显示游戏场景

            //监听游戏场景返回按钮
            connect(play,&PlayScene::ChooselevelBack,[=](){

                //设置 ChooselevelScene 场景位置
                this->setGeometry(play->geometry());
                delete  play;
                this->show();
                play = NULL;
            });
        });


        QLabel* label = new QLabel(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->move(50 + (i%4) * 70, 169 + (i/4) * 70);
        label->setText(QString::number(i+1));

        //设置label 上的文字对齐 水平居中
        label->setAlignment(Qt::AlignHCenter|Qt::AlignJustify);
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}

void ChooselevelScene::paintEvent(QPaintEvent *event)
{
    //设置选择关卡场景
    QPainter painter(this);

    //加载图片
    QPixmap pix;
    pix.load(":/Camera Roll/OtherSceneBg.png");
    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/Camera Roll/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width(),pix.height());
    //绘制标题
    painter.drawPixmap(this->width()*0.5 - pix.width()*0.65,35,pix.width(),pix.height(),pix);

}
