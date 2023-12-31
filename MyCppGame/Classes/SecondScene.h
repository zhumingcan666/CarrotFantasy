#pragma once
#ifndef __SECOND_SCENE_H__
#define __SECOND_SCENE_H__
#include "cocos2d.h"
#include"Monster.h"
#include"carrot.h"
#include <iostream>
#include <fstream>
#include"levelSelectScene.h"

///////////////////////声明第二个场景，也就是游戏界面（map）//////////////////////
class SecondScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//计数器，记录音乐控制按钮点击次数
    virtual bool init();
    // 创建并移动怪物的函数
    void menuBackHome(cocos2d::Ref* pSender);
    void menuBack(cocos2d::Ref* pSender);
    void SecondScene::MusicControl(Ref* sender);
    void createAndMoveMonster1(float dt);
    void createAndMoveMonster2(float dt);
    void createAndMoveMonster3(float dt);

    //关卡保存：为了实现过关保存，只需要添加一个bool变量，且该bool变量存储在外部，通过该变量实现后续关卡的点击打开。
//当第一个关卡成功过关时，设定可以打开第二关，即设置第二关的控制bool变量为1；
//添加一个写入状态函数，
    void saveGameProgress(bool isGameCompleted) {
        std::string filePath = "game_progress.txt";
        std::ofstream file(filePath, std::ios::trunc); // 使用 std::ios::trunc 标志,每次调用都覆写
        if (file.is_open()) {
            file << isGameCompleted << std::endl;
            file.close();
            std::cout << "Game progress saved successfully." << std::endl;
        }
        else {
            std::cout << "Failed to save game progress." << std::endl;
        }
    }
    //添加一个读取状态函数
    void loadGameProgress(bool& isGameCompleted) {

        std::string filePath = "game_progress.txt";
        std::ifstream file(filePath);
        if (file.is_open()) {
            file >> isGameCompleted;
            file.close();
        }
        else {
            std::cout << "Failed to load game progress." << std::endl;
        }
    }




    /// 用于计算开局倒计时
    int countdown = 3;
    void countDown(float dt);
    ///怪物波数
    int round=1;
    int round1_=0;
    int round2_ = 0;
    int round3_ = 0;

    ///加倍速按钮调用的函数
    int speedCount=1;
    void speedUp(Ref* pSender);
    ///    暂停按钮
    int stopCount=1;
    void stopORstart(Ref* pSender);



    bool Win=0;
   void checkWin(float dt)
    {
        if (round == 4) {
            cocos2d::Scene* scene = Director::getInstance()->getRunningScene();
             Monster* object = nullptr;
             Vector<Node*> children =scene->getChildren();
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
            levelSelect::thirdScene = 1;
            saveGameProgress(levelSelect::thirdScene);
            auto spritewin = Sprite::create("win.png");
            // 将场景图片定位在屏幕中央
            spritewin->setPosition(1300,900);
           this-> addChild(spritewin, 4);
        }

    }
    // implement the "static create()" method manually
    CREATE_FUNC(SecondScene);

    
};

#endif // __SECOND_SCENE_H_