#include "GameManager.h"
#include "MonsterManager.h"
#include "MissionManager.h"
#include "character.h"
#include "DBUtil.h"
//character* GameManager::m_character = nullptr;
std::string GameManager::musicName[5] = { "MS00.mp3", "MS01.mp3", "MS01.mp3" , "MS01.mp3" , "MS02.mp3" };
GameManager* GameManager::m_gameManager = nullptr;
//MonsterManager* GameManager::monsterManager = nullptr;
//NPCManager* GameManager::npcManager = nullptr;
GameManager::GameManager()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	_top = origin.y + visibleSize.height;
	_bottom = origin.y;
	_left = origin.x;
	_right = origin.x + visibleSize.width;
}


GameManager * GameManager::getInstance()
{
	if (!m_gameManager)
	{
		m_gameManager = new(std::nothrow) GameManager();
		if (!m_gameManager->init())
		{
			CC_SAFE_DELETE(m_gameManager);
			return nullptr;
		}
	}
	return m_gameManager;
}

bool GameManager::init()
{
	this->retain();
	return true;
}


Size GameManager::getMapSize()
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	return Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height);
}

void GameManager::configWithMap(TMXTiledMap * map)
{
	m_map = map;
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	Size mapSize = Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height);
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	_bottom = 0;
	_top = mapSize.height - 400;
	_left = 0;
	_right = mapSize.width;
	log(u8"_left = %f, right = %f", _left, _right);
}

void GameManager::unLoad()
{
	this->release();
}
