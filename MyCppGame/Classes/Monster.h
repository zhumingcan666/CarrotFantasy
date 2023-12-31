#pragma once
#ifndef MONSTER
#define MONSTER
#include "cocos2d.h"
#include<string>
#include"Tower.h"
USING_NS_CC;


/*********************������*****************************/
class Monster : public Sprite {
private:
    float speed;//�ƶ��ٶ�
    int health;//����ֵ
    std::string fileName;//�ļ���
    int damage;//�˺��ߵ�
    std::vector<Vec2> path;//�ƶ�·��


public:

    bool isPoisoned=0;
    Sprite* poisonSprite;
    ProgressTimer* healthBar;//������
    int value;//�����ֵ



    bool countStart = false;//���ڼ�ʱ



    Monster(float spd, int hp, const std::string& fname, int dmg, int valu, const std::vector<Vec2>& pat)
        : speed(spd), health(hp), fileName(fname), damage(dmg), value(valu),path(pat) {}

    //���ڴ��ݲ������Ⱥ�Ϊ���ٶȡ�����ֵ����ͼ���˺�����ֵ��·��
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
    ProgressTimer* HealthBar()
    {
        return healthBar;
    }

    void scheduleAcceleration(float delay);//���ڴ����ӵ����ٺ�ָ�ԭ���ٶ�

    virtual bool init();
    void monsterUpdate(float dt);

    void handleBulletSpriteCollisions(float dt);//���ڴ�����Bulletʵ������ײ


};
#endif // !Monster
