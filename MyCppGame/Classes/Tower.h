#pragma once
#ifndef __TOWER_H__
#define __TOWER_H__
#define MAX_TOWER_LEVEL 3  // �궨�����������ȼ�
#include "cocos2d.h"
#include"Tower2.h"
class Tower : public cocos2d::Sprite
{
public:
    static Tower* createTower(const std::string& towerImage); // ����������ʵ���ľ�̬����
    bool init(const std::string& towerImage); // ��ʼ������

    bool isPlaced() const;
    void setPlaced(bool placed);
    bool isTouchOnTower(const cocos2d::Vec2& touchPos) const;
    bool Tower::isTouchOnTower2(const cocos2d::Vec2& touchPos);
    bool Tower::isTouchOnTower3(const cocos2d::Vec2& touchPos);
    bool Tower::isTouchOnTower4(const cocos2d::Vec2& touchPos);

    //ʣ�µĵȹ�����ӵ�д��
    // ����¼�������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//�ڸոմ���ʱ����
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);//��������϶�ʱ���ã��Ұ�������Ϊ�˿����ݣ��������������Ҷ�
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//�ڽ�������ʱ���ã�Ҳ�ǿ�����

    // ��������...
    void Tower::onMenuItemClicked(Ref* sender);//T������ѡ�а�ť�Ļص�����
    void Tower::onMenuItemClicked2(Ref* sender);//��������ѡ�а�ť�Ļص�����
    void Tower::onMenuItemClicked3(Ref* sender);
    void Tower::onMenuItemClicked4(Ref* sender);
    void Tower::onMenuItemClicked5(Ref* sender);
    void Tower::onMenuItemClicked6(Ref* sender);
    void Tower::onMenuItemClicked7(Ref* sender);
    void Tower::onMenuItemClicked8(Ref* sender);
    void Tower::onMenuItemClicked9(Ref* sender);
    void Tower::onMenuItemClicked10(Ref* sender);
    void Tower::removeTowerAt(const cocos2d::Vec2& touchPos);
    void Tower::removeTowerAt2(const cocos2d::Vec2& touchPos);
    void Tower::removeTowerAt3(const cocos2d::Vec2& touchPos);
    void Tower::removeTowerButton();//�ڵڶ��ε��ʱ��ȥ֮ǰ��������ת��ť
    void Tower::handleBulletSpriteCollisions();//������ת
    void Tower::update(float delta);//ÿһ֡����������״̬
    void Tower::upgradeTower(const cocos2d::Vec2& touchPos);//������������
    void Tower::upgradeTower2(const cocos2d::Vec2& touchPos);
    void Tower::upgradeTower3(const cocos2d::Vec2& touchPos);
    void Tower::upgradeCarrot(const cocos2d::Vec2& touchPos);//�ܲ���������
    void Tower::showSelectionIcon(const cocos2d::Vec2& position);//ѡ��ͼ��Ĵ�������
    void Tower::removeSelectionIcon();//ѡ��ͼ����Ƴ�����

private:

    cocos2d::Vec2 towerposition;
    int towerLevel=1;//���������ȼ�������ͨ��upgradeTower����ʵ������
    // ��Ա�������津�����λ��
    cocos2d::Vec2 m_lastTouchPos;
    std::string m_towerImage; // ��������ͼƬ·��
    // �� Tower �������һ����Ա���������浱ǰĿ����������
    // ������Ա����...
};

#endif // __TOWER_H__
