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
//��Ϸ�����ʼ��
bool SecondScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	DirChange = false;
	setBackGround();//��ӱ���
	SetScoreLabel();//��ӼƷ���
	creatsnake();//�ߵĳ�ʼ��
	Setmenu();//���ò˵�
	m_score = 0;//��ʼ������
	schedule(schedule_selector(SecondScene::SnakeMove), 0.32f);//��ʼ����ʱ��
	setListener();//��ʼ������
	return true;
}
//�л��˵��ص�����
void SecondScene::popScene(Ref* pSender)
{
	this->unscheduleAllSelectors();
	Director::getInstance()->purgeCachedData();
	TransitionFade* pTransition = TransitionFade::create(0.3, HelloWorld::createScene(), ccc3(248, 248, 255));
	Director::getInstance()->replaceScene(pTransition);
}
//���üƷ���
void SecondScene::SetScoreLabel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_score = 0;
	auto labelScore = Label::create("Score is : 0", "����", 20);
	labelScore->setColor(Color3B(0x70, 0x70, 0x70));
	labelScore->setTag(110);
	labelScore->setPosition(Point(visibleSize.width - 50, visibleSize.height - 20));
	this->addChild(labelScore,1);
}
//������
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
	auto draw = DrawNode::create();//���õ�ͼ
	draw->setAnchorPoint(origin);//���õ�ͼê��
	draw->setPosition(origin);//���õ�ͼ����
	this->addChild(draw);//��ӵ�ͼ
	auto ijk = draw->getContentSize();//��õ�ͼ�ߴ�
	for (int j = 0; j < 15; j++)
	{
		VerticalPoints[0][j] = Vec2(visibleSize.width / 16 + visibleSize.width / 16 * j, 0);
	}//��������������1
	for (int j = 0; j < 15; j++)
	{
		VerticalPoints[1][j] = Vec2(visibleSize.width / 16 + visibleSize.width / 16 * j, visibleSize.height);
		draw->drawSegment(VerticalPoints[0][j], VerticalPoints[1][j], 0.3, Color4F(0x70, 0x70, 0x70, 1));
	}//��������������2������������1��2�γ���
	for (int i = 0; i < 11; i++)
	{
		HorizontalPoint[0][i] = Vec2(0, visibleSize.height / 12 + visibleSize.height / 12 * i);
	}//���ú���������1
	for (int i = 0; i < 11; i++)
	{
		HorizontalPoint[1][i] = Vec2(visibleSize.width, visibleSize.height / 12 + visibleSize.height / 12 * i);
		draw->drawSegment(HorizontalPoint[0][i], HorizontalPoint[1][i], 0.3, Color4F(0x70, 0x70, 0x70, 1));
	}//���ú���������2������������1��2�γ���
}
//�����
void SecondScene::creatsnake()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//���OpenGLԭʼ����
	spHead = new SnakeNode(8, 6);//������ͷ����ʼ����ͷ����
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
	int m_x = rand() % 16;//������������
	int m_y = rand() % 12;//������������
	while (TouchSnake(m_x*One, m_y*Two))//ȷ�����겻��������
	{
		m_x = rand() % 16;
		m_y = rand() % 12;
	}
	spfood =  Sprite::create("node.jpg");//����ʳ��
	spfood->setContentSize(Size(One * 11 / 12, Two * 11 / 12));//����ʳ��ߴ�
	spfood->setAnchorPoint(Point::ZERO);//����ê��
	spfood->setPosition(Vec2( m_x * One+ origin.x, m_y* Two + origin.y));//����ʳ�����λ��
	this->addChild(spfood, 0);//���ʳ�ﵽͼ��
}
//���ü��̼���
void SecondScene::setListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(SecondScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


//�ͷŰ����ص�����
void SecondScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_right && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_left;//�ı���ͷ�ķ���
			if (spHead->m_dir != ENUM_DIR::Dir_left)
				DirChange = true;
		}
		break;
	}//����İ�������Ϊ26
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_left && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_right;
			if (spHead->m_dir != ENUM_DIR::Dir_right)
				DirChange = true;
		}
		break;
	}//��
	case  EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_down && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_up;
			if (spHead->m_dir != ENUM_DIR::Dir_up)
				DirChange = true;
		}
		break;
	}//��
	case  EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		if (spHead->m_dir != ENUM_DIR::Dir_up && !DirChange)
		{
			spHead->m_dir = ENUM_DIR::Dir_down;
			DirChange = true;
		}
		break;
	}//��
	default:break;
	}
}


//�ߵ��ƶ�
void SecondScene::SnakeMove(float delta)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();//�����Ļ�ߴ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//���OpenGLԭʼ����
	auto HeadPosition = allbody.at(0)->getPosition();//��ͷ����
	auto foodPosition = spfood->getPosition();//ʳ������
	auto distance = (int)sqrt(pow(HeadPosition.x - foodPosition.x,2) + pow(HeadPosition.y - foodPosition.y,2));
	DirChange = false;
	if (TouchSnake(HeadPosition.x, HeadPosition.y))
	{
		this->unscheduleAllSelectors();//�رն�ʱ��
		this->GameOver();//��Ϸ����
	}
	else
	if (distance<=2|| TouchSnake(foodPosition.x,foodPosition.y))//�����ͷ��ʳ���������������
	{
		int m_x = 1 + rand() % 15;//������������
		int m_y = 1 + rand() % 11;//������������
		while (TouchSnake(m_x*One, m_y*Two))//ȷ�����겻��������
		{
			m_x = 1 + rand() % 15;
			m_y = 1 + rand() % 11;
		}
		this->m_score+=100;//�ӷ�
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
	for (int i = allbody.size() - 1; i > 0; i--)//�����ƶ�
	{
		allbody.at(i)->runAction(Place::create(Vec2(allbody.at(i - 1)->getPosition().x, allbody.at(i - 1)->getPosition().y)));
	}
	switch (spHead->m_dir)//���ݷ����ƶ���ͷ
	{
	case ENUM_DIR::Dir_up:
	{
		if (allbody.at(0)->getPosition().y + 0.02>= visibleSize.height- Two)
			allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, 0)));//��ǽ
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, allbody.at(0)->getPosition().y + Two)));
		break;
	}
	case ENUM_DIR::Dir_down:
	{
		if (allbody.at(0)->getPosition().y + 0.02 <= origin.y+ Two)
			allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, origin.y+visibleSize.height- One)));//��ǽ
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x, allbody.at(0)->getPosition().y - Two)));
		break;
	}
	case ENUM_DIR::Dir_left:
	{
		if (allbody.at(0)->getPosition().x + 0.02 < 2*One)
			allbody.at(0)->runAction(Place::create(Vec2(16*One, allbody.at(0)->getPosition().y)));//��ǽ
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x - One, allbody.at(0)->getPosition().y)));
		break;
	}
	case ENUM_DIR::Dir_right:
	{
		if (allbody.at(0)->getPosition().x + 0.02 > 16 * One)
			allbody.at(0)->runAction(Place::create(Vec2(One, allbody.at(0)->getPosition().y)));//��ǽ
		else
		    allbody.at(0)->runAction(Place::create(Vec2(allbody.at(0)->getPosition().x + One, allbody.at(0)->getPosition().y)));
		break;
	}
	default:
		break;
	}

	log("The position of Snake's head is (%d,%d)", int((allbody.at(0)->getPosition().x - origin.x) / One), int(allbody.at(0)->getPosition().y / One));
}
//���ò˵�
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
	);//�˵�����
	pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - 15,
		origin.y + pCloseItem->getContentSize().height / 2));
	Menu* pMenu = Menu::create(pCloseItem,NULL);//��Ӳ˵�
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
}
//��Ϸ����
void SecondScene::GameOver()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();//�����Ļ�ߴ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//���OpenGlԭʼ����
	Sprite* sprite = Sprite::create("GameOver.png");//��Ӿ���
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
		                     origin.y + visibleSize.height / 2));//���þ�������
	this->addChild(sprite,0);//��ͼ���м��뾫��
}
//�жϽڵ��Ƿ��������ص�
bool SecondScene::TouchSnake(float x, float y)
{
	for (int i = 1; i < allbody.size(); i++)//��������
	{
		if (Nodetouch(allbody.at(i)->getPosition(),Point(x,y)))
			return true;
	}
	return false;
}
//�ж������غ�
bool SecondScene::Nodetouch(Point first, Point second)
{
	auto distance = (int)sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
	if (distance <= 1)
		return true;
	return false;
}
