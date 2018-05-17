#ifndef HELLO_H_
#define HELLO_H_
#include "cocos2d.h"
using namespace cocos2d;
class helloworld :public Layer
{
public:
	static Scene* createScene();					//静态创建场景的方法
	virtual bool init();							//初始化
	void menuCloseCallback(cocos2d::Ref* pSender);	//菜单项的回调函数
	CREATE_FUNC(helloworld);
};
#endif // ! 
