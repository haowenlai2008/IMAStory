#include "MonsterSM.h"
#include "Useful.h"
#include "MainCharacter.h"
#include "GameManager.h"
#include "character.h"
void MonsterSM::Stay()
{
	setState(State::Staying);
#ifdef STATE_DEBUG
	log("Monster state: Staying");
#endif // STATE_DEBUG
}

void MonsterSM::BeingAttack()
{
	m_state = State::BeingAttacked;
#ifdef STATE_DEBUG
	log("Monster state: BeingAttacking");
#endif // STATE_DEBUG
}

void MonsterSM::Attack()
{
	m_state = State::Attacked;
#ifdef STATE_DEBUG
	log("Monster state: Attacking");
#endif // STATE_DEBUG
}

void MonsterSM::Move()
{
	m_state = State::Running;
}

bool MonsterSM::init()
{
	m_state = State::Staying;
	m_Dir = Dir::DIR_RIGHT;
	setEnable(true);
	//m_character = CharacterManager::getInstance()->getCharacter();
	setMoveSpeed(60.0f);
	foundCharacter = false;
	this->schedule(schedule_selector(MonsterSM::randomMove), 2.5f);
	this->schedule(schedule_selector(MonsterSM::AttackEvent), 1.0f);
	this->scheduleUpdate();
	return true;
}
void MonsterSM::AttackEvent(float delta)
{
	auto m_character = GameManager::getInstance()->getCharacter();
	if ((getState() == State::Staying || getState() == State::Running) && getEnable() &&
		Common::Getlength(m_character->getPosition(), getParent()->getPosition()) < 150)
	{
		foundCharacter = true;
		Attack();
		log("Attack");
		return;
	}
	else
	{
		Stay();
	}
}
//随机移动
void MonsterSM::randomMove(float delta)
{
	//发现主角，不随机移动
	if (getEnable())
		if (!foundCharacter)
		{
			Move();
			RandomHelper random;
			GameManager* sceneManager = GameManager::getInstance();
			int x = random.random_int(-1, 1);
			int y = random.random_int(-1, 1);
			Vec2 dir = Vec2(x, y);
			dir.normalize();
			Vec2 TargetPos = dir * getMoveSpeed() + getParent()->getPosition();
			//判断目标地点是否超出边界
			while (TargetPos.x > sceneManager->_right ||
				TargetPos.x < sceneManager->_left ||
				TargetPos.y > sceneManager->_top ||
				TargetPos.y < sceneManager->_bottom)
			{
				x = random.random_int(-1, 1);
				y = random.random_int(-1, 1);
				dir = Vec2(x, y);
				dir.normalize();
				TargetPos = dir * getMoveSpeed() + getParent()->getPosition();
			}
			if (x != 0)
				x < 0 ? setDir(Dir::DIR_LEFT) : setDir(Dir::DIR_RIGHT);
			auto movefunc = MoveBy::create(1.0f, dir * getMoveSpeed());
			auto finish = CallFunc::create([this]() { Stay(); });
			Action* action = Sequence::create(movefunc, finish, NULL);
			getParent()->runAction(action);
		}
	
}

void MonsterSM::update(float dt)
{
	auto m_character = GameManager::getInstance()->getCharacter();
	//角色死亡
	if (!m_character || !m_character->isVisible())
	{
		Stay();
		return;
	}
	//攻击
	if (m_character && getEnable())
	{
		//怪物感知范围
		if (Common::Getlength(m_character->getPosition(), getParent()->getPosition()) > 350)
		{
			foundCharacter = false;
			return;
		}
		//在怪物感知范围
		foundCharacter = true;
		if (m_character->getPositionX() > getParent()->getPositionX())
		{
			setDir(Dir::DIR_RIGHT);
		}
		else
		{
			setDir(Dir::DIR_LEFT);
		}
		if (getState() != State::BeingAttacked && getState() != State::Attacked)
		{
			Vec2 addr = Vec2(m_character->getPosition() - getParent()->getPosition());
			addr.normalize();
			getParent()->runAction(MoveBy::create(dt, addr * getMoveSpeed() * dt));
			Move();
		}
	}
	
}
