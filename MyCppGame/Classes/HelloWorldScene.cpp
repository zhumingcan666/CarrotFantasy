#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
/*********************************************************************创建主菜单************************************************************/
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 在文件不存在时打印有用的错误消息而不是导致段错误.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//在 'init' 方法中，你需要初始化你的实例
/*********************************************************************初始化主菜单************************************************************/
bool HelloWorld::init()
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


    // 添加一个 "开始" 图标来开始。这是一个自动释放的对象
    auto startItem = MenuItemImage::create(
        "Startgame.png",
        "Startgame(1).png",
        CC_CALLBACK_1(HelloWorld::StartGame, this));

    // 检查图标是否加载成功，若未加载成功，则输出问题信息
    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' 和 'CloseSelected.png'");
    }
    else
    {
        // 设置关闭图标的位置
        float x = origin.x + 1150 - startItem->getContentSize().width / 2;
        float y = origin.y + 170 + startItem->getContentSize().height / 2;
        startItem->setPosition(Vec2(x, y));
    }

    // 创建菜单，这是一个自动释放的对象
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. 在下面添加你的代码...

 //// 添加一个显示 "Hello World" 的标签
 //// 创建并初始化一个标签
 //   auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
 //   if (label == nullptr)
 //   {
 //       problemLoading("'fonts/Marker Felt.ttf'");
 //   }
 //   else
 //   {
 //       // 将标签定位在屏幕中央
 //       label->setPosition(Vec2(origin.x + visibleSize.width / 2,
 //           origin.y + visibleSize.height - label->getContentSize().height));

 //       // 将标签添加为此层的子节点
 //       this->addChild(label, 1);
 //   }

    // 添加 "HelloWorld" 的启动画面
    auto sprite = Sprite::create("menu(2).png");
    if (sprite == nullptr)
    {
        problemLoading("'menu(2).png'");
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
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("menumusic.mp3");

    // 播放音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("menumusic.mp3", true);



    /******************************************************************创建一个音乐控制按钮****************************************************/
    auto musicItem = MenuItemImage::create(
        "share_fan_active.png",
        "share_fan_disable.png",
        CC_CALLBACK_1(HelloWorld::MusicControl, this));

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
            origin.y +1250));

        // 将标签添加为此层的子节点
        this->addChild(label, 1);
    }
    return true;
}
/*********************************************************************开始按钮的回调函数************************************************************/

void HelloWorld::StartGame(Ref* pSender)
{
    // 切换主菜单场景至第一个地图场景
    auto secondScene = SecondScene::create();
    Director::getInstance()->replaceScene(secondScene);

    /* 若要在不退出应用程序的情况下返回到原生 iOS 屏幕（如果存在），请不要使用上述的 Director::getInstance()->end()，
    而是触发 RootViewController.mm 中创建的自定义事件，如下所示 */

    // EventCustom customEndEvent("game_scene_close_event");
    // _eventDispatcher->dispatchEvent(&customEndEvent);
}
/*****************************************************************菜单背景音乐控制按钮的回调函数************************************************************/
void HelloWorld::MusicControl(Ref* sender)
{
    // 切换音乐的播放状态
    if (Musiccontrol %2==0)
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

