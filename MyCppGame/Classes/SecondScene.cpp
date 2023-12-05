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

    // ��� "SecondScene" ����������
    auto sprite = Sprite::create("map.png");
    if (sprite == nullptr)
    {
        problemLoading("'map.png'");
    }
    else
    {
        // ������ͼƬ��λ����Ļ����
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // ������ͼƬ���Ϊ�˲���ӽڵ�
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
    /*********************************************************************������һ����ͼ������**********************************************************/
    // Ԥ���������ļ�
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);
    return true;
}
/************************************************************************�������˵���ť�Ĺ��ܺ���**********************************************************/
void SecondScene::menuBackHome(Ref* pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
}
