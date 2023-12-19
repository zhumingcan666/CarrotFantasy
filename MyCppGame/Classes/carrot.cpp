#include"cocos2d.h"
#include"carrot.h"
USING_NS_CC;

//静态成员的定义和初始化
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

// 在文件不存在时打印有用的错误消息而不是导致段错误.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BossScene.cpp\n");
}

bool Carrot::init()
{
	if (!Sprite::init()) {
		// 初始化失败
		return false;
	}
	// 获取屏幕可见尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// 获取屏幕原点坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始化私有成员
	HP = 10;
	form = 7;

	//萝卜相关的贴图初始化
	auto carrot = Sprite::create("carrotSave.png");//萝卜本体
	addChild(carrot);
	carrot->setPosition(Vec2(origin.x + carrotPositionX, origin.y + carrotPositionY));
	carrot->setScale(1.5f);

	carrotHPCache = SpriteFrameCache::getInstance();//缓存萝卜生命值
	carrotHPCache->addSpriteFramesWithFile("carrotHP.plist");

	carrotCache = SpriteFrameCache::getInstance();//缓存萝卜被啃形态贴图
	carrotCache->addSpriteFramesWithFile("carrot.plist");

	//HP=10贴图初始化
	auto initCarrotHPFrame = carrotHPCache->getSpriteFrameByName("carrotHP10.png");//取出HP=10的一帧
	if (initCarrotHPFrame) {
		auto sprite = Sprite::createWithSpriteFrame(initCarrotHPFrame);
		addChild(sprite);
		sprite->setPosition(Vec2(origin.x + carrotHPPositionX, origin.y + carrotHPPositionY));
		sprite->setScale(1.5f);
	}
	else problemLoading("'carrotHP10.png'");


	carrotBoundingBox = Rect(carrot->getPositionX() - carrot->getContentSize().width * 0.5f,
                             carrot->getPositionY() - carrot->getContentSize().height * 0.5f,
                             carrot->getContentSize().width,
                             carrot->getContentSize().height);

	schedule(schedule_selector(Carrot::handleMonsterSpriteCollisions),1.0f,CC_REPEAT_FOREVER,1.0f);
	return true;
}
void Carrot::handleMonsterSpriteCollisions(float dt)
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
			// 检查子节点是否为怪物精灵实例
			Monster* monster = dynamic_cast<Monster*>(child);
			if (monster)
			{
				// 执行碰撞检测
				if (this->carrotBoundingBox.intersectsRect(monster->getBoundingBox()))
				{
					this->carrotUpdate();
				}
			}

		}
	}
}

void Carrot::carrotUpdate()
{
	// 获取屏幕原点坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	HP--;
	form--;
	//用另一张HP贴图去代替
	if (1) {
		char frameName[20] = { 0 };
		sprintf(frameName, "carrotHP%d.png", HP);
		auto CarrotHPFrame = carrotHPCache->getSpriteFrameByName(frameName);//取出HP对应的一帧
		if (CarrotHPFrame) {
			auto sprite = Sprite::createWithSpriteFrame(CarrotHPFrame);
			addChild(sprite);
			sprite->setPosition(Vec2(origin.x + carrotHPPositionX, origin.y + carrotHPPositionY));
			sprite->setScale(1.5f);
		}
		else problemLoading(frameName);
	}
	//用另一张carrot贴图去代替
	if (1) {
		char frameName[20] = { 0 };
		sprintf(frameName, "carrot%d.png", form);
		auto CarrotFrame = carrotCache->getSpriteFrameByName(frameName);//取出carrot对应的一帧
		if (CarrotFrame) {
			auto sprite = Sprite::createWithSpriteFrame(CarrotFrame);
			addChild(sprite);
			sprite->setPosition(Vec2(origin.x + carrotPositionX, origin.y + carrotPositionY));
			sprite->setScale(1.5f);
		}
		else problemLoading(frameName);
	}
}
