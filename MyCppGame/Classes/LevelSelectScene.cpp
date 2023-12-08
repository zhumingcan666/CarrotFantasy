#include "HelloWorldScene.h"
#include"SecondScene.h"
#include"ThirdScene.h"
#include "LevelSelectScene.h"
#include "ui/CocosGUI.h"
#include <cstdlib>  // ���������������ͷ�ļ�
#include <ctime>    // ����ʱ�亯����ͷ�ļ�

USING_NS_CC;
/*********************************************************************�����ؿ�ѡ�����**********************************************************/
Scene* LevelSelectScene::createScene()
{
    return LevelSelectScene::create();
}

// ���ļ�������ʱ��ӡ���õĴ�����Ϣ�����ǵ��¶δ���.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LevelSelectScene.cpp\n");
}
/*********************************************************************��ʼ���ؿ�ѡ�����**********************************************************/
bool LevelSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        // ��ʼ��ʧ��
        return false;
    }

    // ��ȡ��Ļ�ɼ��ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ȡ��Ļԭ������
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��� "�ؿ�ѡ�����" ����������
    auto sprite = Sprite::create("Levelselectmenu.png");
    if (sprite == nullptr)
    {
        problemLoading("'Levelselectmenu.png'");
    }
    else
    {
        // ������ͼƬ��λ����Ļ����
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // ������ͼƬ���Ϊ�˲���ӽڵ�
        this->addChild(sprite, 0);
    }
    /**********************************************************************���ùؿ���Ƭ��������˿���ƶ�����Ч��****************************************************/
    // ��ӹؿ���Ƭ
    for (int i = 0; i < 2; ++i)
    {
        auto levelCard = Sprite::create(StringUtils::format("level_card_%d.png", i + 1));
        levelCard->setPosition(Vec2(500 + i * 900, 600));
        addChild(levelCard);
        levelCards.push_back(levelCard);
    }

    // ��Ӵ����¼�������
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        touchStartPos = touch->getLocation();
        return true;
    };

    listener->onTouchEnded = [&](Touch* touch, Event* event) {
        Vec2 touchEndPos = touch->getLocation();

        // �����������ĸ��ؿ�
        int clickedIndex = -1;
        for (int i = 0; i < levelCards.size(); ++i) {
            Rect cardRect = levelCards[i]->getBoundingBox();
            if (cardRect.containsPoint(touchEndPos)) {
                clickedIndex = i;
                break;
            }
        }

        // ��������ĳ���ؿ�
        if (clickedIndex != -1) {
            // �ж��Ƿ��Ƕ̻�
            if (std::abs(touchEndPos.x - touchStartPos.x) <= minSwipeDistance) {
                // ����̻��߼��������л�����Ӧ�ĳ���
                if (clickedIndex == 0)
                {
                    auto secondScene = SecondScene::create();
                    Director::getInstance()->replaceScene(secondScene);
                }
                else if (clickedIndex == 1)
                {
                    auto thirdScene = ThirdScene::create();
                    Director::getInstance()->replaceScene(thirdScene);
                }
            }
            // �����ǳ�������������
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// �л��ؿ�
void LevelSelectScene::changeLevel(int direction)
{
    // ����Ŀ��ؿ�����
    int currentLevelIndex = 0;
    currentLevelIndex += direction;
    currentLevelIndex = clampf(currentLevelIndex, 0, levelCards.size() - 1);

    // ����Ŀ��λ��
    Vec2 targetPos = Vec2(400 - currentLevelIndex * 400, 400);

    // ���ƽ�����ɶ���
    for (auto card : levelCards)
    {
        card->runAction(MoveTo::create(0.5f, targetPos));
    }
}

