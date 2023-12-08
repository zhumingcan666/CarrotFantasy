#include "HelloWorldScene.h"
#include"SecondScene.h"
#include"ThirdScene.h"
#include "LevelSelectScene.h"
#include "ui/CocosGUI.h"
#include <cstdlib>  // 包含随机数函数的头文件
#include <ctime>    // 包含时间函数的头文件

USING_NS_CC;
/*********************************************************************创建关卡选择界面**********************************************************/
Scene* LevelSelectScene::createScene()
{
    return LevelSelectScene::create();
}

// 在文件不存在时打印有用的错误消息而不是导致段错误.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LevelSelectScene.cpp\n");
}
/*********************************************************************初始化关卡选择界面**********************************************************/
bool LevelSelectScene::init()
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

    // 添加 "关卡选择界面" 的启动画面
    auto sprite = Sprite::create("Levelselectmenu.png");
    if (sprite == nullptr)
    {
        problemLoading("'Levelselectmenu.png'");
    }
    else
    {
        // 将场景图片定位在屏幕中央
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 将场景图片添加为此层的子节点
        this->addChild(sprite, 0);
    }
    /**********************************************************************放置关卡卡片，并设置丝滑移动动画效果****************************************************/
    // 添加关卡卡片
    for (int i = 0; i < 2; ++i)
    {
        auto levelCard = Sprite::create(StringUtils::format("level_card_%d.png", i + 1));
        levelCard->setPosition(Vec2(500 + i * 900, 600));
        addChild(levelCard);
        levelCards.push_back(levelCard);
    }

    // 添加触摸事件监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        touchStartPos = touch->getLocation();
        return true;
    };

    listener->onTouchEnded = [&](Touch* touch, Event* event) {
        Vec2 touchEndPos = touch->getLocation();

        // 计算点击的是哪个关卡
        int clickedIndex = -1;
        for (int i = 0; i < levelCards.size(); ++i) {
            Rect cardRect = levelCards[i]->getBoundingBox();
            if (cardRect.containsPoint(touchEndPos)) {
                clickedIndex = i;
                break;
            }
        }

        // 如果点击了某个关卡
        if (clickedIndex != -1) {
            // 判断是否是短击
            if (std::abs(touchEndPos.x - touchStartPos.x) <= minSwipeDistance) {
                // 处理短击逻辑，例如切换到相应的场景
                if (clickedIndex == 0)
                {
                    auto secondScene = SecondScene::create();
                    Director::getInstance()->replaceScene(secondScene);
                }
                else if (clickedIndex == 1)
                {
                    auto thirdScene = ThirdScene::create();
                    Director::getInstance()->replaceScene(thirdScene);
                }
            }
            // 否则，是长击，不做处理
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 切换关卡
void LevelSelectScene::changeLevel(int direction)
{
    // 计算目标关卡索引
    int currentLevelIndex = 0;
    currentLevelIndex += direction;
    currentLevelIndex = clampf(currentLevelIndex, 0, levelCards.size() - 1);

    // 计算目标位置
    Vec2 targetPos = Vec2(400 - currentLevelIndex * 400, 400);

    // 添加平滑过渡动画
    for (auto card : levelCards)
    {
        card->runAction(MoveTo::create(0.5f, targetPos));
    }
}

