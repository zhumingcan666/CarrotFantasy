#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //创建“START”标签
    LabelTTF* start_label = LabelTTF::create("START", "Courier", 36);
    addChild(start_label);
    start_label->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    //创建touch监听器,并将其和监听的Node（start_label）绑定
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [start_label,this](Touch* t, Event* e) {
        //判断是否点击到这个label
        if (start_label->getBoundingBox().containsPoint(t->getLocation())) {
            Director::getInstance()->replaceScene(GameScene::createScene());
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, start_label);



    return true;
}


//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
    //Close the cocos2d-x game scene and quit the application
   // Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


//}
