#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define MIUSIC_NUM (5)
class character;
class MonsterManager;
class NPCManager;
class MissionPage;
class NPC;
class Monster;
class GameManager : public Ref
{
public:
	CC_SYNTHESIZE(Layer*, m_Layer, Layer);
	CC_SYNTHESIZE(character*, m_character, Character);
	CC_SYNTHESIZE(NPC*, m_Mainheroine, Mainheroine);
	CC_SYNTHESIZE(Monster*, m_Boss, Boss);
	CC_SYNTHESIZE(MonsterManager*, monsterManager, MonsterManager);
	CC_SYNTHESIZE(NPCManager*, npcManager, NPCManager);
	CC_SYNTHESIZE(MissionPage*, missionManager, MissionPage);
	static GameManager* getInstance();
	bool init();
	Size getMapSize();
	void configWithMap(TMXTiledMap* map);
	void unLoad();
	~GameManager() { this->unLoad(); };
	float _top;
	float _bottom;
	float _left;
	float _right;
	static std::string musicName[5];
private:
	TMXTiledMap* m_map;
	static GameManager* m_gameManager;
	GameManager();
};

