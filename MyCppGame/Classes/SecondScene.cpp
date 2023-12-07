#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

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

    // ���� "SecondScene" ����������
    auto sprite = Sprite::create("map.png");
    if (sprite == nullptr)
    {
        problemLoading("'map.png'");
    }
    else
    {
        // ������ͼƬ��λ����Ļ����
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // ������ͼƬ����Ϊ�˲���ӽڵ�
        this->addChild(sprite, 0);
    }
    /*********************************************************************����һ���������˵���ť��homeItem)**********************************************************/
    auto homeItem = MenuItemImage::create(
        "return.png",
        "return(1).png",
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
        float x = origin.x - 50 + homeItem->getContentSize().width / 2;
        float y = visibleSize.height + 80 - (origin.y + 10 + homeItem->getContentSize().height / 2);
        homeItem->setPosition(Vec2(x, y));

    }

    // �����˵�������һ���Զ��ͷŵĶ���
    auto menu = Menu::create(homeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /************************************************************************�������ﾫ��***********************************************************************/
    // ÿ��3�����һ��createAndMoveMonster����
    schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster), 3.0f, kRepeatForever, 0);

    /*********************************************************************������һ����ͼ������**********************************************************/
    // Ԥ���������ļ�
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);

    /******************************************************************����һ�����ֿ��ư�ť****************************************************/
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

        // ����ǩ����Ϊ�˲���ӽڵ�
        this->addChild(label, 1);
    }
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
// �������ƶ�����ĺ���
void SecondScene::createAndMoveMonster(float dt)
{
    // ����һ���µĹ��ﾫ��
    Sprite* monster = Sprite::create("monster0.png");
    monster->setPosition(Vec2(250, 950));
    this->addChild(monster, 0);

    // ����·��
    Vec2 path[] = {
        Vec2(603, 950),
        Vec2(603, 390),
        Vec2(1340, 390),
        Vec2(1340, 970),
        Vec2(1575, 970),
        // ���Ӹ���·����...
    };

    // ����MoveTo����
    auto moveToAction1 = MoveTo::create(5, path[0]);
    auto moveToAction2 = MoveTo::create(5, path[1]);
    auto moveToAction3 = MoveTo::create(5, path[2]);
    auto moveToAction4 = MoveTo::create(5, path[3]);
    auto moveToAction5 = MoveTo::create(5, path[4]);

    // ����һ�����ж���
    auto sequence = Sequence::create(
        moveToAction1,
        moveToAction2,
        moveToAction3,
        moveToAction4,
        moveToAction5,
        nullptr
    );

    // ���µĹ��ﾫ�������ж���
    monster->runAction(sequence);
}