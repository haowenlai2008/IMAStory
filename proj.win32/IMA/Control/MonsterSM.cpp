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
//����ƶ�
void MonsterSM::randomMove(float delta)
{
	//�������ǣ�������ƶ�
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
			//�ж�Ŀ��ص��Ƿ񳬳��߽�
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
	//��ɫ����
	if (!m_character || !m_character->isVisible())
	{
		Stay();
		return;
	}
	//����
	if (m_character && getEnable())
	{
		//�����֪��Χ
		if (Common::Getlength(m_character->getPosition(), getParent()->getPosition()) > 350)
		{
			foundCharacter = false;
			return;
		}
		//�ڹ����֪��Χ
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
