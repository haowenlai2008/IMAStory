#ifndef GAMEOVER_H_
#define GAMEOVER_H_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "ui/UIScale9Sprite.h"
#include "SnakeNode.h"
#include "SecondScene.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class GameOver: public Layer
{
public:
	int score;
	GameOver();
	~GameOver();
	static Scene* createScene();
	virtual bool init();
	void popScene(Ref* pSender);
	CREATE_FUNC(GameOver);
};

#endif // !GAMEOVER_H_