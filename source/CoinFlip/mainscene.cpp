#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include <QSound>


MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置主场景
    //设置固定大小
    setFixedSize(350,588);
    //设置标题图标
    setWindowIcon(QIcon(":/Camera Roll/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币");

    //实现退出按钮
    connect(ui->actionOut,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始音效
    QSound* startSoud = new QSound(":/Camera Roll/TapButtonSound.wav",this);
    //->setLoops(-1);    //设置循环 如果是 -1 代表无线
    //startSoud->play();


    //设置开始按钮
    MyPushButton* startBtn = new MyPushButton(":/Camera Roll/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.6);


    //实例化选择关卡场景
    chooseScene = new ChooselevelScene;

    //监听返回选择关卡的返回信号
    connect(chooseScene,&ChooselevelScene::ChooselevelBack,[=](){
        //设置 chooseScene场景位置
        this->setGeometry(chooseScene->geometry());

        chooseScene->hide(); //隐藏选关场景
        this->show();        //显示主场景
    });

    connect(startBtn,&QPushButton::clicked,[=](){
        //qDebug()<<"单击了按钮";

        //播放开始音效
        startSoud->play();
        //设置弹跳动作
        startBtn->Zoom1();
        startBtn->Zoom2();

        //延迟进入选择关卡场景
        QTimer::singleShot(500,this,[=](){
            //设置 chooseScene场景位置
            chooseScene->setGeometry(this->geometry());

            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *event)
{
    //设置背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Camera Roll/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置 插画
    pix.load(":/Camera Roll/Title.png");
    pix = pix.scaled(pix.width()* 0.5,pix.height()* 0.5);
    painter.drawPixmap(20,40,pix.width(),pix.height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}
