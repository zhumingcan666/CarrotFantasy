#include"cocos2d.h"
#include"Monster.h"
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
    ScaleTo* reverseScaleAction = ScaleTo::create(1.0f, 1.05f);
    Sequence* scaleSequence = Sequence::create(scaleAction, reverseScaleAction, nullptr);
    RepeatForever* repeatAction = RepeatForever::create(scaleSequence);
   this->runAction(repeatAction);






   Sprite* healthBarFill = Sprite::create("healthBar.png");
   healthBar = ProgressTimer::create(healthBarFill);
   healthBar->setType(ProgressTimer::Type::BAR);
   healthBar->setMidpoint(Vec2(0, 0.5));
   healthBar->setBarChangeRate(Vec2(1, 0));
   healthBar->setPosition(Vec2(getContentSize().width * 0.5f, getContentSize().height));

   healthBar->setPercentage(100);
   this->addChild(healthBar);


   //每一帧都调用Update函数
    schedule(CC_SCHEDULE_SELECTOR(Monster::monsterUpdate));
    return true;
}

void Monster::monsterUpdate(float dt) 
{
    //检测是否发生与Bullet发生碰撞
    this->handleBulletSpriteCollisions();

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

void Monster::handleBulletSpriteCollisions()
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 检查子节点是否为怪物精灵实例
            Monster* monster = dynamic_cast<Monster*>(child);
            if (monster)
            {
                // 执行碰撞检测
                if (this->getBoundingBox().intersectsRect(monster->getBoundingBox()))
                {


                }

            }

        }
    }
}
