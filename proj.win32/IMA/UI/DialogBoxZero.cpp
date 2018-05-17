#include "DialogBoxZero.h"


bool DialogBoxZero::init()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	isHide = false;
	box = Sprite::create("DialogBox.png");
	box->setPosition(0, box->getContentSize().height / 2);
	sentence = Label::createWithSystemFont("A", "Arial", 30);
	sentence->setColor(Color3B::BLACK);
	sentence->setAnchorPoint(Vec2(0, 1));
	sentence->setPosition(Vec2(origin.x + 20,
		box->getContentSize().height - sentence->getContentSize().height));
	box->addChild(sentence, 1);
	box->setPosition(Vec2(box->getContentSize().width / 2, origin.y + box->getContentSize().height / 2));
	ico = Sprite::create();
	this->addChild(ico,1);
	this->addChild(box);
	this->schedule(schedule_selector(DialogBoxZero::showSentence), 0.02f);//添加定时器
	listenInit();
	hideDialog();
	return true;
}

bool DialogBoxZero::isFinish()
{
	return sentenceQueue.empty();
}

void DialogBoxZero::listenInit()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(DialogBoxZero::onKeyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	auto mouseListener = EventListenerMouse::create();//注册监听
	mouseListener->onMouseDown = CC_CALLBACK_1(DialogBoxZero::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void DialogBoxZero::showDialog(const std::string & sentence)
{
	sentenceQueue.push(SentenceUnit(sentence, ""));
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::showDialog(const std::string & sentence, const std::string & texture)
{
	sentenceQueue.push(SentenceUnit(sentence, texture));
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::showDialog(const std::string & sentence, const std::string & texture, const std::function<void()>& func)
{
	sentenceQueue.push(SentenceUnit(sentence, texture,func));
	
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::showDialog(const std::function<void()>& func)
{
	sentenceQueue.push(SentenceUnit(func));
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::hideDialog()
{
	this->setVisible(false);
	isHide = true;
}

void DialogBoxZero::showSentence(float dt)
{
	if (!sentenceQueue.empty() && charCounter < sentenceQueue.front().sentence.size())
	{
		charCounter++;
		auto head = sentenceQueue.front().sentence.begin();
		auto tail = sentenceQueue.front().sentence.begin() + charCounter;
		sentence->setString(std::string(head, tail));
		if (sentenceQueue.front().ico != "")
		{
			auto origin = Director::getInstance()->getVisibleOrigin();
			ico->setTexture(sentenceQueue.front().ico);
			ico->setPosition(Vec2(ico->getContentSize().width / 2, origin.y + box->getContentSize().height / 2 + 20));
			sentence->setPosition(Vec2(ico->getContentSize().width, sentence->getPositionY()));
		}	
	}
}

void DialogBoxZero::onMouseDown(Event * event)
{
	if (!sentenceQueue.empty() && this->isVisible())
	{

		EventMouse* e = (EventMouse*)event;			//获得鼠标事件指针
		Vec2 realPosition = Vec2(e->getCursorX(), e->getCursorY());
		if (realPosition.y < box->getContentSize().height)
		{
			if (charCounter < sentenceQueue.front().sentence.size())
			{
				charCounter = sentenceQueue.front().sentence.size() - 1;
				return;
			}
			charCounter = 0;
			sentenceQueue.front().func();
			sentenceQueue.pop();
		}
	}
	else
	{
		hideDialog();
	}
}

void DialogBoxZero::onKeyDown(EventKeyboard::KeyCode keyCode, Event * event)
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (!sentenceQueue.empty() && this->isVisible())
		{
			if (charCounter < sentenceQueue.front().sentence.size())
			{
				charCounter = sentenceQueue.front().sentence.size() - 1;
				return;
			}
			charCounter = 0; 
			sentenceQueue.front().func();
			sentenceQueue.pop();
			
		}
		else
		{
			hideDialog();
		}
	}
	
}
