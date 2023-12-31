#include"cocos2d.h"
#include"Monster.h"
#include"carrot.h"
#include"Coin.h"
#include"Bullet.h"
#include"Tower.h"
USING_NS_CC;


Monster* Monster::create(float spd, int hp, const std::string& fname, int dmg, int value, const std::vector<Vec2>& path) {
    Monster* monster = new Monster(spd, hp, fname, dmg, value, path);
    if (monster && monster->init()) {
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return nullptr;
}

bool Monster::init() {
    if (!Sprite::initWithFile(fileName)) {
        return false;
    }

    ////给怪物加上收缩变化
    ScaleTo* scaleAction = ScaleTo::create(1.0f, 0.95f);
    ScaleTo* reverseScaleAction = ScaleTo::create(1.0f, 1.03f);
    Sequence* scaleSequence = Sequence::create(scaleAction, reverseScaleAction, nullptr);
    RepeatForever* repeatAction = RepeatForever::create(scaleSequence);
   this->runAction(repeatAction);


   //这是怪物的血条逻辑
   Sprite* healthBarFill = Sprite::create("healthBar.png");
   healthBar = ProgressTimer::create(healthBarFill);
   healthBar->setType(ProgressTimer::Type::BAR);
   healthBar->setMidpoint(Vec2(0, 0.5));
   healthBar->setBarChangeRate(Vec2(1, 0));
   healthBar->setPosition(Vec2(getContentSize().width * 0.5f, getContentSize().height));
   healthBar->setPercentage(this->getHealth());
   this->addChild(healthBar);

   ///中毒显示
   poisonSprite = Sprite::create("poison.png"); // 替换为您的中毒外观图片路径
   poisonSprite->setPosition(this->getPosition().x+50, this->getPosition().y + 50); // 设置中毒外观的位置
   poisonSprite->setVisible(isPoisoned); // 初始时隐藏中毒外观
   this->addChild(poisonSprite); // 将中毒外观添加为Monster类的子节点


   //每一帧都调用Update函数
    schedule(CC_SCHEDULE_SELECTOR(Monster::monsterUpdate));
    return true;
}

//update，处理位置信息，并调用碰撞函数
void Monster::monsterUpdate(float dt) 
{
    poisonSprite->setVisible(isPoisoned); // 初始时隐藏中毒外观

    //检测是否发生与Bullet发生碰撞
    this->handleBulletSpriteCollisions(0.0);

    if (path.empty()) {
        // 如果路径为空，则不进行移动
        return;
    }
    // 获取当前目标点
    Vec2 targetPoint = path.front();

    // 计算朝目标点的方向向量
    Vec2 direction = targetPoint - getPosition();
    direction.normalize();
    // 计算每帧需要移动的距离
    float distance = speed * dt;

    if (distance >= targetPoint.distance(getPosition())) {
        // 如果当前位置已经接近目标点，移动到目标点并移除路径中的该点
        setPosition(targetPoint);
        path.erase(path.begin());
    }

    else {
        // 否则，更新位置
        setPosition(getPosition() + direction * distance);
    }
 
}
//用于处理与子弹碰撞后的各种事宜，如：减生命值、减速、显示中毒外观、怪物死亡（金币系统增加）、
void Monster::handleBulletSpriteCollisions(float dt)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();
    Coin* coin = scene->getChildByTag<Coin*>(1001);
    Tower* towerInstance = scene->getChildByTag<Tower*>(10);

    if (scene)
    {

        Vector<Node*> children = towerInstance->getChildren();
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
                    this->health  -= bullet->damage;
                    if (this->health <= 0)
                        this->health = 0;

                    this->healthBar->setPercentage(health);//减去生命值
                    if (this->health <=0) {
                       if (coin != nullptr)
                         {
                           coin->setCoinCount(this->value);//怪物死亡，coins增加
                         }
                       this->removeFromParent();//删除怪物
                    }


                    if (bullet->bulletKind==1) {
                        countStart = 1;//怪物减速，速度减半，中毒外观，3秒后恢复
                        this->setSpeed(getSpeed() / 2);
                        this->isPoisoned = 1;
                    }
                    if (countStart) {//指定时间后恢复速度,3s
                        countStart = false;
                        this->scheduleAcceleration(3.0f);
                    }
                    if (bullet->bulletKind != 2);
                        bullet->removeFromParent();
                }

            }

        }
    }

}
//用于恢复怪物原始速度，恢复原始外观
void Monster::scheduleAcceleration(float delay) {
    auto accelerationCallback = [this](float dt) {
        // 在这里执行加速操作
        this->setSpeed(getSpeed()*2); // 假设加速为原来的两倍
        this->isPoisoned = 0;//中毒外观不可见
        };
    this->scheduleOnce(accelerationCallback, delay, "acceleration_timer");
}//用于计时
