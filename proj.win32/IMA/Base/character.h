#pragma once
#include "Biology.h"
USING_NS_CC;

enum class State;
enum class Dir;
enum class characterData 
{
	name,
	id,
	MaxHP,
	RealHP,
	MaxEXP,
	EXP,
	ATK,
	Level,
	DeadEXP
};
class character : public Biology
{
public:
	CC_SYNTHESIZE_READONLY(bool, isMoving, MovingState);
	CC_SYNTHESIZE_READONLY(bool, isStaying, StayingState);
	CC_SYNTHESIZE_READONLY(bool, isBeingAttacking, BeingAttackingState);
	CC_SYNTHESIZE_READONLY(bool, isAttacking, AttackingState);
	CC_SYNTHESIZE_READONLY(bool, isQTE, QTEState);

	State getState();
	Dir getDir();
	void setDir(Dir dir);
	void setState(State state);
	void readDataFromDB();
	void readDataFromJson();
	void ReLife();
	void Flip();
	virtual void setTagPosition(float x, float y);
	virtual void LoadAction();
	virtual void AttributesInit();
	virtual void Move();
	virtual void Stay();
	virtual void Attack();
	virtual void BeingAttack();
	virtual void QTE();
protected:
	Animation* Moving_R;
	Animation* Staying_R;
	Animation* Attacking_R;
	Animation* BeingAttacking_R;
	Animation* QTE_R;
	int MovingFrame;
	int StayingFrame;
	int AttackingFrame;
	int BeingAttackingFrame;
	int QTEFrame;
	float MovingSpeed;
	float StayingSpeed;
	float AttackingSpeed;
	float BeingAttackingSpeed;
	float QTESpeed;
};

