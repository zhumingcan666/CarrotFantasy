#include "Tower.h"
#include"SecondScene.h"
#include"Monster.h"
#include"Tower2.h"
#include"Tower3.h"
#include"carrot.h"
#include"Bullet.h"
#include"coin.h"
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
    // ע�� update ����
    this->scheduleUpdate();
    // ���ô���������
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Tower::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Tower::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Tower::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    m_towerImage = towerImage;//����ͼƬ·��
    schedule(schedule_selector(Tower::shootBullet1), 2.0f);
    return true;
}

bool Tower::onTouchBegan(Touch* touch, Event* event)
{


    // ��ȡ�������λ��
    m_lastTouchPos = this->getParent()->convertToNodeSpace(touch->getLocation());

    bool is_TouchOnTower = isTouchOnTower(m_lastTouchPos);//�жϴ��������Ƿ���Tower1
    bool is_TouchOnTower2 = isTouchOnTower2(m_lastTouchPos);//�жϴ��������Ƿ���Tower2
    bool is_TouchOnTower3 = isTouchOnTower3(m_lastTouchPos);//�жϴ��������Ƿ���Tower3
    bool is_TouchOnTower4 = isTouchOnTower4(m_lastTouchPos);//�жϴ��������Ƿ���carrot�ܲ�
    if (!is_TouchOnTower && !is_TouchOnTower2 && !is_TouchOnTower3 && !is_TouchOnTower4) {
        Rect allowedRect(100, 100, 200, 200);
        Rect forbiddenRect1(150, 300, 200, 1200);
        Rect forbiddenRect2(350, 300, 450, 200);
        Rect forbiddenRect3(650, 500, 700, 230);
        Rect forbiddenRect4(1150, 300, 700, 200);
        Rect forbiddenRect5(1650, 300, 200, 1200);
        Rect forbiddenRect6(0, 1150, 2000, 150);
        // �ڵ��֮ǰ����Ƿ��Ѵ��ڰ�ť���������Ƴ�
        removeTowerButton();
        if (!forbiddenRect1.containsPoint(m_lastTouchPos) && !forbiddenRect2.containsPoint(m_lastTouchPos) && !forbiddenRect3.containsPoint(m_lastTouchPos) && !forbiddenRect4.containsPoint(m_lastTouchPos) && !forbiddenRect5.containsPoint(m_lastTouchPos) && !forbiddenRect6.containsPoint(m_lastTouchPos))
        {
            // ��ʾѡ��ͼ��
            showSelectionIcon(m_lastTouchPos);
            // ����һ���µ� MenuItemImage ����
            auto menuItem = MenuItemImage::create("Bottle01.png", "Bottle01.png", "Bottle00.png", CC_CALLBACK_1(Tower::onMenuItemClicked, this));
            // ��ȡ��ǰ�ڵ����ڵĳ���
            cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

            if (scene)
            {
                // ��ȡ�����е������ӽڵ�
                Vector<Node*> children = scene->getChildren();

                // �����ӽڵ�
                for (Node* child : children)
                {
                    // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                    Coin* coin = dynamic_cast<Coin*>(child);
                    if (coin)
                    {
                        if (coin->coinCount < 100)
                        {
                            menuItem->setEnabled(false);  // ��ʼ����Ϊ����ѡ��״̬
                        }
                    }
                }
            }
            menuItem->setName("MenuItem"); // ���ò˵��������
            // ����һ���˵������� MenuItemImage ��ӵ��˵���
            auto menu = Menu::create(menuItem, nullptr);
            menu->setPosition(m_lastTouchPos + Vec2(-60, 70));
            menu->setName("menu"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu);
            //����һ���µ� MenuItemImage ����
            auto menuItem2 = MenuItemImage::create("Fan01.png", "Fan01.png", "Fan00.png", CC_CALLBACK_1(Tower::onMenuItemClicked2, this));
            // ��ȡ��ǰ�ڵ����ڵĳ���
            cocos2d::Scene* scene2 = Director::getInstance()->getRunningScene();

            if (scene2)
            {
                // ��ȡ�����е������ӽڵ�
                Vector<Node*> children = scene->getChildren();

                // �����ӽڵ�
                for (Node* child : children)
                {
                    // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                    Coin* coin = dynamic_cast<Coin*>(child);
                    if (coin)
                    {
                        if (coin->coinCount < 160)
                        {
                            menuItem2->setEnabled(false);  // ��ʼ����Ϊ����ѡ��״̬
                        }
                    }
                }
            }
            menuItem2->setName("MenuItem2"); // ���ò˵��������
            // ����һ���˵������� MenuItemImage ��ӵ��˵���
            auto menu2 = Menu::create(menuItem2, nullptr);
            menu2->setPosition(m_lastTouchPos + Vec2(10, 70));
            menu2->setName("menu2"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu2);
            //����һ���µ� MenuItemImage ����
            auto menuItem3 = MenuItemImage::create("Pin01.png", "Pin01.png", "Pin00.png", CC_CALLBACK_1(Tower::onMenuItemClicked7, this));
            // ��ȡ��ǰ�ڵ����ڵĳ���
            cocos2d::Scene* scene3 = Director::getInstance()->getRunningScene();

            if (scene)
            {
                // ��ȡ�����е������ӽڵ�
                Vector<Node*> children = scene->getChildren();

                // �����ӽڵ�
                for (Node* child : children)
                {
                    // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                    Coin* coin = dynamic_cast<Coin*>(child);
                    if (coin)
                    {
                        if (coin->coinCount < 160)
                        {
                            menuItem3->setEnabled(false);  // ��ʼ����Ϊ����ѡ��״̬
                        }
                    }
                }
            }
            menuItem3->setName("MenuItem3"); // ���ò˵��������
            // ����һ���˵������� MenuItemImage ��ӵ��˵���
            auto menu7 = Menu::create(menuItem3, nullptr);
            menu7->setPosition(m_lastTouchPos + Vec2(80, 70));
            menu7->setName("menu3"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu7);
            return true;
        }
    }
    else if (is_TouchOnTower)
    {
        removeTowerButton();
        //ɾ����ť
        // ����һ���µ� MenuItemImage ����
        auto deleteItem = MenuItemImage::create("sell_80.png.png", "sell_80.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked3, this));
        deleteItem->setName("DeleteItem"); // ���ò˵��������
        // ����һ���˵������� DeleteItem ��ӵ��˵���
        auto menu3 = Menu::create(deleteItem, nullptr);
        //������ť
        auto upgradeItem = MenuItemImage::create("upgrade_180.png.png", "upgrade_180.png.png", "upgrade_-180.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked5, this));
        // ��ȡ��ǰ�ڵ����ڵĳ���
        cocos2d::Scene* scene4 = Director::getInstance()->getRunningScene();

        if (scene4)
        {
            // ��ȡ�����е������ӽڵ�
            Vector<Node*> children = scene4->getChildren();

            // �����ӽڵ�
            for (Node* child : children)
            {
                // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                Coin* coin = dynamic_cast<Coin*>(child);
                if (coin)
                {
                    if (coin->coinCount < 180)
                    {
                        upgradeItem->setEnabled(false);  // ��ʼ����Ϊ����ѡ��״̬
                    }
                }
            }
        }
        upgradeItem->setName("UpgradeItem"); // ���ò˵��������
        // ����һ���˵������� UpgradeItem ��ӵ��˵���
        auto menu5 = Menu::create(upgradeItem, nullptr);
        // ��ȡ��ǰ�ڵ����ڵĳ���
        cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

        if (scene)
        {
            // ��ȡ�����е������ӽڵ�
            Vector<Node*> children = scene->getChildren();

            // �����ӽڵ�
            for (Node* child : children)
            {
                // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                Tower* tower = dynamic_cast<Tower*>(child);
                if (tower)
                {
                    // ��ȡ��������������
                    Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                    // ��鴥�����Ƿ���������Χ��
                    if (m_lastTouchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                    {
                        towerposition = tower->getPosition();
                    }
                }
            }
            menu3->setPosition(towerposition + Vec2(0, -80));
            menu3->setName("menu3"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu3);
            menu5->setPosition(towerposition + Vec2(0, 80));
            menu5->setName("menu5"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu5);
        }
    }
    else if (is_TouchOnTower2)
    {
        removeTowerButton();
        // ����һ���µ� MenuItemImage ����
        auto deleteItem2 = MenuItemImage::create("sell_96.png.png", "sell_96.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked4, this));
        deleteItem2->setName("DeleteItem"); // ���ò˵��������
        // ����һ���˵������� DeleteItem ��ӵ��˵���
        auto menu4 = Menu::create(deleteItem2, nullptr);
        //������ť
        auto upgradeItem2 = MenuItemImage::create("upgrade_220.png.png", "upgrade_220.png.png", "upgrade_-220.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked6, this));
        // ��ȡ��ǰ�ڵ����ڵĳ���
        cocos2d::Scene* scene5 = Director::getInstance()->getRunningScene();

        if (scene5)
        {
            // ��ȡ�����е������ӽڵ�
            Vector<Node*> children = scene5->getChildren();

            // �����ӽڵ�
            for (Node* child : children)
            {
                // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                Coin* coin = dynamic_cast<Coin*>(child);
                if (coin)
                {
                    if (coin->coinCount < 220)
                    {
                        upgradeItem2->setEnabled(false);  // ��ʼ����Ϊ����ѡ��״̬
                    }
                }
            }
        }
        upgradeItem2->setName("UpgradeItem2"); // ���ò˵��������
        // ����һ���˵������� UpgradeItem2 ��ӵ��˵���
        auto menu6 = Menu::create(upgradeItem2, nullptr);
        // ��ȡ��ǰ�ڵ����ڵĳ���
        cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

        if (scene)
        {
            // ��ȡ�����е������ӽڵ�
            Vector<Node*> children = scene->getChildren();

            // �����ӽڵ�
            for (Node* child : children)
            {
                // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                Tower2* tower = dynamic_cast<Tower2*>(child);
                if (tower)
                {
                    // ��ȡ��������������
                    Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                    // ��鴥�����Ƿ���������Χ��
                    if (m_lastTouchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                    {
                        towerposition = tower->getPosition();
                    }
                }
            }
            menu4->setPosition(towerposition + Vec2(0, -70));
            menu4->setName("menu4"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu4);
            menu6->setPosition(towerposition + Vec2(0, 80));
            menu6->setName("menu5"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu6);
        }
    }
    else if (is_TouchOnTower3)
    {
        removeTowerButton();
        //ɾ����ť
        // ����һ���µ� MenuItemImage ����
        auto deleteItem3 = MenuItemImage::create("sell_128.png.png", "sell_128.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked8, this));
        deleteItem3->setName("DeleteItem3"); // ���ò˵��������
        // ����һ���˵������� DeleteItem ��ӵ��˵���
        auto menu7 = Menu::create(deleteItem3, nullptr);
        //������ť
        auto upgradeItem3 = MenuItemImage::create("upgrade_220.png.png", "upgrade_220.png.png", "upgrade_-220.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked9, this));
        cocos2d::Scene* scene6 = Director::getInstance()->getRunningScene();
        if (scene6)
        {
            // ��ȡ�����е������ӽڵ�
            Vector<Node*> children = scene6->getChildren();

            // �����ӽڵ�
            for (Node* child : children)
            {
                // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                Coin* coin = dynamic_cast<Coin*>(child);
                if (coin)
                {
                    if (coin->coinCount < 220)
                    {
                        upgradeItem3->setEnabled(false);  // ��ʼ����Ϊ����ѡ��״̬
                    }
                }
            }
        }
        upgradeItem3->setName("UpgradeItem3"); // ���ò˵��������
        // ����һ���˵������� UpgradeItem ��ӵ��˵���
        auto menu8 = Menu::create(upgradeItem3, nullptr);
        // ��ȡ��ǰ�ڵ����ڵĳ���
        cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

        if (scene)
        {
            // ��ȡ�����е������ӽڵ�
            Vector<Node*> children = scene->getChildren();

            // �����ӽڵ�
            for (Node* child : children)
            {
                // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
                Tower3* tower3 = dynamic_cast<Tower3*>(child);
                if (tower3)
                {
                    // ��ȡ��������������
                    Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                    // ��鴥�����Ƿ���������Χ��
                    if (m_lastTouchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                    {
                        towerposition = tower3->getPosition();
                    }
                }
            }
            menu7->setPosition(towerposition + Vec2(0, -80));
            menu7->setName("menu7"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu7);
            menu8->setPosition(towerposition + Vec2(0, 80));
            menu8->setName("menu8"); // ���ò˵�������
            // ���˵���ӵ�������
            this->getParent()->addChild(menu8);
        }
    }
    else if (is_TouchOnTower4)
    {
        removeTowerButton();
        //�ܲ�������ť
        auto upgradeItem4 = MenuItemImage::create("upgrade_220.png.png", "upgrade_220.png.png", CC_CALLBACK_1(Tower::onMenuItemClicked10, this));
        upgradeItem4->setName("UpgradeItem4"); // ���ò˵��������
        // ����һ���˵������� UpgradeItem4 ��ӵ��˵���
        auto menu9 = Menu::create(upgradeItem4, nullptr);
        Vec2 CarrotPos = Vec2(1775, 995);
        menu9->setPosition(CarrotPos + Vec2(0, 80));
        menu9->setName("menu9"); // ���ò˵�������
        // ���˵���ӵ�������
        this->getParent()->addChild(menu9);
    }
    return false;
}
//�ж������Ƿ��ڴ�����ĺ���
bool Tower::isTouchOnTower(const cocos2d::Vec2& touchPos) const {
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Tower* tower = dynamic_cast<Tower*>(child);
            if (tower)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {
                    // ��������������Χ��
                    CCLOG("Touch on tower at (%f, %f)", touchPos.x, touchPos.y);
                    return true;
                }
            }
        }
    }

    // �����㲻���κ�������Χ��
    return false;
}
bool Tower::isTouchOnTower2(const cocos2d::Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Tower2* tower2 = dynamic_cast<Tower2*>(child);
            if (tower2)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {
                    // ��������������Χ��
                    CCLOG("Touch on tower at (%f, %f)", touchPos.x, touchPos.y);
                    return true;
                }
            }
        }
    }

    // �����㲻���κ�������Χ��
    return false;
}
bool Tower::isTouchOnTower3(const cocos2d::Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Tower3* tower3 = dynamic_cast<Tower3*>(child);
            if (tower3)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {
                    // ��������������Χ��
                    CCLOG("Touch on tower at (%f, %f)", touchPos.x, touchPos.y);
                    return true;
                }
            }
        }
    }

    // �����㲻���κ�������Χ��
    return false;
}
bool Tower::isTouchOnTower4(const cocos2d::Vec2& touchPos)
{
    Vec2 CarrotPos = Vec2(1775, 995);
    if (m_lastTouchPos.getDistance(CarrotPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
    {
        return true;
    }
    // �����㲻���κ�������Χ��
    return false;
}


// ������Ա������ʵ��...

//�Ƴ�����ѡ��ť
void Tower::removeTowerButton()
{
    Node* parentNode = this->getParent();
    if (parentNode)
    {
        Menu* existingMenu = dynamic_cast<Menu*>(parentNode->getChildByName("menu"));
        Menu* existingMenu2 = dynamic_cast<Menu*>(parentNode->getChildByName("menu2"));
        Menu* existingMenu3 = dynamic_cast<Menu*>(parentNode->getChildByName("menu3"));
        Menu* existingMenu4 = dynamic_cast<Menu*>(parentNode->getChildByName("menu4"));
        Menu* existingMenu5 = dynamic_cast<Menu*>(parentNode->getChildByName("menu5"));
        Menu* existingMenu6 = dynamic_cast<Menu*>(parentNode->getChildByName("menu6"));
        Menu* existingMenu7 = dynamic_cast<Menu*>(parentNode->getChildByName("menu7"));
        Menu* existingMenu8 = dynamic_cast<Menu*>(parentNode->getChildByName("menu8"));
        Menu* existingMenu9 = dynamic_cast<Menu*>(parentNode->getChildByName("menu9"));
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
        if (existingMenu9)
        {
            existingMenu9->removeFromParent();
            removeSelectionIcon();
        }
    }
}

//����ѡ��ť1�Ļص�����
void Tower::onMenuItemClicked(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;

    // �Ƴ���ť
    removeTowerButton();
    // ����һ���µ� Tower ����
    Tower* tower = Tower::createTower("bottle11.png");
    tower->setPosition(touchPos);

    // ���µ� Tower ��ӵ�������
    this->getParent()->addChild(tower);
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Coin* coin = dynamic_cast<Coin*>(child);
            if (coin)
            {
                coin->coinCount -= 100;
            }
        }
    }
}
//����ѡ��ť2�Ļص�����
void Tower::onMenuItemClicked2(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;

    // �Ƴ���ť
    removeTowerButton();
    // ����һ���µ� Tower2 ����
    Tower2* fan = Tower2::createTower("Fan11.png");
    fan->setPosition(touchPos);

    // ���µ� Tower2 ��ӵ�������
    this->getParent()->addChild(fan);
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Coin* coin = dynamic_cast<Coin*>(child);
            if (coin)
            {
                coin->coinCount -= 160;
            }
        }
    }
}
//����ѡ��ť3�Ļص�����
void Tower::onMenuItemClicked7(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;

    // �Ƴ���ť
    removeTowerButton();
    // ����һ���µ� Tower ����
    Tower3* Pin = Tower3::createTower("Pin11.png");
    Pin->setPosition(touchPos);

    // ���µ� Tower ��ӵ�������
    this->getParent()->addChild(Pin);
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Coin* coin = dynamic_cast<Coin*>(child);
            if (coin)
            {
                coin->coinCount -= 160;
            }
        }
    }
}
void Tower::onMenuItemClicked3(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;
    // ��ȥ����
    removeTowerAt(touchPos); // ��������Ϊ touchPos
    // �Ƴ���ť
    removeTowerButton();
    removeTowerButton();
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Coin* coin = dynamic_cast<Coin*>(child);
            if (coin)
            {
                coin->coinCount += 80;
            }
        }
    }
}
void Tower::onMenuItemClicked4(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;
    // ��ȥ����
    removeTowerAt2(touchPos); // ��������Ϊ touchPos
    // �Ƴ���ť
    removeTowerButton();
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Coin* coin = dynamic_cast<Coin*>(child);
            if (coin)
            {
                coin->coinCount += 96;
            }
        }
    }
}
void Tower::onMenuItemClicked8(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;
    // ��ȥ����
    removeTowerAt3(touchPos); // ��������Ϊ touchPos
    // �Ƴ���ť
    removeTowerButton();
    removeTowerButton();
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Coin* coin = dynamic_cast<Coin*>(child);
            if (coin)
            {
                coin->coinCount += 128;
            }
        }
    }
}
void Tower::onMenuItemClicked5(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;
    // ��������
    upgradeTower(touchPos);
    // �Ƴ���ť
    removeTowerButton();
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Coin* coin = dynamic_cast<Coin*>(child);
            if (coin)
            {
                coin->coinCount -= 180;
            }
        }
    }
}
void Tower::onMenuItemClicked6(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;
    // ��������
    upgradeTower2(touchPos);
    // �Ƴ���ť
    removeTowerButton();
}
void Tower::onMenuItemClicked9(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;
    // ��������
    upgradeTower3(touchPos);
    // �Ƴ���ť
    removeTowerButton();
}
void Tower::onMenuItemClicked10(Ref* sender)
{
    // ��ȡ����Ĳ˵���
    MenuItemImage* menuItem = static_cast<MenuItemImage*>(sender);

    // ʹ�ñ���Ĵ������λ��
    Vec2 touchPos = m_lastTouchPos;
    // ��������
    upgradeCarrot(touchPos);
    // �Ƴ���ť
    removeTowerButton();
}
void Tower::upgradeTower(const cocos2d::Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower ����
            Tower* tower = dynamic_cast<Tower*>(child);
            if (tower)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());
                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {
                    // ���������������������ȼ�Ϊ3
                    if (tower->towerLevel < MAX_TOWER_LEVEL)
                    {
                        tower->towerLevel++;

                        // ����������ͼ
                        std::string newTowerImage = StringUtils::format("Bottle1%d.png", tower->towerLevel);
                        tower->setTexture(newTowerImage.c_str());

                        // ����������������������������۳���Դ��
                    }
                }
            }
        }
    }
}
// Tower ���е��������� Tower::upgradeTower ��ʵ��
void Tower::upgradeTower2(const cocos2d::Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ���Խ��ڵ�ת��Ϊ Tower2 ����
            Tower2* tower2 = dynamic_cast<Tower2*>(child);
            if (tower2)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());
                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {// ���������������������ȼ�Ϊ3
                    if (tower2->towerLevel2 < MAX_TOWER2_LEVEL)
                    {
                        tower2->towerLevel2++;

                        // ����������ͼ
                        std::string newTowerImage = StringUtils::format("Fan1%d.png", tower2->towerLevel2);
                        tower2->setTexture(newTowerImage.c_str());

                        // ����������������������������۳���Դ��
                    }
                    // ������������������������
                }
            }
        }
    }
}
void Tower::upgradeTower3(const cocos2d::Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ���Խ��ڵ�ת��Ϊ Tower2 ����
            Tower3* tower3 = dynamic_cast<Tower3*>(child);
            if (tower3)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());
                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {// ���������������������ȼ�Ϊ3
                    if (tower3->towerLevel3 < MAX_TOWER2_LEVEL)
                    {
                        tower3->towerLevel3++;

                        // ����������ͼ
                        std::string newTowerImage = StringUtils::format("Pin1%d.png", tower3->towerLevel3);
                        tower3->setTexture(newTowerImage.c_str());

                        // ����������������������������۳���Դ��
                    }
                    // ������������������������
                }
            }
        }
    }
}
void Tower::upgradeCarrot(const cocos2d::Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ���Խ��ڵ�ת��Ϊ Carrot ����
            Carrot* carrot = dynamic_cast<Carrot*>(child);
            if (carrot)
            {
                // ��ȡ��������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());
                // ��鴥�����Ƿ��ڷ�Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {// �����ܲ������������ȼ�Ϊ3
                    if (carrot->level < 3)
                    {
                        carrot->levelUp();
                    }

                }
            }
        }
    }
}


void Tower::removeTowerAt(const Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Tower* tower = dynamic_cast<Tower*>(child);
            if (tower)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {
                    // �Ӹ��ڵ����Ƴ�����
                    child->removeFromParent();
                    return; // �ҵ����Ƴ��������������
                }
            }
        }
        //// �����ӽڵ㣬�����봥����λ�����������
        //for (Node* child : getChildren())
        //{
        //    // ���ڵ��Ƿ��� Tower �������Ѿ�����
        //    if (dynamic_cast<Tower*>(child) && dynamic_cast<Tower*>(child)->isPlaced())
        //    {
        //        // ��ȡ�ڵ����������
        //        Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

        //        // ��鴥�����Ƿ�ӽ�������λ��
        //        if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��ľ���
        //        {
        //            // �Ӹ��ڵ����Ƴ�����
        //            child->removeFromParent();
        //            return; // �ҵ����Ƴ��������������
        //        }
        //    }
    }

    // ���δ�ҵ�Ҫɾ��������
    CCLOG("Error: Tower not found at position (%f, %f)", touchPos.x, touchPos.y);
}
void Tower::removeTowerAt2(const Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Tower2* tower2 = dynamic_cast<Tower2*>(child);
            if (tower2)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {
                    // �Ӹ��ڵ����Ƴ�����
                    child->removeFromParent();
                    return; // �ҵ����Ƴ��������������
                }
            }
        }
        //// �����ӽڵ㣬�����봥����λ�����������
        //for (Node* child : getChildren())
        //{
        //    // ���ڵ��Ƿ��� Tower �������Ѿ�����
        //    if (dynamic_cast<Tower*>(child) && dynamic_cast<Tower*>(child)->isPlaced())
        //    {
        //        // ��ȡ�ڵ����������
        //        Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

        //        // ��鴥�����Ƿ�ӽ�������λ��
        //        if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��ľ���
        //        {
        //            // �Ӹ��ڵ����Ƴ�����
        //            child->removeFromParent();
        //            return; // �ҵ����Ƴ��������������
        //        }
        //    }
    }

    // ���δ�ҵ�Ҫɾ��������
    CCLOG("Error: Tower not found at position (%f, %f)", touchPos.x, touchPos.y);
}
void Tower::removeTowerAt3(const Vec2& touchPos)
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();

        // �����ӽڵ�
        for (Node* child : children)
        {
            // ʹ�� dynamic_cast ���ڵ��Ƿ��� Tower2 ����
            Tower3* tower3 = dynamic_cast<Tower3*>(child);
            if (tower3)
            {
                // ��ȡ��������������
                Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

                // ��鴥�����Ƿ���������Χ��
                if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��Ĵ�����Χ
                {
                    // �Ӹ��ڵ����Ƴ�����
                    child->removeFromParent();
                    return; // �ҵ����Ƴ��������������
                }
            }
        }
        //// �����ӽڵ㣬�����봥����λ�����������
        //for (Node* child : getChildren())
        //{
        //    // ���ڵ��Ƿ��� Tower �������Ѿ�����
        //    if (dynamic_cast<Tower*>(child) && dynamic_cast<Tower*>(child)->isPlaced())
        //    {
        //        // ��ȡ�ڵ����������
        //        Vec2 towerWorldPos = child->getParent()->convertToWorldSpace(child->getPosition());

        //        // ��鴥�����Ƿ�ӽ�������λ��
        //        if (touchPos.getDistance(towerWorldPos) < 50.0f) // ���� 50.0f Ϊ�ʵ��ľ���
        //        {
        //            // �Ӹ��ڵ����Ƴ�����
        //            child->removeFromParent();
        //            return; // �ҵ����Ƴ��������������
        //        }
        //    }
    }

    // ���δ�ҵ�Ҫɾ��������
    CCLOG("Error: Tower not found at position (%f, %f)", touchPos.x, touchPos.y);
}


void Tower::onTouchMoved(Touch* touch, Event* event)
{
    // ���ַ������̶���ԭ�أ������津�����ƶ�
}

void Tower::onTouchEnded(Touch* touch, Event* event)
{


}
void Tower::update(float delta) {
    // �� update ������ʵʱ����������ת���߼�
    handleBulletSpriteCollisions(); // ���ô���ת��ĺ���

}
void Tower::handleBulletSpriteCollisions()//ʵ������ת��
{
    // ��ȡ��ǰ�ڵ����ڵĳ���
    cocos2d::Scene* scene = Director::getInstance()->getRunningScene();

    if (scene)
    {
        // ��ȡ�����е������ӽڵ�
        Vector<Node*> children = scene->getChildren();
        currentTarget = nullptr;
        // �����ǰû��Ŀ�꣬���ߵ�ǰĿ���Ѿ������٣������µ�Ŀ��
        if (currentTarget == nullptr /*|| currentTarget->isDestroyed()*/)
        {
            // �����ӽڵ�
            for (Node* child : children)
            {
                // ����ӽڵ��Ƿ�Ϊ���ﾫ��ʵ��
                Monster* monster = dynamic_cast<Monster*>(child);
                if (monster)
                {
                    // ��ȡ�����͹����λ��
                    Vec2 towerPos = this->getPosition();
                    Vec2 monsterPos = monster->getPosition();

                    // �������������֮��ľ���
                    float distance = towerPos.distance(monsterPos);

                    // ����һ��������ֵ������ 500 ����
                    if (towerLevel == 1)
                    {
                        float distanceThreshold = 300.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel == 2)
                    {
                        float distanceThreshold = 500.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                    else if (towerLevel == 3)
                    {
                        float distanceThreshold = 700.0f;
                        // �������С����ֵ������ΪĿ��
                        if (distance < distanceThreshold)
                        {
                            currentTarget = monster;
                            break; // �ҵ�Ŀ��������ǰ�˳�ѭ��
                        }
                    }
                }
            }
        }

        // �����ǰ��Ŀ�꣬��������ָ�����ĽǶ�
        if (currentTarget)
        {
            Vec2 towerPos = this->getPosition();
            Vec2 monsterPos = currentTarget->getPosition();

            float angle = atan2f(monsterPos.y - towerPos.y, monsterPos.x - towerPos.x);
            angle = CC_RADIANS_TO_DEGREES(angle); // ������ת��Ϊ�Ƕ�

            // ����������ת�Ƕ�
            this->setRotation(-angle + 90); // ע�����������Ҫ�����Ƕȣ�����������������Ϸ����ϵ����
        }
    }
}

void Tower::showSelectionIcon(const Vec2& position) {
    // ����ѡ��ͼ�꾫��
    auto selectionSprite = Sprite::create("select_02.png"); // ʹ�����Լ���ѡ��ͼ��ͼƬ·��
    selectionSprite->setPosition(position);
    selectionSprite->setName("SelectionIcon"); // ����ѡ��ͼ�������
    this->getParent()->addChild(selectionSprite);
}

void Tower::removeSelectionIcon() {
    auto selectionIcon = this->getParent()->getChildByName("SelectionIcon");
    if (selectionIcon) {
        selectionIcon->removeFromParent();
    }
}

//�����ӵ������
void Tower::shootBullet1(float dt)
{
    if (currentTarget != nullptr) {
        auto bullet = Bullet::createSprite(towerposition.x, towerposition.y, currentTarget, 1, towerLevel);
        addChild(bullet);
    }
}
//void Tower::shootBullet2(float dt)
//{
//    if (currentTarget != nullptr) {
//        auto bullet = Bullet::createSprite(towerposition.x, towerposition.y, currentTarget, 2, towerLevel);
//        addChild(bullet);
//    }
//}
//void Tower::shootBullet3(float dt)
//{
//    if (currentTarget != nullptr) {
//        auto bullet = Bullet::createSprite(towerposition.x, towerposition.y, currentTarget, 3, towerLevel);
//        addChild(bullet);
//    }
//}