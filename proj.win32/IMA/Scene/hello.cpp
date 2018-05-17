#include "hello.h"
#include "GameBase.h"

Vec2 hello::FinalPoint = Vec2::ZERO;

Scene * hello::createScene()
{
	//��������
	Scene* scene = Scene::create();

	//ʹ��hello���create()��������ͼ��
	Layer* layer = hello::create();

	//��hello���ͼ����Ϊ�ӽڵ���볡��
	scene->addChild(layer);

	//���س�����ָ��
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
	//�����Ϸ���ڵĳߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�����Ϸ�������½ǵ�����
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