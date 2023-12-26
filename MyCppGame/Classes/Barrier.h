#pragma once
#ifndef BARRIER
#define BARRIER
#include "cocos2d.h"
#include<string>
USING_NS_CC;


/*********************障碍物类*****************************/
class Barrier: public Sprite {
public:

    int value;//障碍物价值
    int health;//障碍物生命值
    std::string fileName;//文件名



    ProgressTimer* healthBar;//生命条
    Barrier(const std::string& fname, int valu,int healt)
         : fileName(fname),value(valu) ,health(healt){}
     //用于传递参数，先后为：贴图、价值、生命值
     static Barrier* create(const std::string& fname,int value,int healt);//用与传参，实现不同障碍物的逻辑

     virtual bool init();
     void barrierUpdate(float dt);

     bool a = 0;



};
#endif // !Monster
