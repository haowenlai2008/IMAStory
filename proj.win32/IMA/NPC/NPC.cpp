#include "NPC.h"
#include "GameDataManager.h"
#include "ScriptManager.h"
NPC * NPC::create(int ID)
{
	NPC *npc = new (std::nothrow) NPC();
	if (npc && npc->LoadData(ID) && npc->init())
	{
		npc->autorelease();
		return npc;
	}
	CC_SAFE_DELETE(npc);
	return nullptr;
}
bool NPC::init()
{
	
	Tips = Sprite::create("tips.png");
	Tips->setPosition(Vec2(100,300));
	/*Tips->setPosition(Vec2(m_sprite->getContentSize().width, m_sprite->getContentSize().height));*/
	this->addChild(Tips, 1);
	listenInit();
	return true;
}

void NPC::showTips()
{
	if (Tips)
	{
		Tips->setVisible(true);
	}
}

void NPC::hideTips()
{
	if (Tips)
	{
		Tips->setVisible(false);
	}
}

void NPC::listenInit()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(NPC::onKeyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool NPC::LoadData(int ID)
{
	auto gm = GameDataManager::getInstance();
	this->npcData = gm->getNPCData(ID);
	this->setPosition(Vec2(npcData.position_x, npcData.position_y));
	if (m_sprite)
	{
		this->m_sprite->setTexture(npcData.TextureName);
	}
	else
	{
		bindSprite(Sprite::create(npcData.TextureName));
	}
	return true;
}

void NPC::onKeyDown(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (Tips->isVisible() && keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		ScriptManager::getInstance()->pushSentence(0, npcData.ID);
	}
}
