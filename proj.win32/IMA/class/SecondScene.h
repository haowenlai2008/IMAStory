#ifndef _SECONDSCENE_H_
#define _SECONDSCENE_H_
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::ui;
class SecondScene : public Layer
{
public:
	static Scene* createScene();//�����������س���ָ��
	virtual bool init();//������ʼ��
	CREATE_FUNC(SecondScene);//����������
private:
	SnakeNode* spHead;//��ͷ
	Sprite* spfood;//ʳ��ָ��
	Vector<Sprite* > allbody;//����
	int m_score;//����
	void SnakeMove(float delta);//�ߵ��ƶ�
	void Setmenu();//���ò˵�
	void popScene(Ref* pSender);//�л��˵��ص�����
	void SetScoreLabel();//���üƷ���
	void setBackGround();//��OpenGL������
	void creatsnake();//��ʼ������
	void setListener();//���ü��̼���
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//�ͷŰ����ص�����
	void GameOver();//��Ϸ�����¼�
	bool DirChange;//�жϷ����Ƿ�ı��һ��
	bool TouchSnake(float x, float y);//�ж������Ƿ���ĳ�ڵ��غ�
	bool Nodetouch(Point first, Point second);//�ж������غ�
};
#endif // !_SECONDSCENE_H_


