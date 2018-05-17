#pragma once
#include "cocos2d.h"
#include <queue>
#include "Mission.h"
USING_NS_CC;
using std::queue;
class Mission;
class Bottom;
class MissionManager;
class MissionPage : public Node
{
public:
	CREATE_FUNC(MissionPage);
	bool init();
	void UIInit();
	void missionScriptUpdate();
	Size getBoxSize();
	void menu_Complete(Ref* pSender);
private:
	MissionManager* missionManager;
	Sprite* Box;
	Sprite* MissionBox;
	Bottom* CompleteBottom;
	Label* MissionCompleteTest;
	LabelTTF* MissionName;
	LabelTTF* MissionScript;
};