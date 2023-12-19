#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include"carrot.h"
#include<vector>
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
        road->setPosition(Vec2(visibleSize.width / 2 + origin.x,500));

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
        menubg->setPosition(Vec2(visibleSize.width / 2 + origin.x-70, 1250));

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
    /******************************************************************�����ܲ�****************************************************/
    auto carrot = Carrot::createSprite(1775,995);
    addChild(carrot);
    
    /************************************************************************�������ﾫ��***********************************************************************/
     std::vector<Vec2> path = {
    Vec2(230, 470),
    Vec2(715, 470),
    Vec2(715, 620),
    Vec2(1230, 620),
    Vec2(1230, 470),
    Vec2(1738, 470),
    Vec2(1738, 970),
    // ��Ӹ���·����...
     };

        Monster* monster = Monster::create(50.0f, 100, "monster0.png", 20, 50,path);
        monster->setPosition(Vec2(230, 970));
        addChild(monster);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
