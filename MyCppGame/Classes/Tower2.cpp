#include "Tower2.h"
#include"SecondScene.h"
#include"Monster.h"
#include"Tower.h"
USING_NS_CC;
Tower2* Tower2::createTower(const std::string& towerImage)
{
    Tower2* tower = new Tower2();
    if (tower && tower->init(towerImage))
    {
        tower->autorelease();
        return tower;
    }
    else
    {
        delete tower;
        return nullptr;
    }
}

bool Tower2::init(const std::string& towerImage)
{
    if (!Sprite::initWithFile(towerImage))
    {
        return false;
    }

    m_towerImage = towerImage;//ÅÚËþÍ¼Æ¬Â·¾¶

    return true;
}

