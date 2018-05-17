#include "Box2DTestLayer.h"
#include <string>



Scene * Box2DTestLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -320));
	auto layer = Box2DTestLayer::create();
	scene->addChild(layer);
	return scene;
}

Box2DTestLayer::~Box2DTestLayer()
{
	CC_SAFE_DELETE(world);
}

bool Box2DTestLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}



	auto size = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("background2.png");
	sprite->setPosition(Vec2(size.width / 2, size.height / 2) + origin);
	this->addChild(sprite);
	auto label = Label::createWithSystemFont(u8"哈哈哈", "fonts/Marker Felt.ttf", 50);
	label->setPosition(Vec2(size.width / 2, size.height / 2) + origin);
	label->setColor(Color3B::BLACK);
	this->addChild(label);
	initPhysics();
	addNewSpriteAtPosition(sprite->getPosition());
	auto mouselistener = EventListenerMouse::create();
	mouselistener->onMouseDown = CC_CALLBACK_1(Box2DTestLayer::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener, this);
	this->scheduleUpdate();
	return true;
}
//物理世界初始化
void Box2DTestLayer::initPhysics()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto edgeSp = Sprite::create();	//边界
	auto body = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Vec2(size.width / 2 + origin.x, size.height / 2 + 100));
	edgeSp->setPhysicsBody(body);
	this->addChild(edgeSp);
	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Box2DTestLayer::onAcceleration, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//b2Vec2 gravity;
	//gravity.Set(0.0f, -320.0f);
	//world = new b2World(gravity);

	//world->SetAllowSleeping(true);
	//world->SetContinuousPhysics(true);
	//uint32 flag = 0;
	//flag += b2Draw::e_shapeBit;

	////定义物体
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0, 0);
	//b2Body* grounBody = world->CreateBody(&groundBodyDef);

	//b2EdgeShape groundBox;//边界

	//groundBox.Set(b2Vec2(0, 0), b2Vec2(size.width / PTM, 0));
	//grounBody->CreateFixture(&groundBox, 0);

	//groundBox.Set(b2Vec2(0, size.height / PTM), b2Vec2(size.width / PTM, size.height / PTM));
	//grounBody->CreateFixture(&groundBox, 0);

	//groundBox.Set(b2Vec2(0, size.height / PTM), b2Vec2(0, 0));
	//grounBody->CreateFixture(&groundBox, 0);

	//groundBox.Set(b2Vec2(size.width / PTM, size.height / PTM), b2Vec2(size.width / PTM, 0));
	//grounBody->CreateFixture(&groundBox, 0);
}

void Box2DTestLayer::createResetButton()
{
}

void Box2DTestLayer::addNewSpriteAtPosition(Vec2 p)
{
	//log("Add sprite %0.2f x %02.f", p.x, p.y);
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(p.x / PTM, p.y / PTM);
	//b2Body *body = world->CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(.5f, .5f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;
	//body->CreateFixture(&fixtureDef);

	////int x = (CCRANDOM_0_1() > .5 ? 0 : 1);
	////int y = (CCRANDOM_0_1() > .5 ? 0 : 1);
	//auto sprite = Sprite::create("slime_L.png");
	//
	//sprite->setPosition(p.x, p.y);
	//body->SetUserData(sprite);
	//this->addChild(sprite);


	auto sprite = Sprite::create("slime_L.png");
	sprite->setPosition(p.x, p.y);
	sprite->setAnchorPoint(Vec2(0.5f, 0.1f));
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 5);

	PhysicsShape* ps = body->getShape(0);
	ps->setMoment(0.2f);				//力矩
	ps->setMass(0.5f);				//质量
	ps->setDensity(0.2f);				//密度
	ps->setFriction(1.0f);				//摩擦力
	ps->setRestitution(1.0f);			//弹力
	sprite->setPhysicsBody(body);
	this->addChild(sprite);
}

void Box2DTestLayer::update(float dt)
{
	//world->Step(dt, 8, 1);
}

void Box2DTestLayer::onMouseUp(Event * event)
{
	EventMouse* e = (EventMouse*)event;			//获得鼠标事件指针
	addNewSpriteAtPosition(Vec2(e->getCursorX(),e->getCursorY()));
}

void Box2DTestLayer::onAcceleration(Acceleration * acc, Event * event)
{
	Vect gravite(-acc->y * 50, acc->x * 50);
	this->getPhysicsBody()->getWorld()->setGravity(gravite);
}

//
//#if CC_ENABLE_BOX2D_INTEGRATION
//void Box2DTestLayer::onDraw()
//{
//}
//#endif