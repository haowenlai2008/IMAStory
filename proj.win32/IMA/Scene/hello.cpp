#include "hello.h"
#include "GameBase.h"

Vec2 hello::FinalPoint = Vec2::ZERO;

Scene * hello::createScene()
{
	//创建场景
	Scene* scene = Scene::create();

	//使用hello类的create()方法创建图层
	Layer* layer = hello::create();

	//将hello类的图层作为子节点放入场景
	scene->addChild(layer);

	//返回场景的指针
	return scene;
}

void hello::SetFinalPoint(Vec2 finalPoint)
{
	hello::FinalPoint = finalPoint;
}

bool hello::init()
{
	if (!Layer::init())
	{
		return false;
	} 
	//获得游戏窗口的尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//获得游戏窗口左下角的坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("tips.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width - sprite->getContentSize().width / 2, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto restart = MenuItemImage::create("restart.png", "restart.png", CC_CALLBACK_1(hello::menuRestartCallback, this));
	restart->setPosition(Vec2(visibleSize.width * 5 / 6, visibleSize.height * 4 / 5));
	restart->setColor(Color3B::BLACK);
	auto exit = MenuItemImage::create("Exit.png", "Exit.png", CC_CALLBACK_1(hello::menuCloseCallback, this));
	exit->setPosition(Vec2(visibleSize.width * 5 / 6, exit->getContentSize().height / 2 + 20));
	exit->setColor(Color3B::BLACK);
	auto menu = Menu::create(restart, exit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void hello::menuRestartCallback(Ref* pSender)
{
	Scene* game = GameBase::createScene();
	Director::getInstance()->purgeCachedData();

	Director::getInstance()->replaceScene(game);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}


void hello::menuCloseCallback(Ref* pSender)
{
	UserDefault::getInstance()->setFloatForKey("Final_X", hello::FinalPoint.x);
	UserDefault::getInstance()->setFloatForKey("Final_Y", hello::FinalPoint.y);
	Director::getInstance()->end();
}