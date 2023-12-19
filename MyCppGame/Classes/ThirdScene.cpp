#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"ThirdScene.h"
#include "ui/CocosGUI.h"
#include"carrot.h"
#include"Monster.h"
#include <cstdlib>  // ���������������ͷ�ļ�
#include <ctime>    // ����ʱ�亯����ͷ�ļ�

USING_NS_CC;
/*********************************************************************�����ڶ�����ͼ����**********************************************************/
Scene* ThirdScene::createScene()
{
    return ThirdScene::create();
}

// ���ļ�������ʱ��ӡ���õĴ�����Ϣ�����ǵ��¶δ���.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
/*********************************************************************��ʼ���ڶ�����ͼ����**********************************************************/
bool ThirdScene::init()
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

    // ��� "ThirdScene" ����������
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
    auto road = Sprite::create("road2.png");
    if (road == nullptr)
    {
        problemLoading("'road2.png'");
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
    auto homeItem = MenuItemImage::create(
        "back.png",
        "back_pressed.png",
        CC_CALLBACK_1(ThirdScene::menuBackHome, this));

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
    /************************************************************************�������ﾫ��***********************************************************************/
    // ÿ��3�����һ��createAndMoveMonster����
    schedule(CC_SCHEDULE_SELECTOR(ThirdScene::createAndMoveMonster0), 1.0f, 7, 0);

    /*********************************************************************������һ����ͼ������**********************************************************/
    // Ԥ���������ļ�
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);

    /******************************************************************����һ�����ֿ��ư�ť****************************************************/
    auto musicItem = MenuItemImage::create(
        "share_fan_active.png",
        "share_fan_disable.png",
        CC_CALLBACK_1(ThirdScene::MusicControl, this));

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
    /******************************************************************�����ܲ�****************************************************/
    auto carrot = Carrot::createSprite(760, 1012);
    addChild(carrot);
    return true;
}
/************************************************************************�������˵���ť�Ļص�����**********************************************************/
void ThirdScene::menuBackHome(Ref* pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
}
/***********************************************************************���Ʊ������ֵĻص�����***************************************************************/
void ThirdScene::MusicControl(Ref* sender)
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
// �������ƶ�����ĺ���
void ThirdScene::createAndMoveMonster0(float dt)
{
    std::vector<Vec2> path= {
        Vec2(116*4, 102 * 4),
        Vec2(116 * 4, 178*4),
        Vec2(385*4, 178 * 4),
        Vec2(385 * 4, 253*4),
        Vec2(194*4, 253*4),
        // ��Ӹ���·����...
    };
    Monster* monster = Monster::create(5000.0f, 100, "monster1.png", 20, 50, path);
    monster->setPosition(Vec2(314*4, 102*4));
    addChild(monster);
}
