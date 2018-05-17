#pragma once
#include "cocos2d.h"
#include "Useful.h"
//#define STATE_DEBUG
USING_NS_CC;
class character;
class MonsterSM : public Node
{
public:
	CREATE_FUNC(MonsterSM);
	CC_SYNTHESIZE(State, m_state, State);
	CC_SYNTHESIZE(Dir, m_Dir, Dir);
	CC_SYNTHESIZE(float, MoveSpeed, MoveSpeed);
	CC_SYNTHESIZE(bool, Enable, Enable);
	virtual void Stay();
	virtual void BeingAttack();
	virtual void Attack();
	virtual void Move();
	virtual bool init();
	virtual void AttackEvent(float delta);
	virtual void randomMove(float delta);
	virtual void update(float dt);
	
private:
	//character* m_character;
	bool foundCharacter;
};

