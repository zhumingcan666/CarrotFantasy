#pragma once
#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"

class LevelSelectScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    std::vector<cocos2d::Sprite*> levelCards; // ��Spriteʹ����ȷ�������ռ�
    cocos2d::Vec2 touchStartPos;
    void changeLevel(int direction); // �Ƴ��� "LevelSelectScene::"
    const float minSwipeDistance = 50.0f;
    CREATE_FUNC(LevelSelectScene);
};

#endif // __LEVELSELECT_SCENE_H__
