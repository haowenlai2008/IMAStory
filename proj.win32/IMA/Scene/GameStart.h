#pragma once
#include "cocos2d.h"

#define length (visibleSize.width / 12)
using namespace cocos2d;
class GameStart:Layer
{
public:
	
	GameStart();
	~GameStart();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameStart);
	
private:
	int matrixSize;
	int gameLevel;
	FILE* file;
	Vec2 origin;
	Vec2 originPoint;
	Size visibleSize;
	bool gameOver;
	bool matrix[10][10];
	Sprite* spriteMatrix[10][10];
	void createListener();
	void click(Event *event);
	void menuBackcall(Ref* pSender);
	void paint();
	void readLevel();
	void resetMatrix();
};

