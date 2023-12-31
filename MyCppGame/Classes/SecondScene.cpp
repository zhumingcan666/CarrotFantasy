#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include"carrot.h"
#include"Bullet.h"
#include"Tower.h"
#include"Tower2.h"
#include<vector>
#include"LevelSelectScene.h"
#include"Coin.h"
#include"Monster.h"
#include <cstdlib>  // ���������������ͷ�ļ�
#include <ctime>    // ����ʱ�亯����ͷ�ļ�

USING_NS_CC;

/*********************************************************************������һ����ͼ����**********************************************************/
Scene* SecondScene::createScene()
{
    return SecondScene::create();
}

// ���ļ�������ʱ��ӡ���õĴ�����Ϣ�����ǵ��¶δ���.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
/*********************************************************************��ʼ����һ����ͼ����**********************************************************/
bool SecondScene::init()
{


    //////////////////////////////////////////////////��if(1)���Ǹ��ְ�ť��ʵ��
    if(1){
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        // ��ʼ��ʧ��
        return false;
    }

    // ��ȡ��Ļ�ɼ��ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ȡ��Ļԭ������
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��� "SecondScene" ����������
    auto sprite = Sprite::create("bg1.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg1.png'");
    }
    else
    {
        // ������ͼƬ��λ����Ļ����
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // ������ͼƬ���Ϊ�˲���ӽڵ�
        this->addChild(sprite, 0);
    }
       auto road = Sprite::create("road1.png");
        road->setPosition(Vec2(visibleSize.width / 2 + origin.x, 500));
        // ������ͼƬ���Ϊ�˲���ӽڵ�
        this->addChild(road, 0);
    auto menubg = Sprite::create("menubg(1).png");
    if (menubg == nullptr)
    {
        problemLoading("'menubg(1).png'");
    }
    else
    {
        // ������ͼƬ��λ����Ļ����
        menubg->setPosition(Vec2(visibleSize.width / 2 + origin.x - 70, 1250));

        // ������ͼƬ���Ϊ�˲���ӽڵ�
        this->addChild(menubg, 0);
    }
    /*********************************************************************����һ���������˵���ť��homeItem)**********************************************************/
    if (1) {
        //�ص�ѡ��ҳ��
        auto homeItem = MenuItemImage::create(
            "back.png",
            "back_pressed.png",
            CC_CALLBACK_1(SecondScene::menuBack, this));

        // ���ͼ���Ƿ���سɹ�����δ���سɹ��������������Ϣ
        if (homeItem == nullptr ||
            homeItem->getContentSize().width <= 0 ||
            homeItem->getContentSize().height <= 0)
        {
            problemLoading("'return.png' �� 'return.png'");
        }
        else
        {
            // ���÷��ذ�ť��λ��Ϊ���Ͻ�
            float x = 30;
            float y = 1250;
            homeItem->setPosition(Vec2(x, y));

        }


        // �����˵�������һ���Զ��ͷŵĶ���
        //�ص���ҳ��
        auto menu = Menu::create(homeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);

        auto backhome = MenuItemImage::create(
            "return1.png",
            "return.png",
            CC_CALLBACK_1(SecondScene::menuBackHome, this));
        backhome->setPosition(1700, 1250);
        auto menu1 = Menu::create(backhome, NULL);
        menu1->setPosition(Vec2::ZERO);
        this->addChild(menu1, 3);

    }
    /*********************************************************************������һ����ͼ������**********************************************************/
    // Ԥ���������ļ�
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);

    /******************************************************************����һ�����ֿ��ư�ť****************************************************/
    if (1) {
        auto musicItem = MenuItemImage::create(
            "share_fan_active.png",
            "share_fan_disable.png",
            CC_CALLBACK_1(SecondScene::MusicControl, this));

        // ���ͼ���Ƿ���سɹ�����δ���سɹ��������������Ϣ
        if (musicItem == nullptr ||
            musicItem->getContentSize().width <= 0 ||
            musicItem->getContentSize().height <= 0)
        {
            problemLoading("'share_fan_active.png' �� 'share_fan_disable.png'");
        }
        else
        {
            // ����ͼ���λ��
            float x = origin.x + 1930;
            float y = origin.y + 1250;
            musicItem->setPosition(Vec2(x, y));
        }
        // �����˵�������һ���Զ��ͷŵĶ���
        auto musicmenu = Menu::create(musicItem, NULL);
        musicmenu->setPosition(Vec2::ZERO);
        this->addChild(musicmenu, 2);


        auto label = Label::createWithTTF("Music", "fonts/Marker Felt.ttf", 24);
        if (label == nullptr)
        {
            problemLoading("'fonts/Marker Felt.ttf'");
        }
        else
        {
            // ����ǩ��λ����Ļ����
            label->setPosition(Vec2(origin.x + 1860,
                origin.y + 1250));

            // ����ǩ���Ϊ�˲���ӽڵ�
            this->addChild(label, 1);
        }

    }


   }
   //////////////////////////////////////////////////����Ϊ��ťʵ��


    /******************************************************************����****************************************************/

   auto speed = MenuItemImage::create(
       "speedup.png",
       "speedup1.png",
       CC_CALLBACK_1(SecondScene::speedUp, this));
   speed->setPosition(1500, 1250);
   auto menus = Menu::create(speed, NULL);
   menus->setPosition(Vec2::ZERO);
   this->addChild(menus, 3);
   /******************************************************************��ͣ****************************************************/

   auto stop = MenuItemImage::create(
       "stop.png",
       "stop1.png",
       CC_CALLBACK_1(SecondScene::stopORstart, this));
   stop->setPosition(1400, 1250);
   auto menust = Menu::create(stop, NULL);
   menust->setPosition(Vec2::ZERO);
   this->addChild(menust, 3);


   /******************************************************************����ʵ��****************************************************/
   Tower* tower = Tower::createTower("Bottle11.png");
   tower->setTag(10);
   this->addChild(tower);
   Tower2* fan = Tower2::createTower("Fan11.png");
   this->addChild(fan);

    /******************************************************************��������ʱ****************************************************/

   schedule(CC_SCHEDULE_SELECTOR(SecondScene::countDown), 0.8f, 2, 0);


    /******************************************************************�����ܲ�****************************************************/
    auto carrot = Carrot::createSprite(1775, 995);
    addChild(carrot);

    /************************************************************************�������ﾫ��***********************************************************************/

    schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster1), 3.50f);

    /************************************************************************�ж�ʤ��***********************************************************************/
    this->schedule(CC_SCHEDULE_SELECTOR(SecondScene::checkWin));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*********************************************************************�������ϵͳ**********************************************************/
    auto coin = Coin::create();
    coin->setTag(1001); // ���ö��صı�ǩ
    addChild(coin);
    return true;

}
/************************************************************************�������˵���ť�Ļص�����**********************************************************/
void SecondScene::menuBack(Ref* pSender)
{
    auto levelSelectScene = LevelSelectScene::create();
    Director::getInstance()->replaceScene(levelSelectScene);
}
void SecondScene::menuBackHome(Ref* pSender)
{
    auto home = HelloWorld::create();
    Director::getInstance()->replaceScene(home);
}

/***********************************************************************���Ʊ������ֵĻص�����***************************************************************/
void SecondScene::MusicControl(Ref* sender)
{
    // �л����ֵĲ���״̬
    if (Musiccontrol % 2 == 0)
    {
        // ��ͣ����
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        Musiccontrol++;
    }
    else
    {
        // �ָ����ֲ���
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        Musiccontrol++;
    }

}
void SecondScene::countDown(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ȡ��Ļԭ������
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto levelCard3 = Sprite::create(StringUtils::format("countdown%d.png", countdown));
        levelCard3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        addChild(levelCard3, 3);
     --countdown; 
     // �����ӳٶ�����1���ִ��ɾ������
     auto delayAction = DelayTime::create(0.85f);
     auto removeAction = RemoveSelf::create();
     auto sequenceAction = Sequence::create(delayAction, removeAction, nullptr);
     levelCard3->runAction(sequenceAction);
}
void  SecondScene::speedUp(Ref* pSender)
{
    ++speedCount;
    stopCount = 3;
    if(speedCount%2==0)
        Director::getInstance()->getScheduler()->setTimeScale(2.0f);
    else
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
}
void SecondScene::stopORstart(Ref* sender)
{
      ++stopCount;
      if (stopCount % 2 == 0)
      {
          Director::getInstance()->getScheduler()->setTimeScale(0.0f);
          speedCount = 2;

      }
    else {
        speedCount = 3;
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);

    }
}
void SecondScene::createAndMoveMonster1(float dt)
{
    std::vector<Vec2> path = {
Vec2(230, 470),
Vec2(715, 470),
Vec2(715, 620),
Vec2(1230, 620),
Vec2(1230, 470),
Vec2(1738, 470),
Vec2(1738, 920),
// ��Ӹ���·����...
    };
    //��һ���а�ֻ����
    if (round == 1) {
        ++round1_;
        //��һ�ֹ���
        if (round1_ % 3 == 0) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster0.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round1_ % 3 == 1) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster1.png", 100, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round1_ % 3 == 2) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster2.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }

        if (round1_ == 10)
        {
            round = 2;
            auto schedulerCallback = [=](float dt) {
                createAndMoveMonster2(dt);

                // �ӳ� 7 ���ִ����һ�ε���
                this->schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster2), 4.0f);
                };

            // �ӳ� 7 ���ִ�е�һ�ε���
            this->scheduleOnce(schedulerCallback, 40.0f,"  ");
        }
    }
}
void SecondScene::createAndMoveMonster2(float dt)
{
    std::vector<Vec2> path = {
Vec2(230, 470),
Vec2(715, 470),
Vec2(715, 620),
Vec2(1230, 620),
Vec2(1230, 470),
Vec2(1738, 470),
Vec2(1738, 920),
// ��Ӹ���·����...
    };
    //��һ���а�ֻ����
    if (round == 2) {
        ++round2_;
        //��һ�ֹ���
        if (round2_ % 3 == 0) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster0.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round2_ % 3 == 1) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster1.png", 100, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round2_ % 3 == 2) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster2.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }

        if (round2_ == 16)
        {
            round = 3;
            auto schedulerCallback = [=](float dt) {
                createAndMoveMonster2(dt);

                // �ӳ� 7 ���ִ����һ�ε���
                this->schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster3), 4.0f);
                };

            // �ӳ� 7 ���ִ�е�һ�ε���
            this->scheduleOnce(schedulerCallback, 20.0f, "  ");

        }
    }


}
void SecondScene::createAndMoveMonster3(float dt)
{
    std::vector<Vec2> path = {
Vec2(230, 470),
Vec2(715, 470),
Vec2(715, 620),
Vec2(1230, 620),
Vec2(1230, 470),
Vec2(1738, 470),
Vec2(1738, 920),
// ��Ӹ���·����...
    };
    //��һ���а�ֻ����
    if (round == 3) {
        ++round3_;
        //��һ�ֹ���
        if (round3_ % 3 == 0) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster0.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round3_ % 3 == 1) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster1.png", 100, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round3_ % 3 == 2) {
            //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
            Monster* monster = Monster::create(50.0f, 100, "monster2.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }

        if (round3_ == 20)
        {
            round = 4;
        }
    }


}