#include "GameBase.h"
#include "SimpleAudioEngine.h"
#include "UILayer.h"
#include "Useful.h"
#include "hello.h"
#include "Box2DTestLayer.h"
#include "GameManager.h"
#include "GameDataManager.h"
#include "MonsterManager.h"
#include "NPCManager.h"
#include "MissionManager.h"
#include "MissionPage.h"
#include "ScriptManager.h"
#include "MainCharacter.h"
#include "Boss.h"
#include "DBUtil.h"
#include "lua.h"
#include "kaguya\kaguya.hpp"

USING_NS_CC;

//二次构建
Scene* GameBase::createScene()
{
	auto scene = Scene::create();
	auto layer2 = UILayer::create();
	scene->addChild(layer2, 3);
	auto layer = GameBase::create();
	layer->LogicLayer = layer;
	GameManager::getInstance()->setLayer(layer);
	scene->addChild(layer);
	return scene;
}

//初始化
bool GameBase::init()
{
	if (!Layer::init())
	{
		return false;
	}
	BGInit();
	BGMInit();
	monsterConfig();
	npcConfig();
	characterConfig();
	this->scheduleUpdate();
	changeMap(GameDataManager::getInstance()->getRecentMap());
	return true;
}
void GameBase::SetOriginPosint()
{
	OriginPoint = Vec2(UserDefault::getInstance()->getFloatForKey("Final_X"), UserDefault::getInstance()->getFloatForKey("Final_Y"));
}
//添加主角
void GameBase::addPlayer(TMXTiledMap * map)
{
	m_character = MainCharacter::create();
	m_character->setPosition(OriginPoint);
	this->addChild(m_character,2);
}
void GameBase::changeMap(const std::string & MapName)
{
	auto gm = GameManager::getInstance();
	auto gdm = GameDataManager::getInstance();
	auto monsterManager = gm->getMonsterManager();
	auto scriptM = ScriptManager::getInstance();
	auto missionManager = MissionManager::getInstance();
	auto missionPage = gm->getMissionPage();
	if (m_map)
	{
		m_map->removeFromParent();
		m_map = nullptr;
		if (monsterManager)
		{
			monsterManager->clearMonster();
		}
		log(u8"角色渲染层级:%d", m_character->getLocalZOrder());
	}
	m_map = TMXTiledMap::create(MapName);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(GameManager::musicName[gdm->getRecentMapID()].c_str(),true);
	GameManager::getInstance()->configWithMap(m_map);
	m_map->setPosition(m_map->getPosition() + Director::getInstance()->getVisibleOrigin());
	this->addChild(m_map, 0);
	//任务剧情
	if (!scriptM->ScripteSign[2] && gdm->getRecentMapID() == 0 && ((missionManager->getMissionID() == 2 && missionManager->getCompleteState()) || missionManager->getMissionID() == 3))
	{
		gdm->NPCDataMsg[0].exist = false;
		log("1_npcExist = %d, name = %s", gdm->NPCDataMsg[0].exist, gdm->NPCDataMsg[0].Name.c_str());
		//npcManager->LoadNPC();
		scriptM->pushSentence(1);
		scriptM->ScripteSign[2] = true;//设置事件已经完成
		if (missionManager->getMissionID() == 2)
			missionManager->missionComPlete();
	}
	//任务3
	if ((gdm->getRecentMapID() == 2 && (missionManager->getMissionID() == 3  || missionManager->getMissionID() == 4))&& !missionManager->getCompleteState())
	{
		gdm->NPCDataMsg[0].exist = true;
		gdm->NPCDataMsg[0].TextureName = "MainHeroine2.png";
		gdm->NPCDataMsg[0].MapID = 2;
		monsterManager->LoadBoss();
		if (missionManager->getMissionID() == 3)
			missionManager->missionComPlete();
		if (!scriptM->ScripteSign[3])
		{
			scriptM->pushSentence(2);
			scriptM->ScripteSign[3] = true;
		}
		else
		{
			gm->getBoss()->setEnable(true);
		}
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(GameManager::musicName[4].c_str(),true);
		//设置事件已经完成
	}
}
//背景初始化
void GameBase::BGInit()
{
	m_map = TMXTiledMap::create(GameDataManager::getInstance()->getRecentMap());
	m_map->setPosition(m_map->getPosition() + Director::getInstance()->getVisibleOrigin());
	GameManager::getInstance()->configWithMap(m_map);
	this->addChild(m_map,0);
	
}



void GameBase::BGMInit()
{
	for (int i = 0; i < MIUSIC_NUM; i++)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(GameManager::musicName[i].c_str());
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(GameManager::musicName[GameDataManager::getInstance()->getRecentMapID()].c_str());
}

void GameBase::menuCloseCallback(Ref* pSender)
{
	Scene* game = GameBase::createScene();
	Director::getInstance()->purgeCachedData();
	Director::getInstance()->replaceScene(game);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void GameBase::update(float dt)
{
	MapChangeListen();
	setViewPointByPlayer();
	hello::SetFinalPoint(m_character->getPosition());
}


void GameBase::characterConfig()
{
	GameManager::getInstance()->setCharacter(m_character = MainCharacter::create());
	this->addChild(m_character,2);
}

void GameBase::monsterConfig()
{
	GameManager::getInstance()->setMonsterManager(monsterManager = MonsterManager::create());
	this->addChild(monsterManager, 2);
}

void GameBase::npcConfig()
{
	GameManager::getInstance()->setNPCManager(npcManager = NPCManager::create());
	this->addChild(npcManager, 1);
	npcManager->LoadNPC();
}

void GameBase::UIConfig()
{
}

void GameBase::setViewPointByPlayer()
{
	if (m_character == NULL)
	{
		return;
	}
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	Size mapSize = Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 spritePos = m_character->getPosition();

	float x = spritePos.x > visibleSize.width / 2 ? spritePos.x : visibleSize.width / 2;
	float y = spritePos.y > visibleSize.height / 2 ? spritePos.y : visibleSize.height / 2;

	float x2 = x > (mapSize.width - visibleSize.width / 2) ? (mapSize.width - visibleSize.width / 2) : x;
	float y2 = y > (mapSize.height - visibleSize.height / 2) ? (mapSize.height - visibleSize.height / 2) : y;


	Vec2 destPos(x2, y2);
	Vec2 centerPos(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 viewPos = centerPos - destPos;

	LogicLayer->setPosition(viewPos);
}

void GameBase::MapChangeListen()
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto gm = GameManager::getInstance();
	auto gdm = GameDataManager::getInstance();
	if (m_character->getIsRight() && m_character->getPositionX() > GameManager::getInstance()->_right && GameDataManager::getInstance()->getRightMapID() != 0xff)
	{
		GameDataManager::getInstance()->toRight();
		changeMap(GameDataManager::getInstance()->getRecentMap());
		m_character->setPosition(Vec2(origin.x + 20, m_character->getPositionY()));
		npcManager->LoadNPC();
	}

	if (!m_character->getIsRight() && m_character->getPositionX() < origin.x && GameDataManager::getInstance()->getLeftMapID() != 0xff)
	{
		
		GameDataManager::getInstance()->toLeft();
		changeMap(GameDataManager::getInstance()->getRecentMap());
		log("2_npcExist = %d, name = %s", gdm->NPCDataMsg[0].exist, gdm->NPCDataMsg[0].Name.c_str());
		m_character->setPosition(Vec2(origin.x + gm->_right - 20, m_character->getPositionY()));
		npcManager->LoadNPC();
	}
}





