#include "Help.h"

using namespace cocos2d::ui;
Scene* Help::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = Help::create();
	scene->addChild(layer);
	return scene;
}

bool Help::init()
{
	auto VisibleSize = Director::getInstance()->getVisibleSize();
	auto Origin = Director::getInstance()->getVisibleOrigin();
	MenuItemImage* pOriginScene = MenuItemImage::create
	(
		"BackNormal.png",
		"BackSelected.png",
		this,
		menu_selector(Help::ComeHome)
	);
	pOriginScene->setPosition(Vec2(Origin.x+VisibleSize.width +150,
		                           Origin.y+pOriginScene->getContentSize().height/ 2));
	Menu* pMenu = Menu::create(pOriginScene, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	//创建精灵对象
	auto sprite = Scale9Sprite::create("BackGround5.jpg");
	sprite->setContentSize(Size(VisibleSize));
	
	//设置精灵坐标
	sprite->setPosition(Vec2(VisibleSize.width / 2 + Origin.x, VisibleSize.height / 2 + Origin.y));

	//将精灵添加到场景中
	this->addChild(sprite, 0);
	//创建精灵对象
	Scale9Sprite* help = Scale9Sprite::create("help.png");
	help->setPosition(Vec2(VisibleSize.width / 2 + Origin.x+50, VisibleSize.height / 2));

	//将精灵添加到场景中
	this->addChild(help, 0);
	return true;
}


void Help::ComeHome(Ref* pSender)
{  
	Director::getInstance()->purgeCachedData();
	TransitionFade* pTransition = TransitionFade::create(0.5, HelloWorld::createScene(), ccc3(248, 248, 255));
	Director::getInstance()->replaceScene(pTransition);
}