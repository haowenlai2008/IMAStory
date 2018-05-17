#pragma once
#include "cocos2d.h"
#include <vector>
USING_NS_CC;
class Monster;
class character;
class CharacterManager;
class Slime;
class MonsterManager : public Node
{
public:
	CREATE_FUNC(MonsterManager);
	CC_SYNTHESIZE(bool, RefreshEnable, RefreshEnable);//�Ƿ�ˢ�¹���
	bool init();//��ʼ��
	void update(float dt);//ÿ֡����
	void loadMonsterList(const std::string& monsterJson);//��Json���ع��δʵ�֣�
	void LoadBoss();//����BOSS
	void ButtleSystem();//ս��ϵͳ
	void MonsterRefresh(float delta);//����ˢ��
	void clearMonster();//��չ���
	void LayerSet();
	std::vector<Monster*> MonsterList;//�����б�
private:
	Monster* m_slime[10];					//ʷ��ķ����

};

