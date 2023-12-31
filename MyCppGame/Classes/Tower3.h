#pragma once
#ifndef __TOWER3_H__
#define __TOWER3_H__
#include "cocos2d.h"
#define MAX_TOWER2_LEVEL 3
class Tower3 : public cocos2d::Sprite
{
public:
    static Tower3* createTower(const std::string& towerImage); // ����������ʵ���ľ�̬����
    bool init(const std::string& towerImage); // ��ʼ������
    int towerLevel3 = 1;//���������ȼ�������ͨ��upgradeTower����ʵ������
    void Tower3::handleBulletSpriteCollisions3();
    void Tower3::update(float delta);
private:
    std::string m_towerImage; // ��������ͼƬ·��
    // �� Tower �������һ����Ա���������浱ǰĿ����������
    // ������Ա����...
};

#endif // __TOWER3_H__


