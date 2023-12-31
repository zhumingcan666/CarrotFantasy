#pragma once
#ifndef __SECOND_SCENE_H__
#define __SECOND_SCENE_H__
#include "cocos2d.h"
#include"Monster.h"
#include"carrot.h"
#include <iostream>
#include <fstream>
#include"levelSelectScene.h"

///////////////////////�����ڶ���������Ҳ������Ϸ���棨map��//////////////////////
class SecondScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();
    int Musiccontrol = 0;//����������¼���ֿ��ư�ť�������
    virtual bool init();
    // �������ƶ�����ĺ���
    void menuBackHome(cocos2d::Ref* pSender);
    void menuBack(cocos2d::Ref* pSender);
    void SecondScene::MusicControl(Ref* sender);
    void createAndMoveMonster1(float dt);
    void createAndMoveMonster2(float dt);
    void createAndMoveMonster3(float dt);

    //�ؿ����棺Ϊ��ʵ�ֹ��ر��棬ֻ��Ҫ���һ��bool�������Ҹ�bool�����洢���ⲿ��ͨ���ñ���ʵ�ֺ����ؿ��ĵ���򿪡�
//����һ���ؿ��ɹ�����ʱ���趨���Դ򿪵ڶ��أ������õڶ��صĿ���bool����Ϊ1��
//���һ��д��״̬������
    void saveGameProgress(bool isGameCompleted) {
        std::string filePath = "game_progress.txt";
        std::ofstream file(filePath, std::ios::trunc); // ʹ�� std::ios::trunc ��־,ÿ�ε��ö���д
        if (file.is_open()) {
            file << isGameCompleted << std::endl;
            file.close();
            std::cout << "Game progress saved successfully." << std::endl;
        }
        else {
            std::cout << "Failed to save game progress." << std::endl;
        }
    }
    //���һ����ȡ״̬����
    void loadGameProgress(bool& isGameCompleted) {

        std::string filePath = "game_progress.txt";
        std::ifstream file(filePath);
        if (file.is_open()) {
            file >> isGameCompleted;
            file.close();
        }
        else {
            std::cout << "Failed to load game progress." << std::endl;
        }
    }




    /// ���ڼ��㿪�ֵ���ʱ
    int countdown = 3;
    void countDown(float dt);
    ///���ﲨ��
    int round=1;
    int round1_=0;
    int round2_ = 0;
    int round3_ = 0;

    ///�ӱ��ٰ�ť���õĺ���
    int speedCount=1;
    void speedUp(Ref* pSender);
    ///    ��ͣ��ť
    int stopCount=1;
    void stopORstart(Ref* pSender);



    bool Win=0;
   void checkWin(float dt)
    {
        if (round == 4) {
            cocos2d::Scene* scene = Director::getInstance()->getRunningScene();
             Monster* object = nullptr;
             Vector<Node*> children =scene->getChildren();
              // �����ӽڵ�
              for (Node* child : children)
                {
                 Monster* monster = dynamic_cast<Monster*>(child);
                 if (monster)
                 {
                   object = monster;
                   break;
                 }
              }

              if (object == nullptr)
                  Win = 1;
        }
        if (Win)
        {
            levelSelect::thirdScene = 1;
            saveGameProgress(levelSelect::thirdScene);
            auto spritewin = Sprite::create("win.png");
            // ������ͼƬ��λ����Ļ����
            spritewin->setPosition(1300,900);
           this-> addChild(spritewin, 4);
        }

    }
    // implement the "static create()" method manually
    CREATE_FUNC(SecondScene);

    
};

#endif // __SECOND_SCENE_H_