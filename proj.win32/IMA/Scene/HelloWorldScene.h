#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	Vec2 origin;
	Size visibleSize;
    virtual bool init();
    
	void menuGameStartcallback(Ref* pSender);//开始新游戏
	void menuGameContinuecallback(Ref* pSender);//继续游戏
    void menuCloseCallback(Ref* pSender);//关闭游戏
    
    CREATE_FUNC(HelloWorld);

	
};

#endif // __HELLOWORLD_SCENE_H__
