#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

//类前置声明
class PlayScene;

class ChooselevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooselevelScene(QWidget *parent = 0);

    //设置选择关卡场景
    void paintEvent(QPaintEvent *event);

    //翻金币游戏场景
    PlayScene* play;

signals:
    void ChooselevelBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
