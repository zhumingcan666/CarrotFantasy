#include"cocos2d.h"
#include"Bullet.h"
#include"Monster.h"
USING_NS_CC;


Bullet* Bullet::createSprite(int x,int y,Monster* target,int kind,int level)
{
    Bullet* bullet = new Bullet(x,y,target,kind,level);
    if (bullet && bullet->init()) {
        bullet->autorelease();
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}

// 在文件不存在时打印有用的错误消息而不是导致段错误.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BossScene.cpp\n");
}

bool Bullet::init()
{
    if (!Sprite::init()) {
        // 初始化失败
        return false;
    }
	// 获取屏幕可见尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 获取屏幕原点坐标
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //初始值
    speed = 500.0;
    damage = 35;

    //子弹运动时的动画
    auto bulletCache = SpriteFrameCache::getInstance();//缓存子弹序列

    char bulletName[20] = {0};
    if(bulletKind == 1) sprintf(bulletName,"PBottle%d.plist",bulletLevel);
    else if(bulletKind == 2){
        sprintf(bulletName,"PFan%d.png",bulletLevel);
        auto fanBullet = Sprite::initWithFile(bulletName);
    }
    else if(bulletKind == 3) sprintf(bulletName, "PShit%d.plist", bulletLevel);

	if(bulletKind == 1) bulletCache->addSpriteFramesWithFile(bulletName);
    else if(bulletKind == 3) bulletCache->addSpriteFramesWithFile(bulletName);

    //取帧
    if(bulletKind != 2)
    {
        Vector<SpriteFrame*> vec;
        char name[20];
        memset(name, 0, 20);
        
        int frameNum;//帧数
        if(bulletKind == 1)frameNum = 3;
        else frameNum = 2;
        
        for (int i = 1; i <= frameNum; i++)
        {
            if(bulletKind == 1) sprintf(name, "PBottle%d%d.png", bulletLevel,i);
            else if(bulletKind == 3) sprintf(name, "PShit%d%d.png", bulletLevel, i);

            vec.pushBack(bulletCache->getSpriteFrameByName(name));

        }
        

        Animation* animation;//动画
        animation = Animation::createWithSpriteFrames(vec, 0.01f);
        Animate* animate = Animate::create(animation);

        auto animateSprite = Sprite::create();
        this->addChild(animateSprite);
        animateSprite->runAction(RepeatForever::create(animate));//运行动画
    }
    
    return true;
}

void Bullet::update(float dt)
{
    if(bulletKind == 2) this->setRotation(this->getRotation() + 10);

    //移动方向(风扇子弹比较特殊,要考虑穿透)
    if (bulletKind != 2 || !collidedJudge) direction = monsterTarget->getPosition() - this->getPosition();
    //转动子弹指向怪物
    float angle = atan2f(direction.y, direction.x);
    angle = CC_RADIANS_TO_DEGREES(angle); // 将弧度转换为角度
    // 设置旋转角度
    if(bulletKind != 2) this->setRotation(-angle + 90);
    //距离
    float distance = direction.length();
    //移动速度（一个矢量）
    Vec2 velocity = direction.getNormalized() * speed * dt;

    if(distance <= 20 && !collidedJudge)//子弹接触到怪时
    {
        collidedJudge = true;//标记为已碰撞过

        monsterTarget->setHealth(monsterTarget->getHealth() - damage);//对怪物造成伤害
        if(monsterTarget->getSpeed() > 30.0f) monsterTarget->setSpeed(monsterTarget->getSpeed() - slowDown);//对怪物减速

        auto healthBar = monsterTarget->getHealthBar();//获取怪物血条
        healthBar->setPercentage(monsterTarget->getHealth());//更新血条
        
        if(monsterTarget->getHealth() <= 0)//把怪打死了
            monsterTarget->removeFromParent();

        if(bulletKind != 2)//除风扇子弹外，其余类型子弹均不穿透
            removeFromParent();//将子弹从场景中移除
    }
    else
        this->setPosition(this->getPosition() + velocity);//更新子弹位置

}