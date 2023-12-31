#include "Tower.h"
#include"SecondScene.h"
#include"Monster.h"
#include"Tower2.h"
#include"Tower3.h"
//#include"coin.h"
USING_NS_CC;


Tower* Tower::createTower(const std::string& towerImage)
{
    Tower* tower = new Tower();
    if (tower && tower->init(towerImage))
    {
        tower->autorelease();
        return tower;
    }
    else
    {
        delete tower;
        return nullptr;
    }
}

bool Tower::init(const std::string& towerImage)
{
    if (!Sprite::initWithFile(towerImage))
    {
        return false;
    }
    // 注册 update 函数
    this->scheduleUpdate();
    // 设置触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Tower::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Tower::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Tower::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    m_towerImage = towerImage;//炮塔图片路径

    return true;
}

bool Tower::onTouchBegan(Touch* touch, Event* event)
{
    
 
    // 获取触摸点的位置
    m_lastTouchPos = this->getParent()->convertToNodeSpace(touch->getLocation());

    bool is_TouchOnTower = isTouchOnTower(m_lastTouchPos);//判断触摸点上是否有Tower1
    bool is_TouchOnTower2 = isTouchOnTower2(m_lastTouchPos);//判断触摸点上是否有Tower2
    bool is_TouchOnTower3 = isTouchOnTower3(m_lastTouchPos);//判断触摸点上是否有Tower3
    if (!is_TouchOnTower&&!is_TouchOnTower2&&!is_TouchOnTower3) {
        Rect allowedRect(100, 100, 200, 200);
        Rect forbiddenRect1(150, 300, 200, 1200);
        Rect forbiddenRect2(350, 300, 450, 200);
        Rect forbiddenRect3(650, 500, 700, 230);
        Rect forbiddenRect4(1150, 300, 700, 200);
        Rect forbiddenRect5(1650, 300, 200, 1200);
        Rect forbiddenRect6(0, 1150, 2000, 150);
        // 在点击之前检查是否已存在按钮，存在则移除
        removeTowerButton();
        if (!forbiddenRect1.containsPoint(m_lastTouchPos) && !forbiddenRect2.containsPoint(m_lastTouchPos) && !forbiddenRect3.containsPoint(m_lastTouchPos) && !forbiddenRect4.containsPoint(m_lastTouchPos) && !forbiddenRect5.containsPoint(m_lastTouchPos) && !forbiddenRect6.containsPoint(m_lastTouchPos))
        {
            // 显示选中图标
            showSelectionIcon(m_lastTouchPos);
            // 创建一个新的 MenuItemImage 对象
            auto menuItem = MenuItemImage::create("Bottle01.png", "Bottle01.png","Bottle00.png", CC_CALLBACK_1(Tower::onMenuItemClicked, this));
            menuItem->setName("MenuItem"); // 设置菜单项的名称
            // 创建一个菜单，并将 MenuItemImage 添加到菜单中
            auto menu = Menu::create(menuItem, nullptr);
            menu->setPosition(m_lastTouchPos + Vec2(-60, 70));
            menu->setName("menu"); // 设置菜单的名称
            // 将菜单添加到场景中
            this->getParent()->addChild(menu);

            //创建一个新的 MenuItemImage 对象
            auto menuItem2 = MenuItemImage::create("Fan01.png", "Fan01.png", CC_CALLBACK_1(Tower::onMenuItemClicked2, this));
            menuItem2->setName("MenuItem2"); // 设置菜单项的名称
            // 创建一个菜单，并将 MenuItemImage 添加到菜单中
            auto menu2 = Menu::create(menuItem2, nullptr);
            menu2->setPosition(m_lastTouchPos + Vec2(10, 70));
            menu2->setName("menu2"); // 设置菜单的名称
            // 将菜单添加到场景中
            this->getParent()->addChild(menu2);
            //创建一个新的 MenuItemImage 对象
            auto menuItem3 = MenuItemImage::create("Pin01.png", "Pin01.png", CC_CALLBACK_1(Tower::onMenuItemClicked7, this));
            menuItem3->setName("MenuItem3"); // 设置菜单项的名称
            // 创建一个菜单，并将 MenuItemImage 添加到菜单中
            auto menu7 = Menu::create(menuItem3, nullptr);
            menu7->setPosition(m_lastTouchPos + Vec2(80, 70));
            menu7->setName("menu3"); // 设置菜单的名称
            // 将菜单添加到场景中
            this->getParent()->addChild(menu7);
            return true;
        }
    }
    else if(is_TouchOnTower)
    {
        removeTowerButton();
        //删掉按钮
        // 创建一个新的 MenuItemImage 对象
        auto deleteItem = MenuItemImage::create("sell_80.png.png", "sell_80.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked3, this));
        deleteItem->setName("DeleteItem"); // 设置菜单项的名称
        // 创建一个菜单，并将 DeleteItem 添加到菜单中
        auto menu3 = Menu::create(deleteItem, nullptr);
        //升级按钮
        auto upgradeItem = MenuItemImage::create("upgrade_180.png.png", "upgrade_180.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked5, this));
        upgradeItem->setName("UpgradeItem"); // 设置菜单项的名称
        // 创建一个菜单，并将 UpgradeItem 添加到菜单中
        auto menu5 = Menu::create(upgradeItem, nullptr);
        // 获取当前节点所在的场景
        cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

        if (scene)
        {
            // 获取场景中的所有子节点
            Vector<Node*> children = scene->getChildren();

            // 遍历子节点
            for (Node* child : children)
            {
                // 使用 dynamic_cast 检查节点是否是 Tower2 类型
                Tower* tower = dynamic_cast<Tower*>(child);
                if (tower)
                {
                    // 获取炮塔的世界坐标
                    Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                    // 检查触摸点是否在炮塔范围内
                    if (m_lastTouchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                    {
                        towerposition = tower->getPosition();
                    }
                }
            }
                menu3->setPosition(towerposition + Vec2(0, -80));
                menu3->setName("menu3"); // 设置菜单的名称
                // 将菜单添加到场景中
                this->getParent()->addChild(menu3);
                menu5->setPosition(towerposition + Vec2(0, 80));
                menu5->setName("menu5"); // 设置菜单的名称
                // 将菜单添加到场景中
                this->getParent()->addChild(menu5);
        }
    }
    else if (is_TouchOnTower2)
    {
        removeTowerButton();
        // 创建一个新的 MenuItemImage 对象
        auto deleteItem2 = MenuItemImage::create("sell_80.png.png", "sell_80.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked4, this));
        deleteItem2->setName("DeleteItem"); // 设置菜单项的名称
        // 创建一个菜单，并将 DeleteItem 添加到菜单中
        auto menu4 = Menu::create(deleteItem2, nullptr);
        //升级按钮
        auto upgradeItem2 = MenuItemImage::create("upgrade_180.png.png", "upgrade_180.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked6, this));
        upgradeItem2->setName("UpgradeItem2"); // 设置菜单项的名称
        // 创建一个菜单，并将 UpgradeItem2 添加到菜单中
        auto menu6 = Menu::create(upgradeItem2, nullptr);
        // 获取当前节点所在的场景
        cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

        if (scene)
        {
            // 获取场景中的所有子节点
            Vector<Node*> children = scene->getChildren();

            // 遍历子节点
            for (Node* child : children)
            {
                // 使用 dynamic_cast 检查节点是否是 Tower2 类型
                Tower2* tower = dynamic_cast<Tower2*>(child);
                if (tower)
                {
                    // 获取炮塔的世界坐标
                    Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                    // 检查触摸点是否在炮塔范围内
                    if (m_lastTouchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                    {
                        towerposition = tower->getPosition();
                    }
                }
            }
            menu4->setPosition(towerposition + Vec2(0, -70));
            menu4->setName("menu4"); // 设置菜单的名称
            // 将菜单添加到场景中
            this->getParent()->addChild(menu4);
            menu6->setPosition(towerposition + Vec2(0, 80));
            menu6->setName("menu5"); // 设置菜单的名称
            // 将菜单添加到场景中
            this->getParent()->addChild(menu6);
        }
    }
    else if (is_TouchOnTower3)
    {
        removeTowerButton();
        //删掉按钮
        // 创建一个新的 MenuItemImage 对象
        auto deleteItem3 = MenuItemImage::create("sell_80.png.png", "sell_80.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked8, this));
        deleteItem3->setName("DeleteItem3"); // 设置菜单项的名称
        // 创建一个菜单，并将 DeleteItem 添加到菜单中
        auto menu7 = Menu::create(deleteItem3, nullptr);
        //升级按钮
        auto upgradeItem3 = MenuItemImage::create("upgrade_180.png.png", "upgrade_180.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked9, this));
        upgradeItem3->setName("UpgradeItem3"); // 设置菜单项的名称
        // 创建一个菜单，并将 UpgradeItem 添加到菜单中
        auto menu8 = Menu::create(upgradeItem3, nullptr);
        // 获取当前节点所在的场景
        cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

        if (scene)
        {
            // 获取场景中的所有子节点
            Vector<Node*> children = scene->getChildren();

            // 遍历子节点
            for (Node* child : children)
            {
                // 使用 dynamic_cast 检查节点是否是 Tower2 类型
                Tower3* tower3 = dynamic_cast<Tower3*>(child);
                if (tower3)
                {
                    // 获取炮塔的世界坐标
                    Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                    // 检查触摸点是否在炮塔范围内
                    if (m_lastTouchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                    {
                        towerposition = tower3->getPosition();
                    }
                }
            }
            menu7->setPosition(towerposition + Vec2(0, -80));
            menu7->setName("menu7"); // 设置菜单的名称
            // 将菜单添加到场景中
            this->getParent()->addChild(menu7);
            menu8->setPosition(towerposition + Vec2(0, 80));
            menu8->setName("menu8"); // 设置菜单的名称
            // 将菜单添加到场景中
            this->getParent()->addChild(menu8);
        }
        }
    return false;
}
//判断炮塔是否在触摸点的函数
bool Tower::isTouchOnTower(const cocos2d::Vec2& touchPos) const {
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 使用 dynamic_cast 检查节点是否是 Tower2 类型
            Tower* tower = dynamic_cast<Tower*>(child);
            if (tower)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {
                    // 触摸点在炮塔范围内
                    CCLOG("Touch on tower at (%f, %f)", touchPos.x, touchPos.y);
                    return true;
                }
            }
        }
    }

    // 触摸点不在任何炮塔范围内
    return false;
}
bool Tower::isTouchOnTower2(const cocos2d::Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 使用 dynamic_cast 检查节点是否是 Tower2 类型
            Tower2* tower2 = dynamic_cast<Tower2*>(child);
            if (tower2)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {
                    // 触摸点在炮塔范围内
                    CCLOG("Touch on tower at (%f, %f)", touchPos.x, touchPos.y);
                    return true;
                }
            }
        }
    }

    // 触摸点不在任何炮塔范围内
    return false;
}
bool Tower::isTouchOnTower3(const cocos2d::Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 使用 dynamic_cast 检查节点是否是 Tower2 类型
            Tower3* tower3 = dynamic_cast<Tower3*>(child);
            if (tower3)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {
                    // 触摸点在炮塔范围内
                    CCLOG("Touch on tower at (%f, %f)", touchPos.x, touchPos.y);
                    return true;
                }
            }
        }
    }

    // 触摸点不在任何炮塔范围内
    return false;
}




// 其他成员函数的实现...

//移除炮塔选择按钮
void Tower::removeTowerButton()
{
    Node* parentNode = this->getParent();
    if (parentNode)
    {
        Menu* existingMenu = dynamic_cast<Menu*>(parentNode->getChildByName("menu"));
        Menu* existingMenu2 = dynamic_cast<Menu*>(parentNode->getChildByName("menu2")); 
        Menu* existingMenu3= dynamic_cast<Menu*>(parentNode->getChildByName("menu3"));
        Menu* existingMenu4 = dynamic_cast<Menu*>(parentNode->getChildByName("menu4"));
        Menu* existingMenu5 = dynamic_cast<Menu*>(parentNode->getChildByName("menu5"));
        Menu* existingMenu6 = dynamic_cast<Menu*>(parentNode->getChildByName("menu6"));
        Menu* existingMenu7 = dynamic_cast<Menu*>(parentNode->getChildByName("menu7"));
        Menu* existingMenu8 = dynamic_cast<Menu*>(parentNode->getChildByName("menu8"));
        if (existingMenu)
        {
            existingMenu->removeFromParent();
            removeSelectionIcon();
        }
        if (existingMenu2)
        {
            existingMenu2->removeFromParent();
            removeSelectionIcon();
        }
        if (existingMenu3)
        {
            existingMenu3->removeFromParent();
            removeSelectionIcon();
        }
        if (existingMenu4)
        {
            existingMenu4->removeFromParent();
            removeSelectionIcon();
        }
        if (existingMenu5)
        {
            existingMenu5->removeFromParent();
            removeSelectionIcon();
        }
        if (existingMenu6)
        {
            existingMenu6->removeFromParent();
            removeSelectionIcon();
        }
        if (existingMenu7)
        {
            existingMenu7->removeFromParent();
            removeSelectionIcon();
        }
        if (existingMenu8)
        {
            existingMenu8->removeFromParent();
            removeSelectionIcon();
        }
    }
}

//炮塔选择按钮1的回调函数
void Tower::onMenuItemClicked(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;

    // 移除按钮
    removeTowerButton();
    // 创建一个新的 Tower 对象
    Tower* tower = Tower::createTower("bottle11.png");
    tower->setPosition(touchPos);

    // 将新的 Tower 添加到场景中
    this->getParent()->addChild(tower);

}
//炮塔选择按钮2的回调函数
void Tower::onMenuItemClicked2(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;

    // 移除按钮
    removeTowerButton();
    // 创建一个新的 Tower2 对象
    Tower2* fan = Tower2::createTower("Fan11.png");
    fan->setPosition(touchPos);

    // 将新的 Tower2 添加到场景中
    this->getParent()->addChild(fan);
}
//炮塔选择按钮3的回调函数
void Tower::onMenuItemClicked7(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;

    // 移除按钮
    removeTowerButton();
    // 创建一个新的 Tower 对象
    Tower3* Pin = Tower3::createTower("Pin11.png");
    Pin->setPosition(touchPos);

    // 将新的 Tower 添加到场景中
    this->getParent()->addChild(Pin);

}
void Tower::onMenuItemClicked3(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;
    // 除去炮塔
    removeTowerAt(touchPos); // 将参数改为 touchPos
    // 移除按钮
    removeTowerButton();
    removeTowerButton();
}
void Tower::onMenuItemClicked4(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;
    // 除去炮塔
    removeTowerAt2(touchPos); // 将参数改为 touchPos
    // 移除按钮
    removeTowerButton();
}
void Tower::onMenuItemClicked8(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;
    // 除去炮塔
    removeTowerAt3(touchPos); // 将参数改为 touchPos
    // 移除按钮
    removeTowerButton();
    removeTowerButton();
}
void Tower::onMenuItemClicked5(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;
    // 升级炮塔
    upgradeTower(touchPos);
    // 移除按钮
    removeTowerButton();
}
void Tower::onMenuItemClicked6(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;
    // 升级炮塔
    upgradeTower2(touchPos);
    // 移除按钮
    removeTowerButton();
}
void Tower::onMenuItemClicked9(Ref* sender)
{
    // 获取点击的菜单项
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // 使用保存的触摸点的位置
    Vec2 touchPos = m_lastTouchPos;
    // 升级炮塔
    upgradeTower3(touchPos);
    // 移除按钮
    removeTowerButton();
}
void Tower::upgradeTower(const cocos2d::Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 使用 dynamic_cast 检查节点是否是 Tower 类型
            Tower* tower = dynamic_cast<Tower*>(child);
            if (tower)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());
                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {
                    // 升级该炮塔，但限制最大等级为3
                    if (tower->towerLevel < MAX_TOWER_LEVEL)
                    {
                        tower->towerLevel++;

                        // 更新炮塔贴图
                        std::string newTowerImage = StringUtils::format("Bottle1%d.png", tower->towerLevel);
                        tower->setTexture(newTowerImage.c_str());

                        // 这里可以添加其他升级操作，例如扣除资源等
                    }
                }
            }
        }
    }
}
// Tower 类中的升级函数 Tower::upgradeTower 的实现
void Tower::upgradeTower2(const cocos2d::Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 尝试将节点转换为 Tower2 类型
            Tower2* tower2 = dynamic_cast<Tower2*>(child);
            if (tower2)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());
                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {// 升级该炮塔，但限制最大等级为3
                    if (tower2->towerLevel2 < MAX_TOWER2_LEVEL)
                    {
                        tower2->towerLevel2++;

                        // 更新炮塔贴图
                        std::string newTowerImage = StringUtils::format("Fan1%d.png", tower2->towerLevel2);
                        tower2->setTexture(newTowerImage.c_str());

                        // 这里可以添加其他升级操作，例如扣除资源等
                    }
                    // 在这里可以添加其他升级操作
                }
            }
        }
    }
}
void Tower::upgradeTower3(const cocos2d::Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 尝试将节点转换为 Tower2 类型
            Tower3* tower3 = dynamic_cast<Tower3*>(child);
            if (tower3)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());
                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {// 升级该炮塔，但限制最大等级为3
                    if (tower3->towerLevel3 < MAX_TOWER2_LEVEL)
                    {
                        tower3->towerLevel3++;

                        // 更新炮塔贴图
                        std::string newTowerImage = StringUtils::format("Pin1%d.png", tower3->towerLevel3);
                        tower3->setTexture(newTowerImage.c_str());

                        // 这里可以添加其他升级操作，例如扣除资源等
                    }
                    // 在这里可以添加其他升级操作
                }
            }
        }
    }
}


void Tower::removeTowerAt(const Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 使用 dynamic_cast 检查节点是否是 Tower2 类型
            Tower* tower = dynamic_cast<Tower*>(child);
            if (tower)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {
                    // 从父节点中移除炮塔
                    child->removeFromParent();
                    return; // 找到并移除炮塔后结束函数
                }
            }
        }
    //// 遍历子节点，查找与触摸点位置相近的炮塔
    //for (Node* child : getChildren())
    //{
    //    // 检查节点是否是 Tower 类型且已经放置
    //    if (dynamic_cast<Tower*>(child) && dynamic_cast<Tower*>(child)->isPlaced())
    //    {
    //        // 获取节点的世界坐标
    //        Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

    //        // 检查触摸点是否接近炮塔的位置
    //        if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的距离
    //        {
    //            // 从父节点中移除炮塔
    //            child->removeFromParent();
    //            return; // 找到并移除炮塔后结束函数
    //        }
    //    }
    }

    // 如果未找到要删除的炮塔
    CCLOG("Error: Tower not found at position (%f, %f)", touchPos.x, touchPos.y);
}
void Tower::removeTowerAt2(const Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 使用 dynamic_cast 检查节点是否是 Tower2 类型
            Tower2* tower2 = dynamic_cast<Tower2*>(child);
            if (tower2)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {
                    // 从父节点中移除炮塔
                    child->removeFromParent();
                    return; // 找到并移除炮塔后结束函数
                }
            }
        }
        //// 遍历子节点，查找与触摸点位置相近的炮塔
        //for (Node* child : getChildren())
        //{
        //    // 检查节点是否是 Tower 类型且已经放置
        //    if (dynamic_cast<Tower*>(child) && dynamic_cast<Tower*>(child)->isPlaced())
        //    {
        //        // 获取节点的世界坐标
        //        Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

        //        // 检查触摸点是否接近炮塔的位置
        //        if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的距离
        //        {
        //            // 从父节点中移除炮塔
        //            child->removeFromParent();
        //            return; // 找到并移除炮塔后结束函数
        //        }
        //    }
    }

    // 如果未找到要删除的炮塔
    CCLOG("Error: Tower not found at position (%f, %f)", touchPos.x, touchPos.y);
}
void Tower::removeTowerAt3(const Vec2& touchPos)
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();

        // 遍历子节点
        for (Node* child : children)
        {
            // 使用 dynamic_cast 检查节点是否是 Tower2 类型
            Tower3* tower3 = dynamic_cast<Tower3*>(child);
            if (tower3)
            {
                // 获取炮塔的世界坐标
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // 检查触摸点是否在炮塔范围内
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的触摸范围
                {
                    // 从父节点中移除炮塔
                    child->removeFromParent();
                    return; // 找到并移除炮塔后结束函数
                }
            }
        }
        //// 遍历子节点，查找与触摸点位置相近的炮塔
        //for (Node* child : getChildren())
        //{
        //    // 检查节点是否是 Tower 类型且已经放置
        //    if (dynamic_cast<Tower*>(child) && dynamic_cast<Tower*>(child)->isPlaced())
        //    {
        //        // 获取节点的世界坐标
        //        Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

        //        // 检查触摸点是否接近炮塔的位置
        //        if (touchPos.getDistance(towerWorldPos) < 50.0f) // 调整 50.0f 为适当的距离
        //        {
        //            // 从父节点中移除炮塔
        //            child->removeFromParent();
        //            return; // 找到并移除炮塔后结束函数
        //        }
        //    }
    }

    // 如果未找到要删除的炮塔
    CCLOG("Error: Tower not found at position (%f, %f)", touchPos.x, touchPos.y);
}


void Tower::onTouchMoved(Touch* touch, Event* event)
{
        // 保持防御塔固定在原地，不跟随触摸点移动
}

void Tower::onTouchEnded(Touch* touch, Event* event)
{

 
}
void Tower::update(float delta) {
    // 在 update 函数中实时更新炮塔的转向逻辑
    handleBulletSpriteCollisions(); // 调用处理转向的函数

}
void Tower::handleBulletSpriteCollisions()//实现炮塔转向
{
    // 获取当前节点所在的场景
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // 获取场景中的所有子节点
        Vector<Node*> children = scene->getChildren();
        Monster* currentTarget = nullptr;
        // 如果当前没有目标，或者当前目标已经被销毁，设置新的目标
        if (currentTarget == nullptr /*|| currentTarget->isDestroyed()*/)
        {
            // 遍历子节点
            for (Node* child : children)
            {
                // 检查子节点是否为怪物精灵实例
                Monster* monster = dynamic_cast<Monster*>(child);
                if (monster)
                {
                    // 获取炮塔和怪物的位置
                    Vec2 towerPos = this->getPosition();
                    Vec2 monsterPos = monster->getPosition();

                    // 计算炮塔与怪物之间的距离
                    float distance = towerPos.distance(monsterPos);

                    // 设置一个距离阈值，例如 500 像素
                    if (towerLevel == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                    else if (towerLevel == 3)
                    {
                        float distanceThreshold = 700.0f;
                        // 如果距离小于阈值，设置为目标
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // 找到目标后可以提前退出循环
                        }
                    }
                }
            }
        }

        // 如果当前有目标，计算炮塔指向怪物的角度
        if (currentTarget)
        {
            Vec2 towerPos = this->getPosition();
            Vec2 monsterPos = currentTarget->getPosition();

            float angle = atan2f(monsterPos.y - towerPos.y, monsterPos.x - towerPos.x);
            angle = CC_RADIANS_TO_DEGREES(angle); // 将弧度转换为角度

            // 设置炮塔旋转角度
            this->setRotation(-angle + 90); // 注意这里可能需要调整角度，具体情况根据你的游戏坐标系而定
        }
    }
}

void Tower::showSelectionIcon(const Vec2& position) {
    // 创建选中图标精灵
    auto selectionSprite = Sprite::create("select_02.png"); // 使用你自己的选中图标图片路径
    selectionSprite->setPosition(position);
    selectionSprite->setName("SelectionIcon"); // 设置选中图标的名称
    this->getParent()->addChild(selectionSprite);
}

void Tower::removeSelectionIcon() {
    auto selectionIcon = this->getParent()->getChildByName("SelectionIcon");
    if (selectionIcon) {
        selectionIcon->removeFromParent();
    }
}
