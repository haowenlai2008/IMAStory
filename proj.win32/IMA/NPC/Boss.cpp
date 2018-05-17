#include "Boss.h"
#include "MainCharacter.h"
#include "GameManager.h"
static bool LoadFinish = false;
Animation* Boss::Moving_L = NULL;
Animation* Boss::Moving_R = NULL;
Animation* Boss::Staying_L = NULL;
Animation* Boss::Staying_R = NULL;
Animation* Boss::Attacking_L = NULL;
Animation* Boss::Attacking_R = NULL;
Animation* Boss::BeingAttacking_L = NULL;
Animation* Boss::BeingAttacking_R = NULL;


bool Boss::init()
{
	AttributesInit();
	LoadAction();
	Sprite* sprite = Sprite::create("DarkKnight.png");
	sprite->setAnchorPoint(Vec2(0.5, 0));
	sprite->setPosition(getPosition());
	bindSprite(sprite);
	AddSM();
	setMaxHP(2000);
	setRealHp(2000);
	setDeadEXP(400);
	UIinit();
	//setName(u8"狗管理");
	this->setATK(250);
	this->setAnchorPoint(Vec2(0.5, 0));
	this->scheduleUpdate();
	this->setIsRight(true);
	return true;
}

void Boss::LoadAction()
{
	if (LoadFinish)
		return;
	do
	{
		Animation* animation = Animation::create();
	/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("slime_R_Stay.plist", "slime_R_Stay.png");*/
		for (int i = 0; i < StayingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("DarkKnight_Stay_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)StayingFrame * StayingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "DarkKnight_Stay");
		Boss::Staying_R = animation;
	} while (false);
	do
	{
		Animation* animation = Animation::create();
	/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("slime_R_Hurt.plist", "slime_R_Hurt.png");*/
		for (int i = 0; i < BeingAttackingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("DarkKnight_Hurt_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)BeingAttackingFrame * BeingAttackingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "DarkKnight_Hurt");
		Boss::BeingAttacking_R = animation;
	} while (false);

	do
	{
		Animation* animation = Animation::create();
		/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("slime_R_Hurt.plist", "slime_R_Hurt.png");*/
		for (int i = 0; i < AttackingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("DarkKnight_Attack_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)AttackingFrame * AttackingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "DarkKnight_Hit");
		Boss::Attacking_R = animation;
	} while (false);
	do
	{
		Animation* animation = Animation::create();
		/*	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("slime_R_Hurt.plist", "slime_R_Hurt.png");*/
		for (int i = 0; i < MovingFrame; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("DarkKnight_Move_0%d.png", i));
		}
		animation->setDelayPerUnit(1.0f / ((float)MovingFrame * MovingSpeed));
		animation->setRestoreOriginalFrame(false);
		CCAnimationCache::getInstance()->addAnimation(animation, "DarkKnight_Moving");
		Boss::Moving_R = animation;
	} while (false);
	LoadFinish = true;
}

void Boss::AttributesInit()
{
	StayingFrame = 2;
	BeingAttackingFrame = 1;
	AttackingFrame = 2;
	StayingSpeed = 2;
	MovingFrame = 4;
	StayingSpeed = 2;
	BeingAttackingSpeed = 3.0f;
	AttackingSpeed = 2.5f;
	MovingSpeed = 2;
	isMoving = false;
	isStaying = false;
	isBeingAttacking = false;
	isAttacking = false;
}

void Boss::update(float dt)
{
	auto m_character = GameManager::getInstance()->getCharacter();
	switch (getState())
	{

	case State::BeingAttacked:
		if (!isBeingAttacking)
		{
			BeingAttacking();
			m_SM->Stay();
		}
		break;
	case State::Staying:
		if (!isStaying)
		{
			Stay();
		}
		break;
	case State::Attacked:
		if (!isAttacking)
		{
			Attack();
		}
		break;
	case State::Running:
		if (!isMoving)
		{
			Move();
		}
	default:
		break;
	}

	//怪物攻击部分
	if (getState() == State::Attacked && !m_character->getBeingAttackingState())//攻击条件满足
	{
		RandomHelper random;
		int damage = random.random_int(0, 500);//玄学输出
		float dis = Common::Getlength(getPosition(), m_character->getPosition());
		if (dis < 300)//测攻击距离是否合法
		{
			log("Monster Attack character");
			switch (getDir())//根据方向判断攻击是否成立
			{
			case Dir::DIR_LEFT:
				if (m_character->getPositionX() < getPositionX())
				{
					m_character->setState(State::BeingAttacked);
					m_character->receiveDamage(getATK());
					//MonsterSM::m_character->receiveDamage(damage);
				}
				break;
			case Dir::DIR_RIGHT:
				if (m_character->getPositionX() > getPositionX())
				{
					m_character->setState(State::BeingAttacked);
					m_character->receiveDamage(getATK());
					log(u8"角色受到%d伤害", getATK());
					//MonsterSM::m_character->receiveDamage(damage);
				}
				break;
			default:
				break;
			}
		}
	}
}

void Boss::Stay()
{
	switch (getDir())
	{
	case Dir::DIR_LEFT:
		do
		{
			if (getIsRight())
			{
				m_sprite->setFlippedX(true);
				setIsRight(false);
			}
		} while (false);
		break;
	case Dir::DIR_RIGHT:
		do
		{
			if (!getIsRight())
			{
				m_sprite->setFlippedX(false);
				setIsRight(true);
			}
		} while (false);
		break;
	default:
		break;
	}

	Animate* animate = Animate::create(Boss::Staying_R);
	auto first = CallFunc::create([this]() { isStaying = true; });
	auto finish = CallFunc::create([this]() { isStaying = false; });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
}


void Boss::BeingAttacking()
{
	switch (getDir())
	{
	case Dir::DIR_LEFT:
		do
		{
			if (getIsRight())
			{
				m_sprite->setFlippedX(true);
				setIsRight(false);
			}
		} while (false);
		break;
	case Dir::DIR_RIGHT:
		do
		{
			if (!getIsRight())
			{
				m_sprite->setFlippedX(false);
				setIsRight(true);
			}
		} while (false);
		break;
	default:
		break;
	}
	Animate* animate = Animate::create(Boss::BeingAttacking_R);
	auto first = CallFunc::create([this]() { isBeingAttacking = true; });
	auto finish = CallFunc::create([this]() { isBeingAttacking = false; });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
}

void Boss::Attack()
{
	switch (getDir())
	{
	case Dir::DIR_LEFT:
		do
		{
			if (getIsRight())
			{
				m_sprite->setFlippedX(true);
				setIsRight(false);
			}
		} while (false);
		break;
	case Dir::DIR_RIGHT:
		do
		{
			if (!getIsRight())
			{
				m_sprite->setFlippedX(false);
				setIsRight(true);
			}
		} while (false);
		break;
	default:
		break;
	}
	Animate* animate = Animate::create(Boss::Attacking_R);
	auto first = CallFunc::create([this]() { isAttacking = true; });
	auto finish = CallFunc::create([this]() { isAttacking = false; });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
}

void Boss::Move()
{
	switch (getDir())
	{
	case Dir::DIR_LEFT:
		do
		{
			if (getIsRight())
			{
				m_sprite->setFlippedX(true);
				setIsRight(false);
			}
		} while (false);
		break;
	case Dir::DIR_RIGHT:
		do
		{
			if (!getIsRight())
			{
				m_sprite->setFlippedX(false);
				setIsRight(true);
			}
		} while (false);
		break;
	default:
		break;
	}

	Animate* animate = Animate::create(Boss::Moving_R);
	auto first = CallFunc::create([this]() { isMoving = true; });
	auto finish = CallFunc::create([this]() { isMoving = false; });
	Action* action = Sequence::create(first, animate, finish, NULL);
	m_sprite->runAction(action);
}

void Boss::AddSM()
{
	MonsterSM* SM = MonsterSM::create();
	this->addChild(SM);
	m_SM = SM;
}
