#include"cocos2d.h"
#include"Coin.h"
#include"Barrier.h"
#include"Bullet.h"
USING_NS_CC;

Barrier* Barrier::create( const std::string& fname, int value,int health) {
   Barrier* barrier = new Barrier( fname, value,health);
    if (barrier && barrier->init()) {
        barrier->autorelease();
        return barrier;
    }
    CC_SAFE_DELETE(barrier);
    return nullptr;
}

bool Barrier::init() {

if (!Sprite::initWithFile(fileName)) {
    return false;
}


//这是障碍物的血条逻辑
Sprite* healthBarFill = Sprite::create("healthBar1.png");
healthBar = ProgressTimer::create(healthBarFill);
healthBar->setType(ProgressTimer::Type::BAR);
healthBar->setMidpoint(Vec2(0, 0.5));
healthBar->setBarChangeRate(Vec2(1, 0));
healthBar->setPosition(Vec2(getContentSize().width * 0.5f, getContentSize().height));
healthBar->setPercentage(this->health);
this->addChild(healthBar);

//每一帧都调用Update函数
schedule(CC_SCHEDULE_SELECTOR(Barrier::barrierUpdate));
return true;
}

//检测碰撞，删除障碍物，增加金币
void Barrier::barrierUpdate(float dt)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();
    Coin* coin = scene->getChildByTag<Coin*>(1001);
    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();
        // 遍历子节点
        for (Node* child : children)
        {
            // 检查子节点是否为Bullet精灵实例
            Bullet* bullet = dynamic_cast<Bullet*>(child);
            if (bullet)
            {
                // 执行碰撞检测
                if (this->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
                {
                    this->healthBar->setPercentage((health -= bullet->damage));//减去生命值
                    if (this->health <= 0) {
                        if (coin != nullptr)
                        {
                            coin->setCoinCount(this->value);//怪物死亡，coins增加
                        }
                        scene->removeChild(this);//删除怪物
                    }
                }

            }
        }
    }

}
