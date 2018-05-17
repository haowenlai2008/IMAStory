#pragma once
#include "cocos2d.h"
#include <queue>
#include "Mission.h"
#define MAX_MISSION_NUM (5)//任务数量
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
	static MissionManager* getInstance();//获得实例
	bool init();//初始化
	void MissionInit();//任务初始化
	void countUp();//当前任务计数+1
	void missionComPlete();//完成任务
	void unLoad();
	int getMissionID();//获得当前任务id
	bool getCompleteState();//获得任务完成状态
	queue<Mission*> MissionList;//任务队列
private:
	MissionManager() {};//封装
	static MissionManager* m_missionManager;//实例
};