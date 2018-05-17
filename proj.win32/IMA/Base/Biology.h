#pragma once
#include "cocos2d.h"
//#include "Controller.h"
USING_NS_CC;
class Controller;
class Biology :public Node
{
public:
	CREATE_FUNC(Biology);
	CC_SYNTHESIZE(bool, Dead, IsDead);						//�Ƿ�����
	CC_SYNTHESIZE(bool, FacingRight, IsRight);				//�Ƿ����ұ�
	CC_SYNTHESIZE(int, ATK, ATK);							//������
	CC_SYNTHESIZE(int, MaxHP, MaxHP);						//�������ֵ
	CC_SYNTHESIZE(int, RealHp, RealHp);						//�ִ�Ѫ��
	CC_SYNTHESIZE(int, level, Level);						//�ȼ�
	CC_SYNTHESIZE(int, EXP, EXP);							//��ǰ����ֵ
	CC_SYNTHESIZE(int, MaxEXP, MaxEXP);						//�������辭��ֵ
	CC_SYNTHESIZE(int, DeadEXP, DeadEXP);					//�����ɻ�õľ���ֵ
	CC_SYNTHESIZE(Sprite*, m_sprite, Sprite);
	void setName(const std::string& text);					//������������
	void changeTexture(const std::string & filename);		//��������
	void bindSprite(Sprite* sprite);						//�󶨾���
	void bindController(Controller* controller);			//�󶨿�����
	void cure(int hp);										//��Ѫ
	void LevelUp();
	void ExpUp(int exp);
	void UIinit();
	void HPUIupdate();
	void EXPUIupdate();
	void receiveDamage(int damage);					//�ܵ��˺�
	void LoadAction();								//��������						
	void AttributesInit();							//���Գ�ʼ��
protected:
	Sprite* Blood;											//Ѫ��
	Sprite* Blood_Box;
	Sprite* EXP_sprite;											//����
	Sprite* EXP_Box;
	Controller* m_Controller;								//������
	Label* Name;											//����
	Label* EXPMsg;											//������Ϣ
	Label* HPMsg;											//����ֵ��Ϣ
};

