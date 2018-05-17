#pragma once
#include "cocos2d.h"
#include "Useful.h"
USING_NS_CC;
static Vec2 vec[4] =
{
	Vec2(0,200),
	Vec2(0,-200),
	Vec2(-200,0),
	Vec2(200,0)
};

class Controller:public Node
{

public:
	virtual bool init();
	virtual void TurnLeftPress();
	virtual void TurnRightPress();
	virtual void RaisePress();
	virtual void FallPress();
	virtual void AttackPress();
	virtual void QTEPress();
	virtual void TurnLeftRelease();
	virtual void TurnRightRelease();
	virtual void RaiseRelease();
	virtual void FallRelease();
	virtual void AttackRelease();
	virtual void QTERelease();
	virtual void update(float dt);
	virtual void onKeyPress(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyRelease(EventKeyboard::KeyCode keyCode, Event* event);
	CREATE_FUNC(Controller);
	CC_SYNTHESIZE(float, moveSpeed_x, MoveSpeedX);
	CC_SYNTHESIZE(float, moveSpeed_y, MoveSpeedY);
	CC_SYNTHESIZE(State, m_state, State);
	CC_SYNTHESIZE(State, Last_state, LastState);
	CC_SYNTHESIZE(Dir, m_Dir, Dir);
	virtual void Run();
	virtual void Attack();
	virtual void BeingAttack();
	virtual void QTE();
	virtual void Stay();
private:
	bool _up;
	bool _down;
	bool _left;
	bool _right;
};

