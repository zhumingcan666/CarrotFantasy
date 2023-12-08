#pragma once
#pragma once
#ifndef __THIRD_SCENE_H__
#define __THIRD_SCENE_H__
#include "cocos2d.h"
///////////////////////声明第二个场景，也就是游戏界面（map）//////////////////////
class ThirdScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//计数器，记录音乐控制按钮点击次数
    virtual bool init();
    // 创建并移动怪物的函数
    void createAndMoveMonster0(float dt);
    void menuBackHome(cocos2d::Ref* pSender);
    void ThirdScene::MusicControl(Ref* sender);
    // implement the "static create()" method manually
    CREATE_FUNC(ThirdScene);
};

#endif // __THIRD_SCENE_H__
