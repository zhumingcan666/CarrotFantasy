#include"GameScene.h"
Scene* GameScene::createScene() {
    Scene* scene = Scene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init() {
    Size size = Director::getInstance()->getVisibleSize();
    Sprite* image = Sprite::create("game.png");
    image->setPosition(size.width / 2, size.height / 2);
    addChild(image);

    return true;
}