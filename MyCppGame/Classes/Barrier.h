#pragma once
#ifndef BARRIER
#define BARRIER
#include "cocos2d.h"
#include<string>
USING_NS_CC;


/*********************�ϰ�����*****************************/
class Barrier: public Sprite {
public:

    int value;//�ϰ����ֵ
    int health;//�ϰ�������ֵ
    std::string fileName;//�ļ���



    ProgressTimer* healthBar;//������
    Barrier(const std::string& fname, int valu,int healt)
         : fileName(fname),value(valu) ,health(healt){}
     //���ڴ��ݲ������Ⱥ�Ϊ����ͼ����ֵ������ֵ
     static Barrier* create(const std::string& fname,int value,int healt);//���봫�Σ�ʵ�ֲ�ͬ�ϰ�����߼�

     virtual bool init();
     void barrierUpdate(float dt);

     bool a = 0;



};
#endif // !Monster
