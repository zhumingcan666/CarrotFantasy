#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//计数器，记录音乐控制按钮点击次数
    virtual bool init();
    // a selector callback
    void StartGame(cocos2d::Ref* pSender);
    void HelloWorld::MusicControl(Ref* sender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__