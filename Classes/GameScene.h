#pragma once
#ifndef GAMESCENE
#define GAMESCENE

#include<iostream>
#include<cocos2d.h>
USING_NS_CC;

class GameScene :public Layer {
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(GameScene);
};
#endif // !GAMESCENE
