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

    m_towerImage = towerImage;//����ͼƬ·��
    //���
    schedule(schedule_selector(Tower2::shootBullet2), 2.0f);
    return true;
}

void Tower2::update(float dt)
{
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
                    if (towerLevel2 == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel2 == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            this->currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel2 == 3)
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

void Tower2::shootBullet2(float dt)
{
    if (currentTarget != nullptr) {
        auto bullet = Bullet::createSprite(getPosition().x, getPosition().y, currentTarget, 2, towerLevel2);
        addChild(bullet);
    }
}

