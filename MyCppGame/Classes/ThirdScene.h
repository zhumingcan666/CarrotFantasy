#pragma once
#pragma once
#ifndef __THIRD_SCENE_H__
#define __THIRD_SCENE_H__
#include "cocos2d.h"
///////////////////////�����ڶ���������Ҳ������Ϸ���棨map��//////////////////////
class ThirdScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//����������¼���ֿ��ư�ť�������
    virtual bool init();
    // �������ƶ�����ĺ���
    void createAndMoveMonster0(float dt);
    void menuBackHome(cocos2d::Ref* pSender);
    void ThirdScene::MusicControl(Ref* sender);
    // implement the "static create()" method manually
    CREATE_FUNC(ThirdScene);
};

#endif // __THIRD_SCENE_H__
