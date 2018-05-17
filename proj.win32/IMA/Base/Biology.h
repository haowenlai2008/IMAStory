#pragma once
#include "cocos2d.h"
//#include "Controller.h"
USING_NS_CC;
class Controller;
class Biology :public Node
{
public:
	CREATE_FUNC(Biology);
	CC_SYNTHESIZE(bool, Dead, IsDead);						//是否死亡
	CC_SYNTHESIZE(bool, FacingRight, IsRight);				//是否朝向右边
	CC_SYNTHESIZE(int, ATK, ATK);							//攻击力
	CC_SYNTHESIZE(int, MaxHP, MaxHP);						//最高生命值
	CC_SYNTHESIZE(int, RealHp, RealHp);						//现存血量
	CC_SYNTHESIZE(int, level, Level);						//等级
	CC_SYNTHESIZE(int, EXP, EXP);							//当前经验值
	CC_SYNTHESIZE(int, MaxEXP, MaxEXP);						//升级所需经验值
	CC_SYNTHESIZE(int, DeadEXP, DeadEXP);					//死亡可获得的经验值
	CC_SYNTHESIZE(Sprite*, m_sprite, Sprite);
	void setName(const std::string& text);					//设置生物名称
	void changeTexture(const std::string & filename);		//更改纹理
	void bindSprite(Sprite* sprite);						//绑定精灵
	void bindController(Controller* controller);			//绑定控制器
	void cure(int hp);										//加血
	void LevelUp();
	void ExpUp(int exp);
	void UIinit();
	void HPUIupdate();
	void EXPUIupdate();
	void receiveDamage(int damage);					//受到伤害
	void LoadAction();								//动作加载						
	void AttributesInit();							//属性初始化
protected:
	Sprite* Blood;											//血条
	Sprite* Blood_Box;
	Sprite* EXP_sprite;											//经验
	Sprite* EXP_Box;
	Controller* m_Controller;								//控制器
	Label* Name;											//名字
	Label* EXPMsg;											//经验信息
	Label* HPMsg;											//生命值信息
};

