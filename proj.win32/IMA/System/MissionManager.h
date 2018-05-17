#pragma once
#include "cocos2d.h"
#include <queue>
#include "Mission.h"
#define MAX_MISSION_NUM (5)//��������
USING_NS_CC;
using std::queue;
class Mission;
class Bottom;
class MissionManager : public Ref
{
public:
	~MissionManager() {
		unLoad();
	}
	static MissionManager* getInstance();//���ʵ��
	bool init();//��ʼ��
	void MissionInit();//�����ʼ��
	void countUp();//��ǰ�������+1
	void missionComPlete();//�������
	void unLoad();
	int getMissionID();//��õ�ǰ����id
	bool getCompleteState();//����������״̬
	queue<Mission*> MissionList;//�������
private:
	MissionManager() {};//��װ
	static MissionManager* m_missionManager;//ʵ��
};