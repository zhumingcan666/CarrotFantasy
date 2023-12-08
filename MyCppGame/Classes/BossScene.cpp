#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "BossScene.h"

USING_NS_CC;
/*********************************************************************�������˵�************************************************************/
Scene* BossScene::createScene()
{
    return BossScene::create();
}

// ���ļ�������ʱ��ӡ���õĴ�����Ϣ�����ǵ��¶δ���.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BossScene.cpp\n");
}

//�� 'init' �����У�����Ҫ��ʼ�����ʵ��
/*********************************************************************��ʼ�����˵�************************************************************/
bool BossScene::init()
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


  

    // ��� "BossScene" �Ļ���
    auto sprite = Sprite::create("bg1.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg1.png'");
    }
    else
    {
        // �����˵���λ����Ļ����
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // �����˵����Ϊ�˲���ӽڵ�
        this->addChild(sprite, 0);
    }
    /*********************************************************************�������˵�����***********************************************************/
    // Ԥ���������ļ�
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);



    /******************************************************************����һ�����ֿ��ư�ť****************************************************/
    auto musicItem = MenuItemImage::create(
        "share_fan_active.png",
        "share_fan_disable.png",
        CC_CALLBACK_1(BossScene::MusicControl, this));

    // ���ͼ���Ƿ���سɹ�����δ���سɹ��������������Ϣ
    if (musicItem == nullptr ||
        musicItem->getContentSize().width <= 0 ||
        musicItem->getContentSize().height <= 0)
    {
        problemLoading("'share_fan_active.png' �� 'share_fan_disable.png'");
    }
    else
    {
        // ���ùر�ͼ���λ��
        float x = origin.x + 1900;
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
        label->setPosition(Vec2(origin.x + 1810,
            origin.y + 1250));

        // ����ǩ���Ϊ�˲���ӽڵ�
        this->addChild(label, 1);
    }
    /*********************************************************************����һ���������˵���ť��homeItem)**********************************************************/
    auto homeItem = MenuItemImage::create(
        "back.png",
        "back_pressed.png",
        CC_CALLBACK_1(BossScene::menuBackHome, this));

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
    return true;
}
/*****************************************************************�˵��������ֿ��ư�ť�Ļص�����************************************************************/
void BossScene::MusicControl(Ref* sender)
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
/************************************************************************�������˵���ť�Ļص�����**********************************************************/
void BossScene::menuBackHome(Ref* pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
}
