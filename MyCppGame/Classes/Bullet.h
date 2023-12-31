#pragma once

#ifndef BULLET

#define BULLET

#include"Monster.h"

USING_NS_CC;




class Bullet : public Sprite {



public:

    Monster* monsterTarget;

    int bulletKind;//�ӵ������ࣨ1��2��3��

    int bulletLevel;//�ӵ��ȼ�

    int damage;//�˺�

    float slowDown;//����

    float speed;//�ٶ�

    Vec2 direction;//����

    bool collidedJudge;//�ж��Ƿ��Ѿ���ײ����


    int bulletPositionX;

    int bulletPositionY;


    static Bullet* createSprite(int x, int y, Monster* target, int kind, int level);

    Bullet() {};

    Bullet(int x, int y, Monster* target, int kind, int level) {

        bulletPositionX = x;

        bulletPositionY = y;

        monsterTarget = target;

        bulletKind = kind;

        bulletLevel = level;

        collidedJudge = false;

        if (kind == 3)slowDown = 30.0f;

        else slowDown = 0.0f;

    }

    virtual bool init();




    //onEnter���������Զ����ã�scheduleUpdate���������Զ�ѭ������update����

    //����Bullet����Զ�ѭ������update����

    void update(float dt);

    void onEnter() override {

        Sprite::onEnter();

        scheduleUpdate();

    }


};
#endif