#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
/*********************************************************************创建第一个地图场景**********************************************************/
Scene* SecondScene::createScene()
{
    return SecondScene::create();
}

// 在文件不存在时打印有用的错误消息而不是导致段错误.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
/*********************************************************************初始化第一个地图场景**********************************************************/
bool SecondScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        // 初始化失败
        return false;
    }

    // 获取屏幕可见尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 获取屏幕原点坐标
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加 "SecondScene" 的启动画面
    auto sprite = Sprite::create("map.png");
    if (sprite == nullptr)
    {
        problemLoading("'map.png'");
    }
    else
    {
        // 将场景图片定位在屏幕中央
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 将场景图片添加为此层的子节点
        this->addChild(sprite, 0);
    }
    /*********************************************************************创建一个返回主菜单按钮（homeItem)**********************************************************/
    auto homeItem = MenuItemImage::create(
        "return.png",
        "return(1).png",
        CC_CALLBACK_1(SecondScene::menuBackHome, this));

    // 检查图标是否加载成功，若未加载成功，则输出问题信息
    if (homeItem == nullptr ||
        homeItem->getContentSize().width <= 0 ||
        homeItem->getContentSize().height <= 0)
    {
        problemLoading("'return.png' 和 'return.png'");
    }
    else
    {
        // 设置返回按钮的位置为左上角
        float x = origin.x - 50 + homeItem->getContentSize().width / 2;
        float y = visibleSize.height + 80 - (origin.y + 10 + homeItem->getContentSize().height / 2);
        homeItem->setPosition(Vec2(x, y));

    }

    // 创建菜单，这是一个自动释放的对象
    auto menu = Menu::create(homeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /*********************************************************************创建第一个地图的音乐**********************************************************/
    // 预加载音乐文件
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // 播放音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);
    return true;
}
/************************************************************************返回主菜单按钮的功能函数**********************************************************/
void SecondScene::menuBackHome(Ref* pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
}
