#include "MonsterManager.h"
#include "GameManager.h"
#include "GameDataManager.h"
#include "MainCharacter.h"
#include "MissionManager.h"
#include "ScriptManager.h"
#include "MissionPage.h"
#include "Slime.h"
#include "Useful.h"
#include "Monster.h"
#include "Boss.h"

//MonsterManager* MonsterManager::m_pM = NULL;


bool MonsterManager::init()
{
	//MonsterSM::bindCharacter(CharacterManager::getInstance()->getCharacter());
	setRefreshEnable(true);
	loadMonsterList("");
	this->setPosition(Vec2::ZERO);
	this->schedule(schedule_selector(MonsterManager::MonsterRefresh), 4.0f);
	this->scheduleUpdate();
	return true;
}

void MonsterManager::update(float dt)
{
	ButtleSystem();
	LayerSet();
}

//void MonsterManager::setCharater(character * target)
//{
//	m_character = target;
//}

void MonsterManager::loadMonsterList(const std::string & monsterJson)
{
	/*在这里添加Boss*/
	for (int i = 0; i < 10; i++)
		MonsterList.push_back(NULL);
}

void MonsterManager::LoadBoss()
{
	auto boss = Boss::create();
	boss->setPosition(400, 300);
	boss->setEnable(false);
	GameManager::getInstance()->setBoss(boss);
	MonsterList[0] = boss;
	this->addChild(boss, 2);
}

void MonsterManager::ButtleSystem()
{
	auto m_character = GameManager::getInstance()->getCharacter();
	auto m_Boss = GameManager::getInstance()->getBoss();
	auto missionManager = MissionManager::getInstance();
	auto missionPage = GameManager::getInstance()->getMissionPage();
	auto sm = ScriptManager::getInstance();
	if (m_character == nullptr)
		return;
	auto visualSize = Director::getInstance()->getVisibleSize();
	//m_character->setGlobalZOrder(1 + m_character->getGlobalZOrder() + (visualSize.height - m_character->getPositionY()) / 100);
	for (auto it = MonsterList.begin(); it != MonsterList.end(); it++)
	{
		if (!(*it))//该位置无怪物
		{
			continue;
		}
		if ((*it)->getIsDead())//怪物死亡
		{
			if ((*it) == m_Boss && missionManager->getMissionID() == 4)
			{
				missionManager->countUp();
				missionPage->missionScriptUpdate();
				missionManager->missionComPlete();
				sm->pushSentence(3);
			}
			if (missionManager->getMissionID() == 2)
			{
				missionManager->countUp();
				missionPage->missionScriptUpdate();
			}
			m_character->ExpUp((*it)->getDeadEXP());
			(*it)->removeFromParent();
			(*it) = NULL;
			continue;
		}
		if (m_character->getState() == State::Attacked && !(*it)->getBeingAttackingState() && (*it)->getEnable())//攻击条件满足
		{
			RandomHelper random;
			int damage = random.random_int(0, 500);//玄学输出
			float dis = Common::Getlength((*it)->getPosition(), m_character->getPosition());
			if (dis < 250)//测攻击距离是否合法
			{
				log("character Attack Monster");
				switch (m_character->getDir())//根据方向判断攻击是否成立
				{
				case Dir::DIR_LEFT:
					if ((*it)->getPositionX() < m_character->getPositionX())
					{
						(*it)->setState(State::BeingAttacked);
						(*it)->receiveDamage(m_character->getATK());
						//(*it)->receiveDamage(damage);
					}
					break;
				case Dir::DIR_RIGHT:
					if ((*it)->getPositionX() > m_character->getPositionX())
					{
						(*it)->setState(State::BeingAttacked);
						(*it)->receiveDamage(m_character->getATK());
					}
					break;
				default:
					break;
				}
			}
		}
		//怪物攻击部分
	}
}

void MonsterManager::MonsterRefresh(float delta)
{
	if (GameDataManager::getInstance()->getMonsterRefreshState() == true)
	{
		for (auto it = MonsterList.begin(); it != MonsterList.end(); it++)
		{
			if (!(*it))
			{
				RandomHelper random;
				float x = random.random_real(GameManager::getInstance()->_left, GameManager::getInstance()->_right);
				float y = random.random_real(GameManager::getInstance()->_bottom, GameManager::getInstance()->_top);
				(*it) = Slime::create();
				(*it)->setPosition(Vec2(x, y));
				GameManager::getInstance()->getLayer()->addChild((*it));
			}
		}
	}
}

void MonsterManager::clearMonster()
{
	for (auto it = MonsterList.begin(); it != MonsterList.end(); it++)
	{
		if ((*it))
		{
			(*it)->removeFromParent();
			(*it) = nullptr;
		}
	}
}

void MonsterManager::LayerSet()
{
	auto m_character = GameManager::getInstance()->getCharacter();
	auto height = GameManager::getInstance()->_top;
	auto unit = height / 100;
	for (auto it = MonsterList.begin(); it != MonsterList.end(); it++)
	{
		if (!(*it))//该位置无怪物
		{
			continue;
		}
		auto layerOrder = int((height - (*it)->getPositionY()) / unit);
		layerOrder = layerOrder < 1 ? 1 : layerOrder;
		(*it)->setLocalZOrder(layerOrder);
	}
	auto layerOrder = int((height - m_character->getPositionY()) / unit);
	layerOrder = layerOrder < 1 ? 1 : layerOrder;
	m_character->setLocalZOrder(layerOrder);
}

//MonsterManager * MonsterManager::getInstance()
//{
//	if (m_pM == NULL)
//	{
//		m_pM = MonsterManager::create();
//	}
//	return m_pM;
//}
