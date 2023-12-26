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


//�����ϰ����Ѫ���߼�
Sprite* healthBarFill = Sprite::create("healthBar1.png");
healthBar = ProgressTimer::create(healthBarFill);
healthBar->setType(ProgressTimer::Type::BAR);
healthBar->setMidpoint(Vec2(0, 0.5));
healthBar->setBarChangeRate(Vec2(1, 0));
healthBar->setPosition(Vec2(getContentSize().width * 0.5f, getContentSize().height));
healthBar->setPercentage(this->health);
this->addChild(healthBar);

//ÿһ֡������Update����
schedule(CC_SCHEDULE_SELECTOR(Barrier::barrierUpdate));
return true;
}

//�����ײ��ɾ���ϰ�����ӽ��
void Barrier::barrierUpdate(float dt)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();
    Coin* coin = scene->getChildByTag<Coin*>(1001);
    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();
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
                    this->healthBar->setPercentage((health -= bullet->damage));//��ȥ����ֵ
                    if (this->health <= 0) {
                        if (coin != nullptr)
                        {
                            coin->setCoinCount(this->value);//����������coins����
                        }
                        scene->removeChild(this);//ɾ������
                    }
                }

            }
        }
    }

}
