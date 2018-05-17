#pragma once
#include "cocos2d.h"
#include "Useful.h"
USING_NS_CC;
using namespace Common;
class MainCharacter;
class Slime;
class GameManager;
class character;
class Monster;
class MonsterManager;
class NPCManager;
class GameBase : public Layer
{
public:
	CREATE_FUNC(GameBase);
	static Scene* createScene();		//���ι���
	virtual bool init();				//��ʼ��
	void SetOriginPosint();
	void addPlayer(TMXTiledMap* map);	//�������
	void changeMap(const std::string& MapName);
	void BGInit();						//������ʼ��
	void BGMInit();
	void characterConfig();
	void monsterConfig();
	void npcConfig();
	void UIConfig();
	void setViewPointByPlayer();
	void MapChangeListen();
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);		//����
	bool gameover;
	Sprite* testSprite;					//�����þ���	
	Slime* m_slime[10];					//ʷ��ķ����
	GameManager* _sp;					//��������
	Vec2 OriginPoint;					//���ǳ��ֵ�
private:
	float _top;
	float _bottom;
	float _left;
	float _right;
	Layer* BaseLayer;
	Layer* LogicLayer;
	Layer* uiLayer;
	MainCharacter* m_character;//����
	MonsterManager* monsterManager;
	NPCManager* npcManager;
	TMXTiledMap* m_map;
};

