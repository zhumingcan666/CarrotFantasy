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
