#pragma once
#ifndef __SECOND_SCENE_H__
#define __SECOND_SCENE_H__
#include "cocos2d.h"
#include"Monster.h"
#include"carrot.h"

///////////////////////�����ڶ���������Ҳ������Ϸ���棨map��//////////////////////
class SecondScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//����������¼���ֿ��ư�ť�������
    virtual bool init();
    // �������ƶ�����ĺ���
    void menuBackHome(cocos2d::Ref* pSender);
    void SecondScene::MusicControl(Ref* sender);
    void createAndMoveMonster0(float dt);

    void createBarriers(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(SecondScene);
    
};

#endif // __SECOND_SCENE_H_