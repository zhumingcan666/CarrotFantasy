#pragma once
#ifndef MONSTER
#define MONSTER
#include "cocos2d.h"
#include<string>
USING_NS_CC;


/*********************������*****************************/
class Monster : public Sprite {
private:
    float speed;//�ƶ��ٶ�
    int health;//����ֵ
    std::string fileName;//�ļ���
    int damage;//�˺��ߵ�
    std::vector<Vec2> path;//�ƶ�·��

    ProgressTimer* healthBar;//������

    bool isAccelerationScheduled;//��ʱ��

public:

    int value;//�����ֵ


    Monster(float spd, int hp, const std::string& fname, int dmg, int valu, const std::vector<Vec2>& pat)
        : speed(spd), health(hp), fileName(fname), damage(dmg), value(valu),path(pat) {}

    static Monster* create(float spd, int hp, const std::string& fname, int dmg, int value, const std::vector<Vec2>& path);//���봫�Σ�ʵ�ֲ�ͬ������߼�

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
        isAccelerationScheduled = true;  // ��Ǽ��ټ�ʱ��������

        auto accelerationCallback = [this](float dt) {
            // ������ִ�м��ٲ���
            this->removeFromParent(); // �������Ϊԭ��������

            isAccelerationScheduled = false;  // ��Ǽ��ټ�ʱ�������
       };


        this->scheduleOnce(accelerationCallback, delay, "acceleration_timer");
    }//���ڼ�ʱ

    void handleBulletSpriteCollisions();//���ڴ�����Bulletʵ������ײ


};
#endif // !Monster
