#pragma once
#pragma once
#ifndef __THIRD_SCENE_H__
#define __THIRD_SCENE_H__
#include "cocos2d.h"
#include"Tower.h"
#include"Tower2.h"
#include"Tower3.h"

///////////////////////声明第二个场景，也就是游戏界面（map）//////////////////////
class ThirdScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//计数器，记录音乐控制按钮点击次数
    virtual bool init();
    // 创建并移动怪物的函数
    void menuBack(cocos2d::Ref* pSender);
    void menuBackHome(cocos2d::Ref* pSender);

    void ThirdScene::MusicControl(Ref* sender);
    int countdown = 3;
    void countDown(float dt);

    ///加倍速按钮调用的函数
    int speedCount = 1;
    void speedUp(Ref* pSender);
    ///    暂停按钮
    int stopCount = 1;
    void stopORstart(Ref* pSender);



    int round = 1;
    int round1_ = 0;
    int round2_ = 0;
    int round3_ = 0;

    bool Win = 0;
    void checkWin(float dt)
    {
        if (round == 4) {
            cocos2d::Scene* scene = Director::getInstance()->getRunningScene();
            Monster* object = nullptr;
            Vector<Node*> children = scene->getChildren();
            // 遍历子节点
            for (Node* child : children)
            {
                Monster* monster = dynamic_cast<Monster*>(child);
                if (monster)
                {
                    object = monster;
                    break;
                }
            }

            if (object == nullptr)
                Win = 1;
        }
        if (Win)
        {
            auto spritewin = Sprite::create("win.png");
            // 将场景图片定位在屏幕中央
            spritewin->setPosition(1300, 900);
            this->addChild(spritewin, 4);
        }

    }
    void createAndMoveMonster1(float dt);
    void createAndMoveMonster2(float dt);
    void createAndMoveMonster3(float dt);



    // implement the "static create()" method manually
    CREATE_FUNC(ThirdScene);
};

#endif // __THIRD_SCENE_H__
