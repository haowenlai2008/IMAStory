#include "SnakeNode.h"
USING_NS_CC;
using namespace cocos2d::ui;

SnakeNode::SnakeNode(int x,int y)
{
	this->sprite = Sprite::create("node.jpg");
	this->SetSpriteSize();
	this->setPositionRC(x, y);
}

SnakeNode::~SnakeNode()
{
}


void SnakeNode::SetSpriteSize()
{
	auto unit = Director::getInstance()->getVisibleSize().width / 16;
	sprite->setContentSize(Size(unit * 11 / 12, unit * 11 / 12));
	sprite->setAnchorPoint(Point::ZERO);//设置锚点
	m_dir = ENUM_DIR::Dir_left;//向左移动
}
void SnakeNode::setPositionRC(int x, int y)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto One = Director::getInstance()->getVisibleSize().width / 16;
	auto Two = Director::getInstance()->getVisibleSize().height / 12;
	this->m_x = x;
	this->m_y = y;
	this->sprite->setPosition(Point(x*One+ origin.x, y*Two+ origin.y));
}

