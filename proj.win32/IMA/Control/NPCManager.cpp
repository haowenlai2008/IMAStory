#include "NPCManager.h"
#include "GameManager.h"
#include "GameDataManager.h"
#include "NPC.h"
#include "character.h"
#include "Useful.h"
bool NPCManager::init()
{
	this->setPosition(Vec2::ZERO);
	this->scheduleUpdate();
	return true;
}

void NPCManager::update(float delta)
{
	auto m_character = GameManager::getInstance()->getCharacter();
	auto size = GameManager::getInstance()->getMapSize();
	float unit = size.height / 100;
	m_character->setGlobalZOrder(int((size.height - m_character->getPosition().y) / unit));
	for (auto it = NPCList.begin(); it != NPCList.end(); it++)
	{
		(*it)->setGlobalZOrder(int((size.height - (*it)->getPosition().y) / unit));
		if (Common::Getlength((*it)->getPosition(), m_character->getPosition()) < 100)//²â¾àÀë£¬»»Í¼²ã
		{
			(*it)->showTips();
		}
		else
		{
			(*it)->hideTips();
		}
	}
}

void NPCManager::LoadNPC()
{
	UnLoadNPC();
	log(u8"unLoadNPCsucess");
	auto gdm = GameDataManager::getInstance();
	for (auto p : GameDataManager::getInstance()->NPCDataMsg)
	{
		if (p.MapID == GameDataManager::getInstance()->getRecentMapID() && p.exist)
		{
			auto npc = NPC::create(p.ID);
			this->addChild(npc,1);
			NPCList.push_back(npc);
		}
	}
	if (NPCList.size() > 0 && NPCList[0])
	{
		GameManager::getInstance()->setMainheroine(NPCList[0]);
	}
}

void NPCManager::UnLoadNPC()
{
	for (auto it = NPCList.begin(); it != NPCList.end(); it++)
	{
		(*it)->removeFromParent();
		(*it) = nullptr;
		log(u8"Çå³ýnpc");
	}
	NPCList.clear();
}
