#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include "mycoin.h"
#include "datacoin.h"
#include <QPropertyAnimation>
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{
//}

PlayScene::PlayScene(int levelNum)
{
    //初始化场景及标题
    this->InofScene(levelNum);
    //显示关卡
    this->showLevel();
    //设置返回按钮 并实现跳转到选关场景
    this->BackToChoose();
    //设置金币数据 及 翻转实现
    this->SetCoinData();

}

void PlayScene::SetCoinData()
{
    //初始化每个关卡的二维数组
    dataCoin data;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //三维数组逻辑 利用 map<vector<vector<int>>> 容器
            this->gameArray[i][j]=data.mData[this->LevelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/Camera Roll/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5, -tmpPix.height());

    //准备胜利音效
    QSound* winSound = new QSound(":/Camera Roll/LevelWinSound.wav");
    //准备点击金币音效
    QSound* filpSound = new QSound(":/Camera Roll/ConFlipSound.wav",this);



    //创建金币的背景图片
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //设置背景
            QPixmap pix = QPixmap(":/Camera Roll/BoardNode.png");
            QLabel* label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(75 + i*51, 200 + j*51);

            //创建金币 或 银币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                //显示金币
                str = QString(":/Camera Roll/Coin0001.png");
            }
            else
            {   //显示银币
                str = QString(":/Camera Roll/Coin0008.png");
            }

            //创建金币对象 并写到窗口
            MyCoin* coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(76 + i*51, 205 + j*51);

            //给金币属性赋值
            coin->posX = i; //设置坐标
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; // 1正面 0反面

            //将金币放入到 金币二维数组 以便于后期维护
            CoinBtn[i][j]= coin;

            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){

                //点击后 禁用所有金币  金币完成翻转后 解锁
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        this->CoinBtn[i][j]->isWin = true;
                    }
                }

                //翻动金币
                coin->ChangeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;;
                //播放翻金币音效
                filpSound->play();

                //翻转周围金币
                //点中金币 的右边金币翻转条件
                if(coin->posX + 1 <= 3)
                {
                    CoinBtn[coin->posX +1][coin->posY]->ChangeFlag();
                    this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                }

                // 点中金币 的左边金币翻转条件
                if(coin->posX - 1 >= 0)
                {
                    CoinBtn[coin->posX - 1][coin->posY]->ChangeFlag();
                    this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                }

                // 点中金币 的上边金币翻转条件
                if(coin->posY - 1 >= 0)
                {
                    CoinBtn[coin->posX][coin->posY - 1]->ChangeFlag();
                    this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                }

                // 点中金币 的下边金币翻转条件
                if(coin->posY + 1 <= 3)
                {
                    CoinBtn[coin->posX][coin->posY + 1]->ChangeFlag();
                    this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX ][coin->posY + 1] == 0 ? 1 : 0;
                }

                //金币完成翻转 解除禁用
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        this->CoinBtn[i][j]->isWin = false;
                    }
                }

                //判断是否胜利
                this->isWin = true;
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        if(CoinBtn[i][j]->flag == false)
                        {
                            this->isWin = false;
                            break;
                        }
                    }
                }

                if(this->isWin == true)
                {
                    qDebug()<<"胜利";

                    //所有按钮的胜利标志改为true
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            CoinBtn[i][j]->isWin = true;
                        }
                    }

                    //将胜利的图片移动下来
                    QPropertyAnimation* anlimation = new QPropertyAnimation(winLabel,"geometry");
                    //设置时间间隔 毫秒
                    anlimation->setDuration(1000);
                    //创建开始位置
                    anlimation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                    //创建结束位置
                    anlimation->setEndValue(QRect(winLabel->x(),winLabel->y()+ 150,winLabel->width(),winLabel->height()));
                    //设置缓和曲线
                    anlimation->setEasingCurve(QEasingCurve::InOutBounce);
                    //开始执行动画
                    anlimation->start();

                    //播放胜利音效
                    winSound->play();
                }
            });
        }
    }
}

void PlayScene::InofScene(int levelNum)
{
    //记录用户选择的关卡
    this->LevelIndex = levelNum;

    //设置翻金币游戏场景配置

    //设置固定大
    this->setFixedSize(350,588);

    //设置标题及图片
    this->setWindowIcon(QPixmap(":/Camera Roll/Coin0001.png"));
    this->setWindowTitle(QString("翻金币"));

    //设置工具栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    //创建菜单
    QMenu* startMenu = bar->addMenu("开始");
    //创建菜单项
    QAction* action = startMenu->addAction("退出");

    //实现退出功能
    connect(action,&QAction::triggered,[=](){
        this->close();
    });
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    //设置选择关卡场景
    QPainter painter(this);

    //绘制背景
    QPixmap pix;
    pix.load(":/Camera Roll/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题
    pix.load(":/Camera Roll/Title.png");
    pix = pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(this->width()*0.5 - pix.width()*0.65,35,pix.width(),pix.height(),pix);
}

void PlayScene::showLevel()
{
    //显示当前的关卡
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str = QString("Level:%1").arg(this->LevelIndex);

    //将字体设置到标签中
    label->setFont(font);
    label->setText(str);
    label->setGeometry(30,this->height()-50,160,50);
}

void  PlayScene::BackToChoose()
{
    //设置返回按钮
    MyPushButton* closeBtn = new MyPushButton(":/Camera Roll/BackButton.png", ":/Camera Roll/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()- closeBtn->width() ,this->height()- closeBtn->height()*1.5);

    //准备退出音效
    QSound* backSoud = new QSound(":/Camera Roll/BackButtonSound.wav",this);

    //单击返回
    connect(closeBtn,&QPushButton::clicked, [=](){
        //qDebug()<<"点击了游戏场景返回按钮";
        //播放音乐
        backSoud->play();

        //选关场景监听 PlayScene 的返回按钮

        //延迟返回
        QTimer::singleShot(500,this,[=](){
            emit this->ChooselevelBack();
        });
    });
}
