#include "GameOver.h"


GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

Scene * GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();//获得界面尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得坐标系原点
	Scale9Sprite* sprite = Scale9Sprite::create("BackGround5.jpg");
	sprite->setContentSize(Size(visibleSize));
	//设置精灵坐标
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//将精灵添加到场景中
	this->addChild(sprite, 0);
	MenuItemImage* pCloseItem = MenuItemImage::create
	(
		"menu.png",
		"menu.png",
		this,
		menu_selector(GameOver::popScene)
	);
	pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - 18,
		origin.y + pCloseItem->getContentSize().height / 2));
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
    return true;
}

void GameOver::popScene(Ref * pSender)
{
	Director::getInstance()->purgeCachedData();
	TransitionFade* pTransition = TransitionFade::create(0.3, HelloWorld::createScene(), ccc3(248, 248, 255));
	Director::getInstance()->replaceScene(pTransition);
}
