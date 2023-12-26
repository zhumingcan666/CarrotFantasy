#include"Coin.h"
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
//³õÊ¼»¯
Coin::Coin()
    : coinCount(200),
    coinLabel(nullptr)
{
}
bool Coin::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    coinLabel = Label::createWithTTF("Coins: 0", "fonts/Marker Felt.ttf", 36);
    coinLabel->setPosition(Vec2(200, 1200));
    this->addChild(coinLabel);

    schedule(CC_SCHEDULE_SELECTOR(Coin::updateCoinLabel));
    return true;    

}

void Coin::updateCoinLabel(float dt)
{
    coinLabel->setString("Coins: " + std::to_string(coinCount));
}