#include "Tower3.h"
#include"SecondScene.h"
#include"Monster.h"
#include"Tower.h"
#include"Bullet.h"

USING_NS_CC;
Tower3* Tower3::createTower(const std::string& towerImage)
{
    Tower3* tower = new Tower3();
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

bool Tower3::init(const std::string& towerImage)
{
    if (!Sprite::initWithFile(towerImage))
    {
        return false;
    }
    // 注册 update 函数
    this->scheduleUpdate();

    //射击
    schedule(schedule_selector(Tower3::shootBullet3), 2.5f);

    return true;
}
void Tower3::handleBulletSpriteCollisions3()//实现炮塔转向
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();
        Monster* currentTarget = nullptr;
        // 如果当前没有目标，或者当前目标已经被销毁，设置新的目标
        if (currentTarget == nullptr /*|| currentTarget->isDestroyed()*/)
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
                    if (towerLevel3 == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel3 == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel3 == 3)
                    {
                        float distanceThreshold = 700.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                }
            }
        }

        // 如果当前有目标，计算炮塔指向怪物的角度
        if (currentTarget)
        {
            Vec2 towerPos = this->getPosition();
            Vec2 monsterPos = currentTarget->getPosition();

            float angle = atan2f(monsterPos.y - towerPos.y, monsterPos.x - towerPos.x);
            angle = CC_RADIANS_TO_DEGREES(angle); // 将弧度转换为角度

            // 设置炮塔旋转角度
            this->setRotation(-angle + 90); // 注意这里可能需要调整角度，具体情况根据你的游戏坐标系而定
        }
    }
}
void Tower3::update(float delta) {
    // 在 update 函数中实时更新炮塔的转向逻辑
    handleBulletSpriteCollisions3(); // 调用处理转向的函数


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
                    if (towerLevel3 == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel3 == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel3 == 3)
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

void Tower3::shootBullet3(float dt)
{
    if (currentTarget != nullptr) {
        auto bullet = Bullet::createSprite(getPosition().x, getPosition().y, currentTarget, 3, towerLevel3);
        addChild(bullet);
    }
}