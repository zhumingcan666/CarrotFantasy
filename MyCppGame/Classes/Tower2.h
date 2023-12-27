#pragma once
#ifndef __TOWER2_H__
#define __TOWER2_H__
#include "cocos2d.h"
#define MAX_TOWER2_LEVEL 3
class Tower2 : public cocos2d::Sprite
{
public:
    static Tower2* createTower(const std::string& towerImage); // 创建防御塔实例的静态方法
    bool init(const std::string& towerImage); // 初始化方法
    int towerLevel2 = 1;//定义炮塔等级，后续通过upgradeTower函数实现升级
private:

    int towerLevel;//定义炮塔等级，后续通过upgradeTower函数实现升级
    std::string m_towerImage; // 防御塔的图片路径
    // 在 Tower 类中添加一个成员变量来保存当前目标怪物的引用
    // 其他成员变量...
};

#endif // __TOWER2_H__


