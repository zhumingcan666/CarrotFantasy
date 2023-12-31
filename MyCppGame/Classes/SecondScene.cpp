#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include"SecondScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include"carrot.h"
#include"Bullet.h"
#include"Tower.h"
#include"Tower2.h"
#include<vector>
#include"LevelSelectScene.h"
#include"Coin.h"
#include"Monster.h"
#include <cstdlib>  // 包含随机数函数的头文件
#include <ctime>    // 包含时间函数的头文件

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


    //////////////////////////////////////////////////该if(1)中是各种按钮的实现
    if(1){
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
       auto road = Sprite::create("road1.png");
        road->setPosition(Vec2(visibleSize.width / 2 + origin.x, 500));
        // 将场景图片添加为此层的子节点
        this->addChild(road, 0);
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
    if (1) {
        //回到选择页面
        auto homeItem = MenuItemImage::create(
            "back.png",
            "back_pressed.png",
            CC_CALLBACK_1(SecondScene::menuBack, this));

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
        //回到主页面
        auto menu = Menu::create(homeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);

        auto backhome = MenuItemImage::create(
            "return1.png",
            "return.png",
            CC_CALLBACK_1(SecondScene::menuBackHome, this));
        backhome->setPosition(1700, 1250);
        auto menu1 = Menu::create(backhome, NULL);
        menu1->setPosition(Vec2::ZERO);
        this->addChild(menu1, 3);

    }
    /*********************************************************************创建第一个地图的音乐**********************************************************/
    // 预加载音乐文件
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backmusic.mp3");

    // 播放音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3", true);

    /******************************************************************创建一个音乐控制按钮****************************************************/
    if (1) {
        auto musicItem = MenuItemImage::create(
            "share_fan_active.png",
            "share_fan_disable.png",
            CC_CALLBACK_1(SecondScene::MusicControl, this));

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

    }


   }
   //////////////////////////////////////////////////以上为按钮实现


    /******************************************************************加速****************************************************/

   auto speed = MenuItemImage::create(
       "speedup.png",
       "speedup1.png",
       CC_CALLBACK_1(SecondScene::speedUp, this));
   speed->setPosition(1500, 1250);
   auto menus = Menu::create(speed, NULL);
   menus->setPosition(Vec2::ZERO);
   this->addChild(menus, 3);
   /******************************************************************暂停****************************************************/

   auto stop = MenuItemImage::create(
       "stop.png",
       "stop1.png",
       CC_CALLBACK_1(SecondScene::stopORstart, this));
   stop->setPosition(1400, 1250);
   auto menust = Menu::create(stop, NULL);
   menust->setPosition(Vec2::ZERO);
   this->addChild(menust, 3);


   /******************************************************************炮塔实现****************************************************/
   Tower* tower = Tower::createTower("Bottle11.png");
   tower->setTag(10);
   this->addChild(tower);
   Tower2* fan = Tower2::createTower("Fan11.png");
   this->addChild(fan);

    /******************************************************************开场倒计时****************************************************/

   schedule(CC_SCHEDULE_SELECTOR(SecondScene::countDown), 0.8f, 2, 0);


    /******************************************************************创建萝卜****************************************************/
    auto carrot = Carrot::createSprite(1775, 995);
    addChild(carrot);

    /************************************************************************创建怪物精灵***********************************************************************/

    schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster1), 3.50f);

    /************************************************************************判断胜利***********************************************************************/
    this->schedule(CC_SCHEDULE_SELECTOR(SecondScene::checkWin));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*********************************************************************创建金币系统**********************************************************/
    auto coin = Coin::create();
    coin->setTag(1001); // 设置独特的标签
    addChild(coin);
    return true;

}
/************************************************************************返回主菜单按钮的回调函数**********************************************************/
void SecondScene::menuBack(Ref* pSender)
{
    auto levelSelectScene = LevelSelectScene::create();
    Director::getInstance()->replaceScene(levelSelectScene);
}
void SecondScene::menuBackHome(Ref* pSender)
{
    auto home = HelloWorld::create();
    Director::getInstance()->replaceScene(home);
}

/***********************************************************************控制背景音乐的回调函数***************************************************************/
void SecondScene::MusicControl(Ref* sender)
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
void SecondScene::countDown(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 获取屏幕原点坐标
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto levelCard3 = Sprite::create(StringUtils::format("countdown%d.png", countdown));
        levelCard3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        addChild(levelCard3, 3);
     --countdown; 
     // 创建延迟动作，1秒后执行删除动作
     auto delayAction = DelayTime::create(0.85f);
     auto removeAction = RemoveSelf::create();
     auto sequenceAction = Sequence::create(delayAction, removeAction, nullptr);
     levelCard3->runAction(sequenceAction);
}
void  SecondScene::speedUp(Ref* pSender)
{
    ++speedCount;
    stopCount = 3;
    if(speedCount%2==0)
        Director::getInstance()->getScheduler()->setTimeScale(2.0f);
    else
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
}
void SecondScene::stopORstart(Ref* sender)
{
      ++stopCount;
      if (stopCount % 2 == 0)
      {
          Director::getInstance()->getScheduler()->setTimeScale(0.0f);
          speedCount = 2;

      }
    else {
        speedCount = 3;
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);

    }
}
void SecondScene::createAndMoveMonster1(float dt)
{
    std::vector<Vec2> path = {
Vec2(230, 470),
Vec2(715, 470),
Vec2(715, 620),
Vec2(1230, 620),
Vec2(1230, 470),
Vec2(1738, 470),
Vec2(1738, 920),
// 添加更多路径点...
    };
    //第一波有八只怪物
    if (round == 1) {
        ++round1_;
        //第一种怪物
        if (round1_ % 3 == 0) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster0.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round1_ % 3 == 1) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster1.png", 100, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round1_ % 3 == 2) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster2.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }

        if (round1_ == 10)
        {
            round = 2;
            auto schedulerCallback = [=](float dt) {
                createAndMoveMonster2(dt);

                // 延迟 7 秒后执行下一次调度
                this->schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster2), 4.0f);
                };

            // 延迟 7 秒后执行第一次调度
            this->scheduleOnce(schedulerCallback, 40.0f,"  ");
        }
    }
}
void SecondScene::createAndMoveMonster2(float dt)
{
    std::vector<Vec2> path = {
Vec2(230, 470),
Vec2(715, 470),
Vec2(715, 620),
Vec2(1230, 620),
Vec2(1230, 470),
Vec2(1738, 470),
Vec2(1738, 920),
// 添加更多路径点...
    };
    //第一波有八只怪物
    if (round == 2) {
        ++round2_;
        //第一种怪物
        if (round2_ % 3 == 0) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster0.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round2_ % 3 == 1) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster1.png", 100, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round2_ % 3 == 2) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster2.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }

        if (round2_ == 16)
        {
            round = 3;
            auto schedulerCallback = [=](float dt) {
                createAndMoveMonster2(dt);

                // 延迟 7 秒后执行下一次调度
                this->schedule(CC_SCHEDULE_SELECTOR(SecondScene::createAndMoveMonster3), 4.0f);
                };

            // 延迟 7 秒后执行第一次调度
            this->scheduleOnce(schedulerCallback, 20.0f, "  ");

        }
    }


}
void SecondScene::createAndMoveMonster3(float dt)
{
    std::vector<Vec2> path = {
Vec2(230, 470),
Vec2(715, 470),
Vec2(715, 620),
Vec2(1230, 620),
Vec2(1230, 470),
Vec2(1738, 470),
Vec2(1738, 920),
// 添加更多路径点...
    };
    //第一波有八只怪物
    if (round == 3) {
        ++round3_;
        //第一种怪物
        if (round3_ % 3 == 0) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster0.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round3_ % 3 == 1) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster1.png", 100, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }
        if (round3_ % 3 == 2) {
            //用于传递参数，                     先后为：速度、 生命值、 贴图、        伤害、价值、路径
            Monster* monster = Monster::create(50.0f, 100, "monster2.png", 110, 100, path);
            monster->setPosition(Vec2(230, 970));
            addChild(monster);
        }

        if (round3_ == 20)
        {
            round = 4;
        }
    }


}