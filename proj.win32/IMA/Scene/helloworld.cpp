#include "helloworld.h"
#include "GameBase.h"


Scene * helloworld::createScene()
{
	//创建场景
	Scene* scene = Scene::create();

	//使用helloworld类的create()方法创建图层
	Layer* layer = helloworld::create();

	//将helloworld类的图层作为子节点放入场景
	scene->addChild(layer);

	//返回场景的指针
	return scene;
}


bool helloworld::init()
{
	if (!Layer::init())
	{
		return false;
	} 
	Size visibleSize = Director::getInstance()->getVisibleSize();	//获得视图的尺寸（宽， 高）
	Vec2 origin = Director::getInstance()->getVisibleOrigin();		//获得原点
	//创建宝箱
	Sprite* box = Sprite::create("Box.png");						//新建精灵
	box->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));	//把宝箱设置在视图中点
	this->addChild(box, 1);//添加宝箱为图层的子节点，优先级为1

	//创建背景
	Sprite* background = Sprite::create("background2.png");//新建一个精灵，纹理是background2.png
	background->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));//把背景设置到中点
	this->addChild(background,0);//优先级为0



	//创建菜单项和菜单
	MenuItemImage* exit = MenuItemImage::create("Exit.png", "Exit.png", CC_CALLBACK_1(helloworld::menuCloseCallback, this));//创建菜单项
	exit->setPosition(Vec2(visibleSize.width * 5 / 6, exit->getContentSize().height / 2 + 20));//设置坐标
	exit->setColor(Color3B(255,255,255));//设置颜色
	Menu* menu = Menu::create(exit, NULL);//创建菜单
	menu->setPosition(Vec2::ZERO);//设置坐标
	this->addChild(menu, 1);//添加菜单为图层的子节点

	return true;
}



void helloworld::menuCloseCallback(Ref* pSender)
{
	Sprite* sprite = Sprite::create("pixiv62468048.png");//创建精灵
	sprite->setPosition(Vec2(300, 400));//设置坐标
	sprite->setContentSize(Size(300, 300));//设置尺寸
	this->addChild(sprite);//添加精灵为该图层的子节点
}