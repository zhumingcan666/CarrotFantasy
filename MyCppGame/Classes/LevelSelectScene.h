#pragma once
#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"

class LevelSelectScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    std::vector<cocos2d::Sprite*> levelCards; // 对Sprite使用正确的命名空间
    cocos2d::Vec2 touchStartPos;
    void changeLevel(int direction); // 移除了 "LevelSelectScene::"
    const float minSwipeDistance = 50.0f;
    CREATE_FUNC(LevelSelectScene);
};

#endif // __LEVELSELECT_SCENE_H__
