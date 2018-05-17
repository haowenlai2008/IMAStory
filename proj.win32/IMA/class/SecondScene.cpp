#include "SecondScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "ui/UIScale9Sprite.h"
#include "SnakeNode.h"
#include "GameOver.h"
using namespace cocos2d::ui;
Scene* SecondScene::createScene() 
{
	auto scene = Scene::create();
	auto layer = SecondScene::create();
	scene->addChild(layer);
    return scene;
}
//游戏界面初始化
bool SecondScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	DirChange = false;
	setBackGround();//添加背景
	SetScoreLabel();//添加计分器
	creatsnake();//蛇的初始化
	Setmenu();//设置菜单
	m_score = 0;//初始化分数
	schedule(schedule_selector(SecondScene::SnakeMove), 0.32f);//初始化定时器
	setListener();//初始化监听
	return true;
}
//切换菜单回调函数
void SecondScene::popScene(Ref* pSender)
{
	this->unscheduleAllSelectors();
	Director::getInstance()->purgeCachedData();
	TransitionFade* pTransition = TransitionFade::create(0.3, HelloWorld::createScene(), ccc3(248, 248, 255));
	Director::getInstance()->replaceScene(pTransition);
}
//设置计分器
void SecondScene::SetScoreLabel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_score = 0;
	auto labelScore = Label::create("Score is : 0", "宋体", 20);
	labelScore->setColor(Color3B(0x70, 0x70, 0x70));
	labelScore->setTag(110);
	labelScore->setPosition(Point(visibleSize.width - 50, visibleSize.height - 20));
	this->addChild(labelScore,1);
}
//画网格
void SecondScene::setBackGround()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2  VerticalPoints[2][15];
	Vec2  HorizontalPoint[2][12];
	auto background = Sprite::create("background2.png");
	background->setContentSize(visibleSize);
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2));
	this->addChild(background);
	auto draw = DrawNode::create();//设置地图
	draw->setAnchorPoint(origin);//设置地图锚点
	draw->setPosition(origin);//设置地图坐标
	this->addChild(draw);//添加地图
	auto ijk = draw->getContentSize();//获得地图尺寸
	for (int j = 0; j < 15; j++)
	{
		VerticalPoints[0][j] = Vec2(visibleSize.width / 16 + visibleSize.width / 16 * j, 0);
	}//设置竖轴坐标组1
	for (int j = 0; j < 15; j++)
	{
		VerticalPoints[1][j] = Vec2(visibleSize.width / 16 + visibleSize.width / 16 * j, visibleSize.height);
		draw->drawSegment(VerticalPoints[0][j], VerticalPoints[1][j], 0.3, Color4F(0x70, 0x70, 0x70, 1));
	}//设置竖轴坐标组2，连接坐标组1和2形成线
	for (int i = 0; i < 11; i++)
	{
		HorizontalPoint[0][i] = Vec2(0, visibleSize.height / 12 + visibleSize.height / 12 * i);
	}//设置横轴坐标组1
	for (int i = 0; i < 11; i++)
	{
		HorizontalPoint[1][i] = Vec2(visibleSize.width, visibleSize.height / 12 + visibleSize.height / 12 * i);
		draw->drawSegment(HorizontalPoint[0][i], HorizontalPoint[1][i], 0.3, Color4F(0x70, 0x70, 0x70, 1));
	}//设置横轴坐标组2，连接坐标组1和2形成线
}
//添加蛇
void SecondScene::creatsnake()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得OpenGL原始坐标
	spHead = new SnakeNode(8, 6);//生成蛇头并初始化蛇头坐标
	allbody.pushBack(spHead->sprite);
	for (int i = 0; i < 5; i++)
	{
		auto body = new SnakeNode(spHead->m_x + i + 1, spHead->m_y);
		allbody.pushBack(body->sprite);
	}
	for (int i = 0; i <allbody.size(); i++)
	{
		this->addChild(allbody.at(i), 0);
	}
	int m_x = rand() % 16;//获得随机横坐标
	int m_y = rand() % 12;//获得随机纵坐标
	while (TouchSnake(m_x*One, m_y*Two))//确保坐标不在蛇身上
	{
		m_x = rand() % 16;
		m_y = rand() % 12;
	}
	spfood =  Sprite::create("node.jpg");//创建食物
	spfood->setContentSize(Size(One * 11 / 12, Two * 11 / 12));//设置食物尺寸
	spfood->setAnchorPoint(Point::ZERO);//设置锚点
	spfood->setPosition(Vec2( m_x * One+ origin.x, m_y* Two + origin.y));//设置食物随机位置
	this->addChild(spfood, 0);//添加食物到图层
}
//设置键盘监听
void SecondScene::setListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(SecondScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


//释放按键回调函数
void SecondScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_right && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_left;//改变蛇头的方向
			if (spHead->m_dir != ENUM_DIR::Dir_left)
				DirChange = true;
		}
		break;
	}//左键的按键代码为26
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_left && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_right;
			if (spHead->m_dir != ENUM_DIR::Dir_right)
				DirChange = true;
		}
		break;
	}//右
	case  EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_down && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_up;
			if (spHead->m_dir != ENUM_DIR::Dir_up)
				DirChange = true;
		}
		break;
	}//上
	case  EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_up && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_down;
			DirChange = true;
		}
		break;
	}//下
	default:break;
	}
}


//蛇的移动
void SecondScene::SnakeMove(float delta)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();//获得屏幕尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得OpenGL原始坐标
	auto HeadPosition = allbody.at(0)->getPosition();//蛇头坐标
	auto foodPosition = spfood->getPosition();//食物坐标
	auto distance = (int)sqrt(pow(HeadPosition.x - foodPosition.x,2) + pow(HeadPosition.y - foodPosition.y,2));
	DirChange = false;
	if (TouchSnake(HeadPosition.x, HeadPosition.y))
	{
		this->unscheduleAllSelectors();//关闭定时器
		this->GameOver();//游戏结束
	}
	else
	if (distance<=2|| TouchSnake(foodPosition.x,foodPosition.y))//如果蛇头和食物坐标距离趋于零
	{
		int m_x = 1 + rand() % 15;//获得随机横坐标
		int m_y = 1 + rand() % 11;//获得随机纵坐标
		while (TouchSnake(m_x*One, m_y*Two))//确保坐标不在蛇身上
		{
			m_x = 1 + rand() % 15;
			m_y = 1 + rand() % 11;
		}
		this->m_score+=100;//加分
		Label* label = (Label*)this->getChildByTag(110);
		char strscore[20];
		sprintf(strscore, "Score is:%d", m_score);
		label->setString(strscore);
	    spfood->runAction(Place::create(Point(m_x * One + origin.x, m_y * Two + origin.y)));
		auto last = allbody.back()->getPosition();
		auto body = new SnakeNode(0, 0);
		allbody.pushBack(body->sprite);
		this->addChild(body->sprite, 0);
	}
	for (int i = allbody.size() - 1; i > 0; i--)//蛇身移动
	{
		allbody.at(i)->runAction(Place::create(Vec2(allbody.at(i - 1)->getPosition().x, allbody.at(i - 1)->getPosition().y)));
	}
	switch (spHead->m_dir)//根据方向移动蛇头
	{
	case ENUM_DIR::Dir_up:
	{
		if (allbody.at(0)->getPosition().y + 0.02>= visibleSize.height- Two)
			allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, 0)));//穿墙
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, allbody.at(0)->getPosition().y + Two)));
		break;
	}
	case ENUM_DIR::Dir_down:
	{
		if (allbody.at(0)->getPosition().y + 0.02 <= origin.y+ Two)
			allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, origin.y+visibleSize.height- One)));//穿墙
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, allbody.at(0)->getPosition().y - Two)));
		break;
	}
	case ENUM_DIR::Dir_left:
	{
		if (allbody.at(0)->getPosition().x + 0.02 < 2*One)
			allbody.at(0)->runAction(Place::create(Vec2(16*One, allbody.at(0)->getPosition().y)));//穿墙
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x - One, allbody.at(0)->getPosition().y)));
		break;
	}
	case ENUM_DIR::Dir_right:
	{
		if (allbody.at(0)->getPosition().x + 0.02 > 16 * One)
			allbody.at(0)->runAction(Place::create(Vec2(One, allbody.at(0)->getPosition().y)));//穿墙
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x + One, allbody.at(0)->getPosition().y)));
		break;
	}
	default:
		break;
	}

	log("The position of Snake's head is (%d,%d)", int((allbody.at(0)->getPosition().x - origin.x) / One), int(allbody.at(0)->getPosition().y / One));
}
//设置菜单
void SecondScene::Setmenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemImage* pCloseItem = MenuItemImage::create
	(
		"menu.png",
		"menu.png",
		this,
		menu_selector(SecondScene::popScene)
	);//菜单按键
	pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - 15,
		origin.y + pCloseItem->getContentSize().height / 2));
	Menu* pMenu = Menu::create(pCloseItem,NULL);//添加菜单
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
}
//游戏结束
void SecondScene::GameOver()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();//获得屏幕尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得OpenGl原始坐标
	Sprite* sprite = Sprite::create("GameOver.png");//添加精灵
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
		                     origin.y + visibleSize.height / 2));//设置精灵坐标
	this->addChild(sprite,0);//往图层中加入精灵
}
//判断节点是否与蛇身重叠
bool SecondScene::TouchSnake(float x, float y)
{
	for (int i = 1; i < allbody.size(); i++)//遍历蛇身
	{
		if (Nodetouch(allbody.at(i)->getPosition(),Point(x,y)))
			return true;
	}
	return false;
}
//判断坐标重合
bool SecondScene::Nodetouch(Point first, Point second)
{
	auto distance = (int)sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
	if (distance <= 1)
		return true;
	return false;
}
