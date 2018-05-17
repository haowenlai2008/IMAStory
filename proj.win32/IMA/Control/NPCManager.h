#pragma once
#include "cocos2d.h"
USING_NS_CC;
class NPC;
class NPCManager : public Node
{
public:
	CREATE_FUNC(NPCManager);
	bool init();
	void update(float delta);
	void LoadNPC();//加载NPC
	void UnLoadNPC();//清空当前NPC
	std::vector<NPC*> NPCList;//NPC列表
};