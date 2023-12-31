#pragma once
#ifndef __TOWER2_H__
#define __TOWER2_H__
#include "cocos2d.h"
#include"Monster.h"
#define MAX_TOWER2_LEVEL 3
class Tower2 : public cocos2d::Sprite
{
public:
    Monster* currentTarget;

    static Tower2* createTower(const std::string& towerImage); // ����������ʵ���ľ�̬����
    bool init(const std::string& towerImage); // ��ʼ������
    int towerLevel2 = 1;//���������ȼ�������ͨ��upgradeTower����ʵ������

    void update(float dt);//�������Ŀ��
    void onEnter() override {
        Sprite::onEnter();
        scheduleUpdate();
    }
    void shootBullet2(float dt);//���
private:

    int towerLevel;//���������ȼ�������ͨ��upgradeTower����ʵ������
    std::string m_towerImage; // ��������ͼƬ·��
    // �� Tower �������һ����Ա���������浱ǰĿ����������
    // ������Ա����...
};

#endif // __TOWER2_H__


