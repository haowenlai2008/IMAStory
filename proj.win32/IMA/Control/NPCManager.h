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
	void LoadNPC();//����NPC
	void UnLoadNPC();//��յ�ǰNPC
	std::vector<NPC*> NPCList;//NPC�б�
};