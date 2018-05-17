#include "Monster.h"
#include "Useful.h"
#include "MonsterSM.h"
Dir Monster::getDir()
{
	if (m_SM)
		return m_SM->getDir();
	return Dir();
}

State Monster::getState()
{
	if (m_SM)
		return m_SM->getState();
	return State();
}

void Monster::setDir(Dir dir)
{
	if (m_SM)
	{
		m_SM->setDir(dir);
	}
}

void Monster::setState(State state)
{
	if (m_SM)
	{
		m_SM->setState(state);
	}
		
}

void Monster::setEnable(bool _Enable)
{
	m_SM->setEnable(_Enable);
}

bool Monster::getEnable()
{
	return m_SM->getEnable();
}


void Monster::bindMonsterSM(MonsterSM* monsterSM)
{
	m_SM = monsterSM;
	this->addChild(m_SM);
}

void Monster::LoadAction()
{
}

void Monster::AttributesInit()
{
	MovingParam = AnimaParam();
	StayingParam = AnimaParam();
	AttackingParam = AnimaParam();
	BeingAttackingParam = AnimaParam();
}

void Monster::Move()
{
}

void Monster::Stay()
{
}

void Monster::Attack()
{
}

void Monster::BeingAttacking()
{
}



