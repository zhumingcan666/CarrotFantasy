#pragma once
#ifndef COIN
#define COIN
#include "cocos2d.h"
#include<string>
USING_NS_CC;

class Coin : public Sprite
{
public:
    int coinCount;       // 金币数量
    cocos2d::Label* coinLabel;    // 用于显示金币数量的 Label

     Coin();
    virtual bool init();

    void setCoinCount(const int value)//传进来的值进行+=，传正数加钱，负数减钱；
    {
        coinCount += value;
    }

    void updateCoinLabel(float dt);
    CREATE_FUNC(Coin);

};
#endif // !Coin
