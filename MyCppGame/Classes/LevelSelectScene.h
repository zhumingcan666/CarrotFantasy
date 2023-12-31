#pragma once
#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include <fstream>


//��ȫ�ֱ���ʵ�ֱ���ؿ�
namespace levelSelect {
    extern bool thirdScene;
}

class LevelSelectScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    std::vector<cocos2d::Sprite*> levelCards; // ��Spriteʹ����ȷ�������ռ�
    cocos2d::Vec2 touchStartPos;
    void changeLevel(int direction); // �Ƴ��� "LevelSelectScene::"
    const float minSwipeDistance = 50.0f;



    //�ؿ����棺Ϊ��ʵ�ֹ��ر��棬ֻ��Ҫ���һ��bool�������Ҹ�bool�����洢���ⲿ��ͨ���ñ���ʵ�ֺ����ؿ��ĵ���򿪡�
//����һ���ؿ��ɹ�����ʱ���趨���Դ򿪵ڶ��أ������õڶ��صĿ���bool����Ϊ1��
// �洢���ⲿ��game_progress.txt�ļ��У�
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


    void reset(Ref* sender);
    void backHome(Ref* sender);
    CREATE_FUNC(LevelSelectScene);

};

#endif // __LEVELSELECT_SCENE_H__
