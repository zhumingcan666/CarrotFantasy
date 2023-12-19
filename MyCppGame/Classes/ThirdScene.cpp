#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"ThirdScene.h"
#include "ui/CocosGUI.h"
#include"carrot.h"
#include"Monster.h"
#include <cstdlib>  // 包含随机数函数的头文件
#include <ctime>    // 包含时间函数的头文件

USING_NS_CC;
/*********************************************************************创建第二个地图场景**********************************************************/
Scene* ThirdScene::createScene()
{
    return ThirdScene::create();
}

// 在文件不存在时打印有用的错误消息而不是导致段错误.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
/*********************************************************************初始化第二个地图场景**********************************************************/
bool ThirdScene::init()
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

    // 添加 "ThirdScene" 的启动画面
    auto sprite = Sprite::create("bg1.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg1.png'");
    }
    else
    {
        // 将场景图片定位在屏幕中央
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 将场景图片添加为此层的子节点
        this->addChild(sprite, 0);
    }
    auto road = Sprite::create("road2.png");
    if (road == nullptr)
    {
        problemLoading("'road2.png'");
    }
    else
    {
        // 将场景图片定位在屏幕中央
        road->setPosition(Vec2(visibleSize.width / 2 + origin.x, 500));

        // 将场景图片添加为此层的子节点
        this->addChild(road, 0);
    }
    auto menubg = Sprite::create("menubg(1).png");
    if (menubg == nullptr)
    {
        problemLoading("'menubg(1).png'");
    }
    else
    {
        // 将场景图片定位在屏幕中央
        menubg->setPosition(Vec2(visibleSize.width / 2 + origin.x - 70, 1250));

        // 将场景图片添加为此层的子节点
        this->addChild(menubg, 0);
    }
    /*********************************************************************创建一个返回主菜单按钮（homeItem)**********************************************************/
    auto homeItem = MenuItemImage::create(
        "back.png",
        "back_pressed.png",
        CC_CALLBACK_1(ThirdScene::menuBackHome, this));

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
    /************************************************************************创建怪物精灵***********************************************************************/
    // 每隔3秒调用一次createAndMoveMonster函数
    schedule(CC_SCHEDULE_SELECTOR(ThirdScene::createAndMoveMonster0), 1.0f, 7, 0);

    /*********************************************************************创建第一个地图的音乐**********************************************************/
    // 预加载音乐文件
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // 播放音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);

    /******************************************************************创建一个音乐控制按钮****************************************************/
    auto musicItem = MenuItemImage::create(
        "share_fan_active.png",
        "share_fan_disable.png",
        CC_CALLBACK_1(ThirdScene::MusicControl, this));

    // 检查图标是否加载成功，若未加载成功，则输出问题信息
    if (musicItem == nullptr ||
        musicItem->getContentSize().width <= 0 ||
        musicItem->getContentSize().height <= 0)
    {
        problemLoading("'share_fan_active.png' 和 'share_fan_disable.png'");
    }
    else
    {
        // 设置图标的位置
        float x = origin.x + 1930;
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
        label->setPosition(Vec2(origin.x + 1860,
            origin.y + 1250));

        // 将标签添加为此层的子节点
        this->addChild(label, 1);
    }
    /******************************************************************创建萝卜****************************************************/
    auto carrot = Carrot::createSprite(760, 1012);
    addChild(carrot);
    return true;
}
/************************************************************************返回主菜单按钮的回调函数**********************************************************/
void ThirdScene::menuBackHome(Ref* pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
}
/***********************************************************************控制背景音乐的回调函数***************************************************************/
void ThirdScene::MusicControl(Ref* sender)
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
// 创建并移动怪物的函数
void ThirdScene::createAndMoveMonster0(float dt)
{
    std::vector<Vec2> path= {
        Vec2(116*4, 102 * 4),
        Vec2(116 * 4, 178*4),
        Vec2(385*4, 178 * 4),
        Vec2(385 * 4, 253*4),
        Vec2(194*4, 253*4),
        // 添加更多路径点...
    };
    Monster* monster = Monster::create(5000.0f, 100, "monster1.png", 20, 50, path);
    monster->setPosition(Vec2(314*4, 102*4));
    addChild(monster);
}
