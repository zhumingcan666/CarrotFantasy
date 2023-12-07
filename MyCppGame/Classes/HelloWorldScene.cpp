#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
/*********************************************************************�������˵�************************************************************/
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// ���ļ�������ʱ��ӡ���õĴ�����Ϣ�����ǵ��¶δ���.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//�� 'init' �����У�����Ҫ��ʼ�����ʵ��
/*********************************************************************��ʼ�����˵�************************************************************/
bool HelloWorld::init()
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


    // ���һ�� "��ʼ" ͼ������ʼ������һ���Զ��ͷŵĶ���
    auto startItem = MenuItemImage::create(
        "Startgame.png",
        "Startgame(1).png",
        CC_CALLBACK_1(HelloWorld::StartGame, this));

    // ���ͼ���Ƿ���سɹ�����δ���سɹ��������������Ϣ
    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' �� 'CloseSelected.png'");
    }
    else
    {
        // ���ùر�ͼ���λ��
        float x = origin.x + 1150 - startItem->getContentSize().width / 2;
        float y = origin.y + 170 + startItem->getContentSize().height / 2;
        startItem->setPosition(Vec2(x, y));
    }

    // �����˵�������һ���Զ��ͷŵĶ���
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. �����������Ĵ���...

 //// ���һ����ʾ "Hello World" �ı�ǩ
 //// ��������ʼ��һ����ǩ
 //   auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
 //   if (label == nullptr)
 //   {
 //       problemLoading("'fonts/Marker Felt.ttf'");
 //   }
 //   else
 //   {
 //       // ����ǩ��λ����Ļ����
 //       label->setPosition(Vec2(origin.x + visibleSize.width / 2,
 //           origin.y + visibleSize.height - label->getContentSize().height));

 //       // ����ǩ���Ϊ�˲���ӽڵ�
 //       this->addChild(label, 1);
 //   }

    // ��� "HelloWorld" ����������
    auto sprite = Sprite::create("menu(2).png");
    if (sprite == nullptr)
    {
        problemLoading("'menu(2).png'");
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
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("menumusic.mp3");

    // ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("menumusic.mp3", true);



    /******************************************************************����һ�����ֿ��ư�ť****************************************************/
    auto musicItem = MenuItemImage::create(
        "share_fan_active.png",
        "share_fan_disable.png",
        CC_CALLBACK_1(HelloWorld::MusicControl, this));

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
            origin.y +1250));

        // ����ǩ���Ϊ�˲���ӽڵ�
        this->addChild(label, 1);
    }
    return true;
}
/*********************************************************************��ʼ��ť�Ļص�����************************************************************/

void HelloWorld::StartGame(Ref* pSender)
{
    // �л����˵���������һ����ͼ����
    auto secondScene = SecondScene::create();
    Director::getInstance()->replaceScene(secondScene);

    /* ��Ҫ�ڲ��˳�Ӧ�ó��������·��ص�ԭ�� iOS ��Ļ��������ڣ����벻Ҫʹ�������� Director::getInstance()->end()��
    ���Ǵ��� RootViewController.mm �д������Զ����¼���������ʾ */

    // EventCustom customEndEvent("game_scene_close_event");
    // _eventDispatcher->dispatchEvent(&customEndEvent);
}
/*****************************************************************�˵��������ֿ��ư�ť�Ļص�����************************************************************/
void HelloWorld::MusicControl(Ref* sender)
{
    // �л����ֵĲ���״̬
    if (Musiccontrol %2==0)
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

