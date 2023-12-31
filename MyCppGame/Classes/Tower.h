#pragma once
#ifndef __TOWER_H__
#define __TOWER_H__
#define MAX_TOWER_LEVEL 3  // 宏定义炮塔的最大等级
#include "cocos2d.h"
#include"Tower2.h"
class Tower : public cocos2d::Sprite
{
public:
    static Tower* createTower(const std::string& towerImage); // 创建防御塔实例的静态方法
    bool init(const std::string& towerImage); // 初始化方法

    bool isPlaced() const;
    void setPlaced(bool placed);
    bool isTouchOnTower(const cocos2d::Vec2& touchPos) const;
    bool Tower::isTouchOnTower2(const cocos2d::Vec2& touchPos);
    bool Tower::isTouchOnTower3(const cocos2d::Vec2& touchPos);
    bool Tower::isTouchOnTower4(const cocos2d::Vec2& touchPos);

    //剩下的等怪物和子弹写好
    // 点击事件处理函数
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//在刚刚触摸时调用
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);//在鼠标点击拖动时调用，我把内容设为了空内容，这样炮塔不会乱动
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);//在结束触摸时调用，也是空内容

    // 其他方法...
    void Tower::onMenuItemClicked(Ref* sender);//T型炮塔选中按钮的回调函数
    void Tower::onMenuItemClicked2(Ref* sender);//风扇炮塔选中按钮的回调函数
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
    void Tower::removeTowerButton();//在第二次点击时除去之前的炮塔旋转按钮
    void Tower::handleBulletSpriteCollisions();//炮塔旋转
    void Tower::update(float delta);//每一帧都更新炮塔状态
    void Tower::upgradeTower(const cocos2d::Vec2& touchPos);//炮塔升级函数
    void Tower::upgradeTower2(const cocos2d::Vec2& touchPos);
    void Tower::upgradeTower3(const cocos2d::Vec2& touchPos);
    void Tower::upgradeCarrot(const cocos2d::Vec2& touchPos);//萝卜升级函数
    void Tower::showSelectionIcon(const cocos2d::Vec2& position);//选中图标的创建函数
    void Tower::removeSelectionIcon();//选中图标的移除函数

private:

    cocos2d::Vec2 towerposition;
    int towerLevel=1;//定义炮塔等级，后续通过upgradeTower函数实现升级
    // 成员变量保存触摸点的位置
    cocos2d::Vec2 m_lastTouchPos;
    std::string m_towerImage; // 防御塔的图片路径
    // 在 Tower 类中添加一个成员变量来保存当前目标怪物的引用
    // 其他成员变量...
};

#endif // __TOWER_H__
