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
    // ע�� update ����
    this->scheduleUpdate();

    //���
    schedule(schedule_selector(Tower3::shootBullet3), 2.5f);

    return true;
}
void Tower3::handleBulletSpriteCollisions3()//ʵ������ת��
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();
        Monster* currentTarget = nullptr;
        // �����ǰû��Ŀ�꣬���ߵ�ǰĿ���Ѿ������٣������µ�Ŀ��
        if (currentTarget == nullptr /*|| currentTarget->isDestroyed()*/)
        {
            // �����ӽڵ�
            for (Node* child : children)
            {
                // ����ӽڵ��Ƿ�Ϊ���ﾫ��ʵ��
                Monster* monster = dynamic_cast<Monster*>(child);
                if (monster)
                {
                    // ��ȡ�����͹����λ��
                    Vec2 towerPos = this->getPosition();
                    Vec2 monsterPos = monster->getPosition();

                    // �������������֮��ľ���
                    float distance = towerPos.distance(monsterPos);

                    // ����һ��������ֵ������ 500 ����
                    if (towerLevel3 == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel3 == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel3 == 3)
                    {
                        float distanceThreshold = 700.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                }
            }
        }

        // �����ǰ��Ŀ�꣬��������ָ�����ĽǶ�
        if (currentTarget)
        {
            Vec2 towerPos = this->getPosition();
            Vec2 monsterPos = currentTarget->getPosition();

            float angle = atan2f(monsterPos.y - towerPos.y, monsterPos.x - towerPos.x);
            angle = CC_RADIANS_TO_DEGREES(angle); // ������ת��Ϊ�Ƕ�

            // ����������ת�Ƕ�
            this->setRotation(-angle + 90); // ע�����������Ҫ�����Ƕȣ�����������������Ϸ����ϵ����
        }
    }
}
void Tower3::update(float delta) {
    // �� update ������ʵʱ����������ת���߼�
    handleBulletSpriteCollisions3(); // ���ô���ת��ĺ���


    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();
        this->currentTarget = nullptr;
        // �����ǰû��Ŀ�꣬���ߵ�ǰĿ���Ѿ������٣������µ�Ŀ��
        if (this->currentTarget == nullptr /*|| currentTarget->isDestroyed()*/)
        {
            // �����ӽڵ�
            for (Node* child : children)
            {
                // ����ӽڵ��Ƿ�Ϊ���ﾫ��ʵ��
                Monster* monster = dynamic_cast<Monster*>(child);
                if (monster)
                {
                    // ��ȡ�����͹����λ��
                    Vec2 towerPos = this->getPosition();
                    Vec2 monsterPos = monster->getPosition();

                    // �������������֮��ľ���
                    float distance = towerPos.distance(monsterPos);

                    // ����һ��������ֵ������ 500 ����
                    if (towerLevel3 == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel3 == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel3 == 3)
                    {
                        float distanceThreshold = 700.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
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