#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "BossScene.h"

USING_NS_CC;
/*********************************************************************创建主菜单************************************************************/
Scene* BossScene::createScene()
{
    return BossScene::create();
}

// 在文件不存在时打印有用的错误消息而不是导致段错误.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BossScene.cpp\n");
}

//在 'init' 方法中，你需要初始化你的实例
/*********************************************************************初始化主菜单************************************************************/
bool BossScene::init()
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


  

    // 添加 "BossScene" 的画面
    auto sprite = Sprite::create("bg1.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg1.png'");
    }
    else
    {
        // 将主菜单定位在屏幕中央
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 将主菜单添加为此层的子节点
        this->addChild(sprite, 0);
    }
    /*********************************************************************创建主菜单音乐***********************************************************/
    // 预加载音乐文件
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // 播放音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);



    /******************************************************************创建一个音乐控制按钮****************************************************/
    auto musicItem = MenuItemImage::create(
        "share_fan_active.png",
        "share_fan_disable.png",
        CC_CALLBACK_1(BossScene::MusicControl, this));

    // 检查图标是否加载成功，若未加载成功，则输出问题信息
    if (musicItem == nullptr ||
        musicItem->getContentSize().width <= 0 ||
        musicItem->getContentSize().height <= 0)
    {
        problemLoading("'share_fan_active.png' 和 'share_fan_disable.png'");
    }
    else
    {
        // 设置关闭图标的位置
        float x = origin.x + 1900;
        float y = origin.y + 1250;
        musicItem->setPosition(Vec2(x, y));
    }
    // 创建菜单，这是一个自动释放的对象
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
        // 将标签定位在屏幕中央
        label->setPosition(Vec2(origin.x + 1810,
            origin.y + 1250));

        // 将标签添加为此层的子节点
        this->addChild(label, 1);
    }
    /*********************************************************************创建一个返回主菜单按钮（homeItem)**********************************************************/
    auto homeItem = MenuItemImage::create(
        "back.png",
        "back_pressed.png",
        CC_CALLBACK_1(BossScene::menuBackHome, this));

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
        float x = 30;
        float y = 1250;
        homeItem->setPosition(Vec2(x, y));

    }

    // 创建菜单，这是一个自动释放的对象
    auto menu = Menu::create(homeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    return true;
}
/*****************************************************************菜单背景音乐控制按钮的回调函数************************************************************/
void BossScene::MusicControl(Ref* sender)
{
    // 切换音乐的播放状态
    if (Musiccontrol % 2 == 0)
    {
        // 暂停音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        Musiccontrol++;
    }
    else
    {
        // 恢复音乐播放
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        Musiccontrol++;
    }
}
/************************************************************************返回主菜单按钮的回调函数**********************************************************/
void BossScene::menuBackHome(Ref* pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
}
