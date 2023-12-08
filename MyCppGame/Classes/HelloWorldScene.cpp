#include "HelloWorldScene.h"
#include"LevelSelectScene.h"
#include"BossScene.h"
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


    // ���һ�� "ð��ģʽ" ͼ������ʼ������һ���Զ��ͷŵĶ���
    auto startItem = MenuItemImage::create(
        "adventure.png",
        "adventure_pressed.png",
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
        float x = origin.x + 1130 - startItem->getContentSize().width / 2;
        float y = origin.y + 700 + startItem->getContentSize().height / 2;
        startItem->setPosition(Vec2(x, y));
    }

    // �����˵�������һ���Զ��ͷŵĶ���
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    // ���һ�� "Bossģʽ" ͼ������ʼ������һ���Զ��ͷŵĶ���
    auto bossItem = MenuItemImage::create(
        "boss.png",
        "boss_pressed.png",
        CC_CALLBACK_1(HelloWorld::Bosspatern, this));

    // ���ͼ���Ƿ���سɹ�����δ���سɹ��������������Ϣ
    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("'boss.png' �� 'boss_pressed.png'");
    }
    else
    {
        // ���ùر�ͼ���λ��
        float x = -5;
        float y = -30;
        bossItem->setPosition(Vec2(x, y));
    }

    // �����˵�������һ���Զ��ͷŵĶ���
    auto menu1 = Menu::create(bossItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu1, 3);

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
/*****************************************************************���ò˵�����********************************************************************/

  // ����һ�����飬��������¸����Ķ���
    Sprite* animatedSprite0 = Sprite::create("monster1.png");
    animatedSprite0->setPosition(Vec2(320, 880));
    this->addChild(animatedSprite0);

    auto moveUp = MoveBy::create(1.0f, Vec2(0, 20));   // �����ƶ�30������
    auto moveDown = MoveBy::create(1.0f, Vec2(0, -20)); // �����ƶ�30������
    auto sequenceMove = Sequence::create(moveUp, moveDown, nullptr);
    auto repeatForeverMove = RepeatForever::create(sequenceMove);
    animatedSprite0->runAction(repeatForeverMove);

    // ������һ�����飬����ӱ���С�Ķ���
    Sprite* animatedSprite1 = Sprite::create("monster2.png");
    animatedSprite1->setPosition(Vec2(1720, 280));
    this->addChild(animatedSprite1);

    auto scaleUp = ScaleTo::create(1.0f, 1.01f);   // ���ŵ�ԭʼ��С��1.1��
    auto scaleDown = ScaleTo::create(1.0f, 0.991f); // ���ŵ�ԭʼ��С��0.9��
    auto sequenceScale = Sequence::create(scaleUp, scaleDown, nullptr);
    auto repeatForeverScale = RepeatForever::create(sequenceScale);
    animatedSprite1->runAction(repeatForeverScale);



    return true;
}
/*********************************************************************��ʼ��ť�Ļص�����************************************************************/

void HelloWorld::StartGame(Ref* pSender)
{
    // �л����˵���������һ����ͼ����
    auto levelSelectScene = LevelSelectScene::create();
    Director::getInstance()->replaceScene(levelSelectScene);

    /* ��Ҫ�ڲ��˳�Ӧ�ó��������·��ص�ԭ�� iOS ��Ļ��������ڣ����벻Ҫʹ�������� Director::getInstance()->end()��
    ���Ǵ��� RootViewController.mm �д������Զ����¼���������ʾ */

    // EventCustom customEndEvent("game_scene_close_event");
    // _eventDispatcher->dispatchEvent(&customEndEvent);
}
    /*********************************************************************Bossģʽ��ť�Ļص�����************************************************************/

    void HelloWorld::Bosspatern(Ref * pSender)
    {
        // �л����˵���������һ����ͼ����
        auto bossScene = BossScene::create();
        Director::getInstance()->replaceScene(bossScene);
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

