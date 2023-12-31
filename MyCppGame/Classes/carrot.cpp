#include"cocos2d.h"
#include"carrot.h"
USING_NS_CC;

//��̬��Ա�Ķ���ͳ�ʼ��
int Carrot::carrotPositionX = 0;
int Carrot::carrotPositionY = 0;
int Carrot::carrotHPPositionX = 0;
int Carrot::carrotHPPositionY = 0;

Carrot* Carrot::createSprite(int x, int y)
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
	HP = 6;
	form = 7;
	level = 1;

	//�ܲ���ص���ͼ��ʼ��
	auto carrot = Sprite::create("carrotSave.png");//�ܲ�����
	addChild(carrot);
	carrot->setPosition(Vec2(origin.x + carrotPositionX, origin.y + carrotPositionY));
	carrot->setScale(1.5f);

	carrotHPCache = SpriteFrameCache::getInstance();//�����ܲ�����ֵ
	carrotHPCache->addSpriteFramesWithFile("carrotHP.plist");

	carrotCache = SpriteFrameCache::getInstance();//�����ܲ�������̬��ͼ
	carrotCache->addSpriteFramesWithFile("carrot.plist");

	//HP=6��ͼ��ʼ��
	auto initCarrotHPFrame = carrotHPCache->getSpriteFrameByName("carrotHP6.png");//ȡ��HP=10��һ֡
	if (initCarrotHPFrame) {
		auto sprite = Sprite::createWithSpriteFrame(initCarrotHPFrame);
		addChild(sprite);
		sprite->setPosition(Vec2(origin.x + carrotHPPositionX, origin.y + carrotHPPositionY));
		sprite->setScale(1.5f);
	}
	else problemLoading("'carrotHP6.png'");


	carrotBoundingBox = Rect(carrot->getPositionX() - carrot->getContentSize().width * 0.5f,
		carrot->getPositionY() - carrot->getContentSize().height * 0.5f,
		carrot->getContentSize().width,
		carrot->getContentSize().height);

	schedule(schedule_selector(Carrot::handleMonsterSpriteCollisions), 1.0f, CC_REPEAT_FOREVER, 1.0f);
	return true;
}
void Carrot::handleMonsterSpriteCollisions(float dt)
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
			// ����ӽڵ��Ƿ�Ϊ���ﾫ��ʵ��
			Monster* monster = dynamic_cast<Monster*>(child);
			if (monster)
			{
				// ִ����ײ���
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
	// ��ȡ��Ļԭ������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	HP--;
	form--;
	//����һ��HP��ͼȥ����
	if (1) {
		char frameName[20] = { 0 };
		sprintf(frameName, "carrotHP%d.png", HP);
		auto CarrotHPFrame = carrotHPCache->getSpriteFrameByName(frameName);//ȡ��HP��Ӧ��һ֡
		if (CarrotHPFrame) {
			auto sprite = Sprite::createWithSpriteFrame(CarrotHPFrame);
			addChild(sprite);
			sprite->setPosition(Vec2(origin.x + carrotHPPositionX, origin.y + carrotHPPositionY));
			sprite->setScale(1.5f);
		}
		else problemLoading(frameName);
	}
	//����һ��carrot��ͼȥ����
	if (1) {
		char frameName[20] = { 0 };
		sprintf(frameName, "carrot%d.png", form);
		auto CarrotFrame = carrotCache->getSpriteFrameByName(frameName);//ȡ��carrot��Ӧ��һ֡
		if (CarrotFrame) {
			auto sprite = Sprite::createWithSpriteFrame(CarrotFrame);
			addChild(sprite);
			sprite->setPosition(Vec2(origin.x + carrotPositionX, origin.y + carrotPositionY));
			sprite->setScale(1.5f);
		}
		else problemLoading(frameName);
	}
}

void Carrot::levelUp()
{
	//���������
	if (level == 3) return;
	//HP��Ѫ���ȼ��������������⼼��
	HP += 2;
	level++;

	auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// ��ȡ��Ļԭ������

	//���������HP
	char frameName[20] = { 0 };
	sprintf(frameName, "carrotHP%d.png", HP);
	auto CarrotHPFrame = carrotHPCache->getSpriteFrameByName(frameName);//ȡ��HP��Ӧ��һ֡
	if (CarrotHPFrame) {
		auto sprite = Sprite::createWithSpriteFrame(CarrotHPFrame);
		addChild(sprite);
		sprite->setPosition(Vec2(/*origin.x + carrotHPPositionX, origin.y + carrotHPPositionY*/0,0));
		sprite->setScale(1.5f);
	}
	else problemLoading(frameName);

	//��ʾ������
	Node* parent = this->getParent();//��ȡ��ǰ�����������ʾ��
	if (parent != nullptr)
	{
		Sprite* scene = dynamic_cast<Sprite*> (parent);
		auto label = Label::createWithTTF("�ܲ���������", "fonts/Impact.ttf", 36);
		label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * (3.0 / 4.0) + origin.y));
		scene->addChild(label);

		// �������붯��
		auto fadeIn = FadeIn::create(1.0f);
		// ������������
		auto fadeOut = FadeOut::create(1.0f);
		// �����ӳٶ���
		auto delay = DelayTime::create(2.0f);
		// �����������У��ȵ������ӳ٣���󵭳�
		auto sequence = Sequence::create(fadeIn, delay, fadeOut, nullptr);
		// ���ж�������
		label->runAction(sequence);
	}
}
