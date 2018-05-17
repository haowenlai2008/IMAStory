#include "Bottom.h"

//bool Bottom::init()
//{
//	if (!Node::init())
//	{
//		return false;
//	}
//	auto origin = Director::getInstance()->getVisibleOrigin();
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Sprite* sprite = Sprite::create("box.png");
//	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
//	this->addChild(sprite);
//}

void Bottom::setBottomSize(Size size)
{
	this->getNormalImage()->setContentSize(size);
	this->getSelectedImage()->setContentSize(size);
}

Bottom * Bottom::create(const std::string& name, const ccMenuCallback& callback)
{
	Bottom* bottom = (Bottom*)MenuItemImage::create(
		"BottomNormal.png",
		"BottomPress.png",
		callback
	);
	Label* Tag = Label::createWithSystemFont(name, "Arial", 30);
	Tag->setColor(Color3B::WHITE);
	Tag->setPosition(Vec2(bottom->getContentSize().width / 2, bottom->getContentSize().height / 2));
	bottom->addChild(Tag);
	return bottom;
}

Bottom * Bottom::CircalBottionCreate(const std::string & name, const ccMenuCallback & callback)
{
	Bottom* bottom = (Bottom*)MenuItemImage::create(
		"CircleBottomNormal.png",
		"CircalBottomPress.png",
		callback
	);
	Label* Tag = Label::createWithSystemFont(name, "Arial", 30);
	Tag->setColor(Color3B::WHITE);
	Tag->setPosition(Vec2(bottom->getContentSize().width / 2, bottom->getContentSize().height / 2));
	bottom->addChild(Tag);
	return bottom;
}
