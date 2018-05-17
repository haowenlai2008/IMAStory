#pragma once
#include "Monster.h"
#include "MonsterSM.h"
#include "AnimaParam.h"

USING_NS_CC;
class Slime : public Monster
{
public:
	CREATE_FUNC(Slime);
	virtual bool init();
	virtual void LoadAction();
	virtual void AttributesInit();
	virtual void update(float dt);
	virtual void Stay();
	virtual void BeingAttacking();
	virtual void Attack();
	virtual void Move();
	void AddSM();
protected:
	static Animation* Moving_L;
	static Animation* Moving_R;
	static Animation* Staying_L;
	static Animation* Staying_R;
	static Animation* Attacking_L;
	static Animation* Attacking_R;
	static Animation* BeingAttacking_L;
	static Animation* BeingAttacking_R;

};

