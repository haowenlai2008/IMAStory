#pragma once
#include "cocos2d.h"
#include <vector>
USING_NS_CC;
class Monster;
class character;
class CharacterManager;
class Slime;
class MonsterManager : public Node
{
public:
	CREATE_FUNC(MonsterManager);
	CC_SYNTHESIZE(bool, RefreshEnable, RefreshEnable);//是否刷新怪物
	bool init();//初始化
	void update(float dt);//每帧更新
	void loadMonsterList(const std::string& monsterJson);//从Json加载怪物（未实现）
	void LoadBoss();//加载BOSS
	void ButtleSystem();//战斗系统
	void MonsterRefresh(float delta);//怪物刷新
	void clearMonster();//清空怪物
	void LayerSet();
	std::vector<Monster*> MonsterList;//怪物列表
private:
	Monster* m_slime[10];					//史莱姆集合

};

