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
    //����ֵ
    int HP;
    //�ܲ���̬(һ��7�ֱ�����̬)
    int form;
    //����HP��������ͼ
    SpriteFrameCache* carrotHPCache;
    //����carrot��������ͼ
    SpriteFrameCache* carrotCache;
    Rect carrotBoundingBox;//���ڼ����ײ


public:
    static int carrotPositionX;
    static int carrotPositionY;
    static int carrotHPPositionX;
    static int carrotHPPositionY;

    static Sprite* createSprite(int x,int y);
    virtual bool init();

    //��������ֵ������HP��ͼ
    void carrotUpdate();

    void handleMonsterSpriteCollisions(float dt);

    CREATE_FUNC(Carrot);
};



#endif // !CARROT
