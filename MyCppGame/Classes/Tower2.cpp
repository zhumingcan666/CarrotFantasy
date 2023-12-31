#include "Tower2.h"
#include"SecondScene.h"
#include"Monster.h"
#include"Tower.h"
#include"Bullet.h"
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

    m_towerImage = towerImage;//炮塔图片路径
    //射击
    schedule(schedule_selector(Tower2::shootBullet2), 2.0f);
    return true;
}

void Tower2::update(float dt)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();
        this->currentTarget = nullptr;
        // 如果当前没有目标，或者当前目标已经被销毁，设置新的目标
        if (this->currentTarget == nullptr /*|| currentTarget->isDestroyed()*/)
        {
            // 遍历子节点
            for (Node* child : children)
            {
                // 检查子节点是否为怪物精灵实例
                Monster* monster = dynamic_cast<Monster*>(child);
                if (monster)
                {
                    // 获取炮塔和怪物的位置
                    Vec2 towerPos = this->getPosition();
                    Vec2 monsterPos = monster->getPosition();

                    // 计算炮塔与怪物之间的距离
                    float distance = towerPos.distance(monsterPos);

                    // 设置一个距离阈值，例如 500 像素
                    if (towerLevel2 == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel2 == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel2 == 3)
                    {
                        float distanceThreshold = 700.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                }
            }
        }
    }
}

void Tower2::shootBullet2(float dt)
{
    if (currentTarget != nullptr) {
        auto bullet = Bullet::createSprite(getPosition().x, getPosition().y, currentTarget, 2, towerLevel2);
        addChild(bullet);
    }
}

