#pragma once
#include "cocos2d.h"
#include "Biology.h"
#include "AnimaParam.h"
#include "Useful.h"
USING_NS_CC;
class MonsterSM;
class AnimaParam;
class Monster:public Biology
{
public:
	CC_SYNTHESIZE_READONLY(bool, isMoving, MovingState);
	CC_SYNTHESIZE_READONLY(bool, isStaying, StayingState);
	CC_SYNTHESIZE_READONLY(bool, isBeingAttacking, BeingAttackingState);
	CC_SYNTHESIZE_READONLY(bool, isAttacking, AttackingState); 
	Dir getDir();
	State getState();
	void setDir(Dir dir);
	void setState(State state);
	void setEnable(bool _Enable);
	bool getEnable();
	void bindMonsterSM(MonsterSM* monsterSM);
	void LoadAction();
	virtual void AttributesInit();
	virtual void Move();
	virtual void Stay();
	virtual void Attack();
	virtual void BeingAttacking();
	AnimaParam MovingParam;
	AnimaParam StayingParam;
	AnimaParam AttackingParam;
	AnimaParam BeingAttackingParam;
protected:
	MonsterSM* m_SM;
	Animation* Moving_L;
	Animation* Moving_R;
	Animation* Staying_L;
	Animation* Staying_R;
	Animation* Attacking_L;
	Animation* Attacking_R;
	Animation* BeingAttacking_L;
	Animation* BeingAttacking_R;
	int MovingFrame;
	int StayingFrame;
	int AttackingFrame;
	int BeingAttackingFrame;
	float MovingSpeed;
	float StayingSpeed;
	float AttackingSpeed;
	float BeingAttackingSpeed;
};

