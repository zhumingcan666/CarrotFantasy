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

    ////��������������仯
    ScaleTo* scaleAction = ScaleTo::create(1.0f, 0.95f);
    ScaleTo* reverseScaleAction = ScaleTo::create(1.0f, 1.03f);
    Sequence* scaleSequence = Sequence::create(scaleAction, reverseScaleAction, nullptr);
    RepeatForever* repeatAction = RepeatForever::create(scaleSequence);
   this->runAction(repeatAction);


   //���ǹ����Ѫ���߼�
   Sprite* healthBarFill = Sprite::create("healthBar.png");
   healthBar = ProgressTimer::create(healthBarFill);
   healthBar->setType(ProgressTimer::Type::BAR);
   healthBar->setMidpoint(Vec2(0, 0.5));
   healthBar->setBarChangeRate(Vec2(1, 0));
   healthBar->setPosition(Vec2(getContentSize().width * 0.5f, getContentSize().height));
   healthBar->setPercentage(this->getHealth());
   this->addChild(healthBar);

   ///�ж���ʾ
   poisonSprite = Sprite::create("poison.png"); // �滻Ϊ�����ж����ͼƬ·��
   poisonSprite->setPosition(this->getPosition().x+50, this->getPosition().y + 50); // �����ж���۵�λ��
   poisonSprite->setVisible(isPoisoned); // ��ʼʱ�����ж����
   this->addChild(poisonSprite); // ���ж�������ΪMonster����ӽڵ�


   //ÿһ֡������Update����
    schedule(CC_SCHEDULE_SELECTOR(Monster::monsterUpdate));
    return true;
}

//update������λ����Ϣ����������ײ����
void Monster::monsterUpdate(float dt) 
{
    poisonSprite->setVisible(isPoisoned); // ��ʼʱ�����ж����

    //����Ƿ�����Bullet������ײ
    this->handleBulletSpriteCollisions(0.0);

    if (path.empty()) {
        // ���·��Ϊ�գ��򲻽����ƶ�
        return;
    }
    // ��ȡ��ǰĿ���
    Vec2 targetPoint = path.front();

    // ���㳯Ŀ���ķ�������
    Vec2 direction = targetPoint - getPosition();
    direction.normalize();
    // ����ÿ֡��Ҫ�ƶ��ľ���
    float distance = speed * dt;

    if (distance >= targetPoint.distance(getPosition())) {
        // �����ǰλ���Ѿ��ӽ�Ŀ��㣬�ƶ���Ŀ��㲢�Ƴ�·���еĸõ�
        setPosition(targetPoint);
        path.erase(path.begin());
    }

    else {
        // ���򣬸���λ��
        setPosition(getPosition() + direction * distance);
    }
 
}
//���ڴ������ӵ���ײ��ĸ������ˣ��磺������ֵ�����١���ʾ�ж���ۡ��������������ϵͳ���ӣ���
void Monster::handleBulletSpriteCollisions(float dt)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();
    Coin* coin = scene->getChildByTag<Coin*>(1001);
    Tower* towerInstance = scene->getChildByTag<Tower*>(10);

    if (scene)
    {

        Vector<Node*> children = towerInstance->getChildren();
        // �����ӽڵ�
        for (Node* child : children)
        {
            // ����ӽڵ��Ƿ�ΪBullet����ʵ��
            Bullet* bullet = dynamic_cast<Bullet*>(child);
            if (bullet)
            {
                // ִ����ײ���
                if (this->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
                {
                    this->health  -= bullet->damage;
                    if (this->health <= 0)
                        this->health = 0;

                    this->healthBar->setPercentage(health);//��ȥ����ֵ
                    if (this->health <=0) {
                       if (coin != nullptr)
                         {
                           coin->setCoinCount(this->value);//����������coins����
                         }
                       this->removeFromParent();//ɾ������
                    }


                    if (bullet->bulletKind==1) {
                        countStart = 1;//������٣��ٶȼ��룬�ж���ۣ�3���ָ�
                        this->setSpeed(getSpeed() / 2);
                        this->isPoisoned = 1;
                    }
                    if (countStart) {//ָ��ʱ���ָ��ٶ�,3s
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
//���ڻָ�����ԭʼ�ٶȣ��ָ�ԭʼ���
void Monster::scheduleAcceleration(float delay) {
    auto accelerationCallback = [this](float dt) {
        // ������ִ�м��ٲ���
        this->setSpeed(getSpeed()*2); // �������Ϊԭ��������
        this->isPoisoned = 0;//�ж���۲��ɼ�
        };
    this->scheduleOnce(accelerationCallback, delay, "acceleration_timer");
}//���ڼ�ʱ
