#ifndef HELLO_H_
#define HELLO_H_
#include "cocos2d.h"
using namespace cocos2d;
class hello:public Layer
{
public:
	
	static Scene* createScene();
	static void SetFinalPoint(Vec2 finalPoint);
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuRestartCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(hello);
private:
	static Vec2 FinalPoint;
};
#endif // ! 
