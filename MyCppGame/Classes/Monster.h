#pragma once
#ifndef MONSTER
#define MONSTER
#include "cocos2d.h"
#include<string>
USING_NS_CC;


/*********************怪物类*****************************/
class Monster : public Sprite {
private:
    float speed;//移动速度
    int health;//健康值
    std::string fileName;//文件名
    int damage;//伤害高低
    std::vector<Vec2> path;//移动路径

    ProgressTimer* healthBar;//生命条

    bool isAccelerationScheduled;//计时器

public:

    int value;//怪物价值


    Monster(float spd, int hp, const std::string& fname, int dmg, int valu, const std::vector<Vec2>& pat)
        : speed(spd), health(hp), fileName(fname), damage(dmg), value(valu),path(pat) {}

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
    void setPath(const std::vector<Vec2>& newPath) {
        path = newPath;
    }
    virtual bool init();
    void monsterUpdate(float dt);


    void scheduleAcceleration(float delay) {
        isAccelerationScheduled = true;  // 标记加速计时器已启动

        auto accelerationCallback = [this](float dt) {
            // 在这里执行加速操作
            this->removeFromParent(); // 假设加速为原来的两倍

            isAccelerationScheduled = false;  // 标记加速计时器已完成
       };


        this->scheduleOnce(accelerationCallback, delay, "acceleration_timer");
    }//用于计时

    void handleBulletSpriteCollisions();//用于处理与Bullet实例的碰撞


};
#endif // !Monster
