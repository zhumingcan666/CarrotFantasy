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
    //�ܲ��ȼ�
    //����HP��������ͼ
    SpriteFrameCache* carrotHPCache;
    //����carrot��������ͼ
    SpriteFrameCache* carrotCache;
    //���ڼ����ײ
    Rect carrotBoundingBox;


public:
    int level;

    static int carrotPositionX;
    static int carrotPositionY;
    static int carrotHPPositionX;
    static int carrotHPPositionY;

    static Carrot* createSprite(int x, int y);
    virtual bool init();

    //��������ֵ������HP��ͼ
    void carrotUpdate();
    //������ײ
    void handleMonsterSpriteCollisions(float dt);
    //�ܲ�����
    void levelUp();
    //�ܲ������⼼�ܣ�������ܷ�����
    void skillSlowDown();
    void skillDestoryAll();

    CREATE_FUNC(Carrot);
};



#endif // !CARROT
