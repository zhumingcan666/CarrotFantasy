#pragma once
#ifndef CARROT
#define CARROT
#include"cocos2d.h"
#include"Monster.h"
USING_NS_CC;
class Carrot : public Sprite
{
private:
private:
    //生命值
    int HP;
    //萝卜形态(一共7种被啃形态)
    int form;
    //缓存HP的所有贴图
    SpriteFrameCache* carrotHPCache;
    //缓存carrot的所有贴图
    SpriteFrameCache* carrotCache;
    Rect carrotBoundingBox;//用于检测碰撞


public:
    static int carrotPositionX;
    static int carrotPositionY;
    static int carrotHPPositionX;
    static int carrotHPPositionY;

    static Sprite* createSprite(int x,int y);
    virtual bool init();

    //更新生命值并更换HP贴图
    void carrotUpdate();

    void handleMonsterSpriteCollisions(float dt);

    CREATE_FUNC(Carrot);
};



#endif // !CARROT
