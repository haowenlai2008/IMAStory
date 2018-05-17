#pragma once
#include "cocos2d.h"
#include "Biology.h"
#include "Useful.h"
USING_NS_CC;

class NPC : public Biology
{
public:
	CREATE_FUNC(NPC);
	static NPC* create(int ID);
	bool init(); 
	void showTips();
	void hideTips();
	void listenInit();
	bool LoadData(int ID);
	void onKeyDown(EventKeyboard::KeyCode keyCode, Event * event);
private:
	Sprite* Tips;
	NPCData npcData;
};
