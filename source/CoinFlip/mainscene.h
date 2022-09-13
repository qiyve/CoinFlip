#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
class ChooselevelScene;

    namespace Ui {
    class MainScene;
    }

    class MainScene : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainScene(QWidget *parent = 0);
        ~MainScene();

        //设置主场景
        void paintEvent(QPaintEvent *event);

        //选择关卡场景
        ChooselevelScene* chooseScene;

    private:
        Ui::MainScene *ui;
    };

    #endif // MAINSCENE_H
