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
    
	void menuGameStartcallback(Ref* pSender);//��ʼ����Ϸ
	void menuGameContinuecallback(Ref* pSender);//������Ϸ
    void menuCloseCallback(Ref* pSender);//�ر���Ϸ
    
    CREATE_FUNC(HelloWorld);

	
};

#endif // __HELLOWORLD_SCENE_H__
