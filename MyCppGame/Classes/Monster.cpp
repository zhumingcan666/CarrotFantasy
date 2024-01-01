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
