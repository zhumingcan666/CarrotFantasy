#pragma once
#ifndef COIN
#define COIN
#include "cocos2d.h"
#include<string>
USING_NS_CC;

class Coin : public Sprite
{
public:
    int coinCount;       // �������
    cocos2d::Label* coinLabel;    // ������ʾ��������� Label

     Coin();
    virtual bool init();

    void setCoinCount(const int value)//��������ֵ����+=����������Ǯ��������Ǯ��
    {
        coinCount += value;
    }

    void updateCoinLabel(float dt);
    CREATE_FUNC(Coin);

};
#endif // !Coin
