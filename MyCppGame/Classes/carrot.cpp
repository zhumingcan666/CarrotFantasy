#include"cocos2d.h"
#include"carrot.h"
USING_NS_CC;

//��̬��Ա�Ķ���ͳ�ʼ��
int Carrot::carrotPositionX = 0;
int Carrot::carrotPositionY = 0;
int Carrot::carrotHPPositionX = 0;
int Carrot::carrotHPPositionY = 0;

Sprite* Carrot::createSprite(int x, int y)
{
	carrotPositionX = x;
	carrotPositionY = y;
	carrotHPPositionX = carrotPositionX + 95;
	carrotHPPositionY = carrotPositionY;
	return Carrot::create();
}

// ���ļ�������ʱ��ӡ���õĴ�����Ϣ�����ǵ��¶δ���.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BossScene.cpp\n");
}

bool Carrot::init()
{
	if (!Sprite::init()) {
        // ��ʼ��ʧ��
        return false;
    }
	// ��ȡ��Ļ�ɼ��ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ȡ��Ļԭ������
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ��˽�г�Ա
	HP = 10;
	

	//�ܲ���ص���ͼ��ʼ��
	auto carrot = Sprite::create("carrotSave.png");//�ܲ�����
	addChild(carrot);
	carrot->setPosition(Vec2(origin.x+carrotPositionX,origin.y+carrotPositionY));
	carrot->setScale(1.5f);

	carrotHPCache = SpriteFrameCache::getInstance();//�����ܲ�����ֵ
	carrotHPCache->addSpriteFramesWithFile("carrotHP.plist");

	/*Vector<SpriteFrame*> carrotHPFrames;//����ÿһ֡
	char carrotHPName[25] = {0};
	for (int i = 1; i <= 10; i++)
	{
		sprintf(carrotHPName, "carrotHP%d.png", i);
		carrotHPFrames.pushBack(carrotHPCache->getSpriteFrameByName(carrotHPName));
	}*/

	//HP=10��ͼ��ʼ��
	auto initCarrotHPFrame = carrotHPCache->getSpriteFrameByName("carrotHP10.png");//ȡ��HP=10��һ֡
	if(initCarrotHPFrame){
		auto sprite = Sprite::createWithSpriteFrame(initCarrotHPFrame);
		addChild(sprite);
		sprite->setPosition(Vec2(origin.x+carrotHPPositionX,origin.y+carrotHPPositionY));
		sprite->setScale(1.5f);
	}
	else problemLoading("'carrotHP10.png'");

	//����Ƿ��й����������ܲ�������update����
	return true;
}

void Carrot::carrotUpdate(float dt)
{
	// ��ȡ��Ļԭ������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	HP--;
	//����һ��HP��ͼȥ����
	char frameName[20] = {0};
	sprintf(frameName,"carrotHP%d.png",HP);
	auto CarrotHPFrame = carrotHPCache->getSpriteFrameByName(frameName);//ȡ��HP��Ӧ��һ֡
	if(CarrotHPFrame){
		auto sprite = Sprite::createWithSpriteFrame(CarrotHPFrame);
		addChild(sprite);
		sprite->setPosition(Vec2(origin.x+carrotHPPositionX,origin.y+carrotHPPositionY));
		sprite->setScale(1.5f);
	}
	else problemLoading(frameName);
	
}
