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
    //萝卜等级
    //缓存HP的所有贴图
    SpriteFrameCache* carrotHPCache;
    //缓存carrot的所有贴图
    SpriteFrameCache* carrotCache;
    //用于检测碰撞
    Rect carrotBoundingBox;


public:
    int level;

    static int carrotPositionX;
    static int carrotPositionY;
    static int carrotHPPositionX;
    static int carrotHPPositionY;

    static Carrot* createSprite(int x, int y);
    virtual bool init();

    //更新生命值并更换HP贴图
    void carrotUpdate();
    //处理碰撞
    void handleMonsterSpriteCollisions(float dt);
    //萝卜升级
    void levelUp();
    //萝卜的特殊技能（点击才能发动）
    void skillSlowDown();
    void skillDestoryAll();

    CREATE_FUNC(Carrot);
};



#endif // !CARROT
