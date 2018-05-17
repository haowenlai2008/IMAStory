#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PropertyPage : public Node
{
public:
	CREATE_FUNC(PropertyPage);
	bool init();
	void PropertyUpdate();
private:
	Sprite* box;
	Label* Name;
	Label* HP;
	Label* EXP;
	Label* ATK;
};