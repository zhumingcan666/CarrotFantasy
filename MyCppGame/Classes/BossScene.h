#pragma once
#ifndef __BOSS_SCENE_H__
#define __BOSS_SCENE_H__

#include "cocos2d.h"


class BossScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//计数器，记录音乐控制按钮点击次数
    virtual bool init();
    void BossScene::MusicControl(Ref* sender);
    void menuBackHome(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(BossScene);
};

#endif // __BOSS_SCENE_H__
