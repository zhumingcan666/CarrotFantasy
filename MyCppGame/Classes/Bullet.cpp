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

// ���ļ�������ʱ��ӡ���õĴ�����Ϣ�����ǵ��¶δ���.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BossScene.cpp\n");
}

bool Bullet::init()
{
    if (!Sprite::init()) {
        // ��ʼ��ʧ��
        return false;
    }
	// ��ȡ��Ļ�ɼ��ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ȡ��Ļԭ������
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //��ʼֵ
    speed = 500.0;
    damage = 35;

    //�ӵ��˶�ʱ�Ķ���
    auto bulletCache = SpriteFrameCache::getInstance();//�����ӵ�����

    char bulletName[20] = {0};
    if(bulletKind == 1) sprintf(bulletName,"PBottle%d.plist",bulletLevel);
    else if(bulletKind == 2){
        sprintf(bulletName,"PFan%d.png",bulletLevel);
        auto fanBullet = Sprite::initWithFile(bulletName);
    }
    else if(bulletKind == 3) sprintf(bulletName, "PShit%d.plist", bulletLevel);

	if(bulletKind == 1) bulletCache->addSpriteFramesWithFile(bulletName);
    else if(bulletKind == 3) bulletCache->addSpriteFramesWithFile(bulletName);

    //ȡ֡
    if(bulletKind != 2)
    {
        Vector<SpriteFrame*> vec;
        char name[20];
        memset(name, 0, 20);
        
        int frameNum;//֡��
        if(bulletKind == 1)frameNum = 3;
        else frameNum = 2;
        
        for (int i = 1; i <= frameNum; i++)
        {
            if(bulletKind == 1) sprintf(name, "PBottle%d%d.png", bulletLevel,i);
            else if(bulletKind == 3) sprintf(name, "PShit%d%d.png", bulletLevel, i);

            vec.pushBack(bulletCache->getSpriteFrameByName(name));

        }
        

        Animation* animation;//����
        animation = Animation::createWithSpriteFrames(vec, 0.01f);
        Animate* animate = Animate::create(animation);

        auto animateSprite = Sprite::create();
        this->addChild(animateSprite);
        animateSprite->runAction(RepeatForever::create(animate));//���ж���
    }
    
    return true;
}

void Bullet::update(float dt)
{
    if(bulletKind == 2) this->setRotation(this->getRotation() + 10);

    //�ƶ�����(�����ӵ��Ƚ�����,Ҫ���Ǵ�͸)
    if (bulletKind != 2 || !collidedJudge) direction = monsterTarget->getPosition() - this->getPosition();
    //ת���ӵ�ָ�����
    float angle = atan2f(direction.y, direction.x);
    angle = CC_RADIANS_TO_DEGREES(angle); // ������ת��Ϊ�Ƕ�
    // ������ת�Ƕ�
    if(bulletKind != 2) this->setRotation(-angle + 90);
    //����
    float distance = direction.length();
    //�ƶ��ٶȣ�һ��ʸ����
    Vec2 velocity = direction.getNormalized() * speed * dt;

    if(distance <= 20 && !collidedJudge)//�ӵ��Ӵ�����ʱ
    {
        collidedJudge = true;//���Ϊ����ײ��

        monsterTarget->setHealth(monsterTarget->getHealth() - damage);//�Թ�������˺�
        if(monsterTarget->getSpeed() > 30.0f) monsterTarget->setSpeed(monsterTarget->getSpeed() - slowDown);//�Թ������

        auto healthBar = monsterTarget->getHealthBar();//��ȡ����Ѫ��
        healthBar->setPercentage(monsterTarget->getHealth());//����Ѫ��
        
        if(monsterTarget->getHealth() <= 0)//�ѹִ�����
            monsterTarget->removeFromParent();

        if(bulletKind != 2)//�������ӵ��⣬���������ӵ�������͸
            removeFromParent();//���ӵ��ӳ������Ƴ�
    }
    else
        this->setPosition(this->getPosition() + velocity);//�����ӵ�λ��

}