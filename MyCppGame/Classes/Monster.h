#pragma once
#ifndef MONSTER
#define MONSTER
#include "cocos2d.h"
#include<string>
#include"Tower.h"
USING_NS_CC;


/*********************怪物类*****************************/
class Monster : public Sprite {
private:
    float speed;//移动速度
    int health;//健康值
    std::string fileName;//文件名
    int damage;//伤害高低
    std::vector<Vec2> path;//移动路径


public:

    bool isPoisoned=0;
    Sprite* poisonSprite;
    ProgressTimer* healthBar;//生命条
    int value;//怪物价值



    bool countStart = false;//用于计时



    Monster(float spd, int hp, const std::string& fname, int dmg, int valu, const std::vector<Vec2>& pat)
        : speed(spd), health(hp), fileName(fname), damage(dmg), value(valu),path(pat) {}

    //用于传递参数，先后为：速度、生命值、贴图、伤害、价值、路径
    static Monster* create(float spd, int hp, const std::string& fname, int dmg, int value, const std::vector<Vec2>& path);//用与传参，实现不同怪物的逻辑

    int getHealth() const {
        return health;
    }
    float getSpeed() const {
        return speed;
    }

    void setHealth(int health) {
        this->health = health;
    }
    void setSpeed(float speed) {
        this->speed = speed;
    }
    ProgressTimer* HealthBar()
    {
        return healthBar;
    }

    void scheduleAcceleration(float delay);//用于处理子弹加速后恢复原有速度

    virtual bool init();
    void monsterUpdate(float dt);

    void handleBulletSpriteCollisions(float dt);//用于处理与Bullet实例的碰撞


};
#endif // !Monster
