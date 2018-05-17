#pragma once
#ifndef _THIRDSCENE_H
#define _THIRDSCENE_H
 // !_THIRDSCENE_H
#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "ui/UIScale9Sprite.h"
#include "cocos2d.h"
using namespace cocos2d;
class Help :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Help);
	void ComeHome(Ref* pSender);
};
#endif

