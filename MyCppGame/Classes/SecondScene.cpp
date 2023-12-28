#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include"carrot.h"
#include"Bullet.h"
#include<vector>
#include"Coin.h"
#include"Monster.h"
#include <cstdlib>  // ���������������ͷ�ļ�
#include <ctime>    // ����ʱ�亯����ͷ�ļ�
#include"Barrier.h"

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
    if (road == nullptr)
    {
        problemLoading("'road1.png'");
    }
    else
    {
        // ������ͼƬ��λ����Ļ����
        road->setPosition(Vec2(visibleSize.width / 2 + origin.x, 500));

        // ������ͼƬ���Ϊ�˲���ӽڵ�
        this->addChild(road, 0);
    }
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
        auto homeItem = MenuItemImage::create(
            "back.png",
            "back_pressed.png",
            CC_CALLBACK_1(SecondScene::menuBackHome, this));

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
        auto menu = Menu::create(homeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);

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
    /******************************************************************�����ܲ�****************************************************/
    auto carrot = Carrot::createSprite(1775, 995);
    carrot->setTag(1);
    addChild(carrot);

    /************************************************************************�������ﾫ��***********************************************************************/
    schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster0), 4.0f, 7, 0);

    /************************************************************************�����ϰ���***********************************************************************/
  scheduleOnce(CC_SCHEDULE_SELECTOR(SecondScene::createBarriers), 0.0f);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*********************************************************************�������ϵͳ**********************************************************/
    auto coin = Coin::create();
    coin->setTag(1001); // ���ö��صı�ǩ
    addChild(coin);

    return true;

}
/************************************************************************�������˵���ť�Ļص�����**********************************************************/
void SecondScene::menuBackHome(Ref* pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
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
void SecondScene::createAndMoveMonster0(float dt)
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

    //���ڴ��ݲ�����                     �Ⱥ�Ϊ���ٶȡ� ����ֵ�� ��ͼ��        �˺�����ֵ��·��
    Monster* monster = Monster::create(300.0f, 100, "monster0.png", 20, 100, path);
    monster->setPosition(Vec2(230, 970));
    addChild(monster);
}
void SecondScene::createBarriers(float dt)
{

  std::vector<Vec2> path = {
Vec2(117*4, 172*4),
Vec2(152*4,172 * 4),
Vec2(120*4, 234*4),
Vec2(200*4, 215*4),
Vec2(242*4, 90*4),
Vec2(261*4, 210*4),
Vec2(1738, 970),
// ��Ӹ���·����...
    };

      Barrier* barrier1 = Barrier::create("Barrier1.png", 100, 100);
      barrier1->setPosition(path[0]);
      addChild(barrier1);

      Barrier* barrier2 = Barrier::create("Barrier1.png", 100, 100);
      barrier2->setPosition(path[1]);
      addChild(barrier2);


      Barrier* barrier3 = Barrier::create("Barrier2.png", 100, 100);
      barrier3->setPosition(path[2]);
      addChild(barrier3);

      Barrier* barrier4 = Barrier::create("Barrier3.png", 100, 100);
      barrier4->setPosition(path[3]);
      addChild(barrier4);

      Barrier* barrier5 = Barrier::create("Barrier4.png", 100, 100);
      barrier5->setPosition(path[4]);
      addChild(barrier5);

      Barrier* barrier6 = Barrier::create("Barrier3.png", 100, 100);
      barrier6->setPosition(path[5]);
      addChild(barrier6);

      levelSelect::thirdScene = 1;
      saveGameProgress(levelSelect::thirdScene);
}