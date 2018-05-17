#pragma once
#include "cocos2d.h"
#include "Useful.h"
USING_NS_CC;
using namespace Common;
class MainCharacter;
class Slime;
class GameManager;
class character;
class Monster;
class MonsterManager;
class NPCManager;
class GameBase : public Layer
{
public:
	CREATE_FUNC(GameBase);
	static Scene* createScene();		//二次构建
	virtual bool init();				//初始化
	void SetOriginPosint();
	void addPlayer(TMXTiledMap* map);	//添加主角
	void changeMap(const std::string& MapName);
	void BGInit();						//背景初始化
	void BGMInit();
	void characterConfig();
	void monsterConfig();
	void npcConfig();
	void UIConfig();
	void setViewPointByPlayer();
	void MapChangeListen();
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);		//更新
	bool gameover;
	Sprite* testSprite;					//测试用精灵	
	Slime* m_slime[10];					//史莱姆集合
	GameManager* _sp;					//场景参数
	Vec2 OriginPoint;					//主角出现点
private:
	float _top;
	float _bottom;
	float _left;
	float _right;
	Layer* BaseLayer;
	Layer* LogicLayer;
	Layer* uiLayer;
	MainCharacter* m_character;//主角
	MonsterManager* monsterManager;
	NPCManager* npcManager;
	TMXTiledMap* m_map;
};

