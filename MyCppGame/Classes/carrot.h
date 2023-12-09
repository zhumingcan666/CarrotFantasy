#pragma once
#ifndef CARROT
#define CARROT
#include"cocos2d.h"
USING_NS_CC;
class Carrot : public Sprite
{
private:
    //�ܲ���ͼ��HP��ͼ������ϵ�е�λ��
   
    //����ֵ
    int HP;
    //����HP��������ͼ
    SpriteFrameCache* carrotHPCache;
public:
    static int carrotPositionX;
    static int carrotPositionY;
    static int carrotHPPositionX;
    static int carrotHPPositionY;

    static Sprite* createSprite(int x,int y);
    virtual bool init();

    //��������ֵ������HP��ͼ
    void carrotUpdate(float dt);

    CREATE_FUNC(Carrot);
};



#endif // !CARROT
