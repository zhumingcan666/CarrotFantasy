#pragma once

#ifndef BULLET

#define BULLET

#include"Monster.h"

USING_NS_CC;




class Bullet : public Sprite {



public:

    Monster* monsterTarget;

    int bulletKind;//子弹的种类（1、2、3）

    int bulletLevel;//子弹等级

    int damage;//伤害

    float slowDown;//减速

    float speed;//速度

    Vec2 direction;//方向

    bool collidedJudge;//判断是否已经碰撞过了


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




    //onEnter函数可以自动调用，scheduleUpdate函数可以自动循环调用update函数

    //所以Bullet类会自动循环调用update函数

    void update(float dt);

    void onEnter() override {

        Sprite::onEnter();

        scheduleUpdate();

    }


};
#endif