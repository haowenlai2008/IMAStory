#include "MainCharacter.h"
#include "GameManager.h"
#include "Controller.h"



bool MainCharacter::init()
{
	AttributesInit();
	LoadAction();
	Sprite* sprite = Sprite::create("Knight_R.png");
	sprite->setAnchorPoint(Vec2(0.5, 0));
	Controller* controller = Controller::create();
	sprite->setPosition(getPosition());//ÉèÖÃ×ø±ê
	bindSprite(sprite);
	bindController(controller);
	UIinit();
	//this->setAnchorPoint(Vec2(0.5, 0));
	QTESprite = Sprite::create();
	QTESprite->setPosition(getPosition());
	this->addChild(QTESprite);
	this->scheduleUpdate();
	return true;
}
void MainCharacter::LoadAction()
{
	do
	{
		Animation* animation = Animation::create();
	/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Knight_R_Hit.plist", "Knight_R_Hit.png");*/
		for (int i = 0; i < AttackingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("Knight_R_Hit_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)AttackingFrame * AttackingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "Hit_R");
		Attacking_R = animation;
	} while (false);
	do
	{
		Animation* animation = Animation::create();
		for (int i = 0; i < MovingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("Knight_R_Move_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)MovingFrame * MovingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "Move_R");
		Moving_R = animation;
	} while (false);
	do
	{
		Animation* animation = Animation::create();
	/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Knight_R_Stay.plist", "Knight_R_Stay.png");*/
		for (int i = 0; i < StayingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("Knight_R_Stay_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)StayingFrame * StayingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "Knight_R_Stay");
		Staying_R = animation;
	} while (false);
	do
	{
		Animation* animation = Animation::create();
		/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Knight_R_Hit.plist", "Knight_R_Hit.png");*/
		for (int i = 0; i < QTEFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("Knight_R_QTE_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)QTEFrame * QTESpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "QTE_R");
		QTE_R = animation;
	} while (false);
	do
	{
		Animation* animation = Animation::create();
		/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Knight_R_Hit.plist", "Knight_R_Hit.png");*/
		for (int i = 0; i < BeingAttackingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("Knight_R_Hurt_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)BeingAttackingFrame * BeingAttackingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "Knight_Hurt_R");
		BeingAttacking_R = animation;
	} while (false);

	do
	{
		Animation* animation = Animation::create();
		//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Knight_L_Hit.plist", "Knight_L_Hit.png");
		for (int i = 0; i < 4; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("Skill_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)QTEFrame * QTESpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "QTEA_L");
		QTESpriteAnimation = animation;
	} while (false);
}



void MainCharacter::update(float dt)
{
	GameManager* _sp = GameManager::getInstance();
	if (getIsDead())
		ReLife();
	Flip();//·­×ª
	switch (getState())
	{
	case State::Running:
		if (!isMoving && !isAttacking)
		{
			Move();
		}
		break;
	case State::Attacked:
		if (!isAttacking && !isBeingAttacking)
		{
			Attack();
		}
		break;
	case State::BeingAttacked:
		if (!isBeingAttacking)
		{
			BeingAttack();
			m_Controller->Stay();
		}
		break;
	case State::Staying:
		if (!isMoving && !isAttacking && !isStaying && !isQTE && !isBeingAttacking)
		{
			Stay();
		}
		break;
	case State::QTE:
		if (!isQTE)
		{
			QTE();
		}
		break;
	default:
		break;
	}

	//setViewPointByPlayer();
}



void MainCharacter::AttributesInit()
{
	readDataFromJson();
	MovingFrame = 5;
	StayingFrame = 2;
	AttackingFrame = 4;
	BeingAttackingFrame = 2;
	QTEFrame = 4;
	MovingSpeed = 4.0f;
	StayingSpeed = 2.0f;
	AttackingSpeed = 2.5f;
	BeingAttackingSpeed = 2.0f;
	QTESpeed = 1.5f;
	isMoving = false;
	isStaying = false;
	isAttacking = false;
	isBeingAttacking = false;
	isQTE = false;
	setIsRight(true);
}

void MainCharacter::Move()
{
	Animate* animate = Animate::create(Moving_R);
	auto first = CallFunc::create([this]() {isMoving = true; });
	auto finish = CallFunc::create([this]() {isMoving = false;  });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
}

void MainCharacter::Stay()
{
	stopAllActions();
	Animate* animate = Animate::create(Staying_R);
	auto first = CallFunc::create([this]() {isStaying = true; });
	auto finish = CallFunc::create([this]() {isStaying = false; });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
}

void MainCharacter::Attack()
{
	stopAllActions();
	Animate* animate = Animate::create(Attacking_R);
	auto first = CallFunc::create([this]() {isAttacking = true; });
	auto finish = CallFunc::create(
	[this]() 
	{
		isAttacking = false; 
	});
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
}

void MainCharacter::BeingAttack()
{
	Animate* animate = Animate::create(BeingAttacking_R);
	auto first = CallFunc::create([this]() {isBeingAttacking = true; });
	auto finish = CallFunc::create([this]() {isBeingAttacking = false;  });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);

}

void MainCharacter::QTE()
{
	Animate* animate = Animate::create(QTE_R);
	auto first = CallFunc::create([this]() {QTESprite->setVisible(true); isQTE = true; });
	auto finish = CallFunc::create([this]() {QTESprite->setVisible(false); isQTE = false;  });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
	do
	{
		Animate* animate = Animate::create(QTESpriteAnimation);
		Action* action = Sequence::create(animate, NULL);
		m_sprite->runAction(action);
		QTESprite->runAction(action);
	} while (false);
}
