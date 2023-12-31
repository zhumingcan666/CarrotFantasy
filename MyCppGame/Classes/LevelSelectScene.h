#pragma once
#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include <fstream>


//用全局变量实现保存关卡
namespace levelSelect {
    extern bool thirdScene;
}

class LevelSelectScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    std::vector<cocos2d::Sprite*> levelCards; // 对Sprite使用正确的命名空间
    cocos2d::Vec2 touchStartPos;
    void changeLevel(int direction); // 移除了 "LevelSelectScene::"
    const float minSwipeDistance = 50.0f;



    //关卡保存：为了实现过关保存，只需要添加一个bool变量，且该bool变量存储在外部，通过该变量实现后续关卡的点击打开。
//当第一个关卡成功过关时，设定可以打开第二关，即设置第二关的控制bool变量为1；
// 存储在外部的game_progress.txt文件中，
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


    void reset(Ref* sender);
    void backHome(Ref* sender);
    CREATE_FUNC(LevelSelectScene);

};

#endif // __LEVELSELECT_SCENE_H__
