#pragma once
#include "character.h"


class MainCharacter : public character
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual void LoadAction();
	virtual void AttributesInit();
	virtual void Move();
	virtual void Stay();
	virtual void Attack();
	virtual void BeingAttack();
	virtual void QTE();
	CREATE_FUNC(MainCharacter);
private:
	Sprite* QTESprite;
	Animation* QTESpriteAnimation;
};

