#include "Controller.h"
#include "GameManager.h"
#include "GameDataManager.h"
bool Controller::init()
{
	if (!Node::init())
	{
		return false;
	}
	_up = false;
	_down = false;
	_left = false;
	_right = false;
	m_state = State::Staying;

	m_Dir = Dir::DIR_RIGHT;

	moveSpeed_y = 2;
	moveSpeed_x = 4;
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Controller::onKeyPress, this);
	listener->onKeyReleased = CC_CALLBACK_2(Controller::onKeyRelease, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	return true;
}

void Controller::TurnLeftPress()
{
	if (getState() != State::Attacked)
	{
		_left = true;
		_right = false;
		m_Dir = Dir::DIR_LEFT;
	}
	Run();
}

void Controller::TurnRightPress()
{
	if (getState() != State::Attacked)
	{
		_right = true;
		_left = false;
		m_Dir = Dir::DIR_RIGHT;
	}
	Run();
}

void Controller::RaisePress()
{
	_up = true;
	_down = false;
	Run();
}

void Controller::FallPress()
{
	_down = true;
	_up = false;
	Run();
}

void Controller::AttackPress()
{
	Attack();
}

void Controller::QTEPress()
{
	QTE();
}

void Controller::TurnLeftRelease()
{
	_left = false;
	if (m_state == State::Running && !_up && !_down && !_right)
	{
		Stay();
	}
}

void Controller::TurnRightRelease()
{
	_right = false;
	if (m_state == State::Running && !_up && !_down && !_left)
	{
		Stay();
	}
}

void Controller::RaiseRelease()
{
	_up = false;
	if (m_state != State::QTE && !_right && !_left && !_down)
	{
		Stay();
	}
}

void Controller::FallRelease()
{
	_down = false;
	if (m_state != State::QTE && !_right && !_left && !_up)
	{
		Stay();
	}
}

void Controller::AttackRelease()
{
	if (_up || _down || _left || _right)
	{
		Run();
		return;
	}
	else
	{
		Stay();
	}
	
}

void Controller::QTERelease()
{
	if (_up || _down || _left || _right)
	{
		Run();
		return;
	}
	Stay();
}

void Controller::update(float dt)
{
	GameManager* gm = GameManager::getInstance();
	auto dm = GameDataManager::getInstance();
	Vec2 characterMove = Vec2(0, 0);
	if (m_state == State::Attacked || m_state == State::BeingAttacked)
	{
		return;
	}
	if (dm->getRecentMapID() == 0)
	{
		if (getParent()->getPositionX() < gm->_left && _left)
			return;
	}
	if (dm->getRecentMapID() == 3)
	{
		if (getParent()->getPositionX() > gm->_right && _right)
			return;
	}
	if (getParent()->getPositionY() < gm->_top && _up)
	{
		characterMove += vec[0] * moveSpeed_y;
	}
	if (getParent()->getPositionY() > gm->_bottom && _down)
	{
		characterMove += vec[1] * moveSpeed_y;
	}
	if (_left)
	{
		characterMove += vec[2] * moveSpeed_x;
	}
	if (_right)
	{
		characterMove += vec[3] * moveSpeed_x;
	}
	getParent()->runAction(MoveBy::create(dt, characterMove * dt));
}

void Controller::onKeyPress(EventKeyboard::KeyCode keyCode, Event * event)
{

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		RaisePress();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		FallPress();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		TurnLeftPress();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		TurnRightPress();
		break;
	case EventKeyboard::KeyCode::KEY_X:
		AttackPress();
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		QTEPress();
		break;
	default:break;
	}
}

void Controller::onKeyRelease(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		RaiseRelease();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		FallRelease();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		TurnLeftRelease();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		TurnRightRelease();
		break;
	case EventKeyboard::KeyCode::KEY_X:
		AttackRelease();
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		QTERelease();
		break;
	default:break;
	}
}

void Controller::Run()
{
	//if (m_state != State::QTE)
	//{
	//	m_state = State::Running;
	//	log("Character state: Running");
	//}
	m_state = State::Running;
	log("Character state: Running");
}

void Controller::Attack()
{
	m_state = State::Attacked;
	log("Character state: Attacked");
}

void Controller::BeingAttack()
{
	m_state = State::BeingAttacked;
	log("Character state: BeingAttacked");
}

void Controller::QTE()
{
	m_state = State::QTE;
	log("Character state: QTE");
}

void Controller::Stay()
{
	m_state = State::Staying;
	log("Character state: Staying");
}
