#ifndef HELLO_H_
#define HELLO_H_
#include "cocos2d.h"
using namespace cocos2d;
class helloworld :public Layer
{
public:
	static Scene* createScene();					//��̬���������ķ���
	virtual bool init();							//��ʼ��
	void menuCloseCallback(cocos2d::Ref* pSender);	//�˵���Ļص�����
	CREATE_FUNC(helloworld);
};
#endif // ! 
