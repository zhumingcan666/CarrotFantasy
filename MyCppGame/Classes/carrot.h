#pragma once
#ifndef CARROT
#define CARROT
#include"cocos2d.h"
USING_NS_CC;
class Carrot : public Sprite
{
private:
    //萝卜贴图和HP贴图在坐标系中的位置
   
    //生命值
    int HP;
    //缓存HP的所有贴图
    SpriteFrameCache* carrotHPCache;
public:
    static int carrotPositionX;
    static int carrotPositionY;
    static int carrotHPPositionX;
    static int carrotHPPositionY;

    static Sprite* createSprite(int x,int y);
    virtual bool init();

    //更新生命值并更换HP贴图
    void carrotUpdate(float dt);

    CREATE_FUNC(Carrot);
};



#endif // !CARROT
