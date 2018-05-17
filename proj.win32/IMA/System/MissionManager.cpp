#include "MissionManager.h"
#include "GameDataManager.h"
#include "Mission.h"
#include "Bottom.h"
MissionManager* MissionManager::m_missionManager = nullptr;
MissionManager * MissionManager::getInstance()
{
	if (!m_missionManager)
	{
		m_missionManager = new (std::nothrow)MissionManager();
		if (!m_missionManager->init())
		{
			return nullptr;
		}
		m_missionManager->autorelease();
	}
	return m_missionManager;
}
bool MissionManager::init()
{
	this->retain();
	MissionInit();
	return true;
}

void MissionManager::MissionInit()
{
	Mission* mission_1 = Mission::create(1, 0, 1, false, u8"日常", u8"找你的青梅竹马了解下设定吧\n");
	Mission* mission_2 = Mission::create(2, 0, 5, false, u8"粮食", u8"粮食不足，去杀几个史莱姆吧\n");
	Mission* mission_3 = Mission::create(3, 0, 1, false, u8"消失的青梅竹马", u8"青梅竹马不见了？快去东边看看\n");
	Mission* mission_4 = Mission::create(4, 0, 1, false, u8"打败黑影", u8"打败黑影，救回青梅竹马\n");
	Mission* mission_5 = Mission::create(5, 0, 1, false, u8"连接一切", u8"未来会怎样呢。。。。\n");
	mission_1->retain();
	mission_2->retain();
	mission_3->retain();
	mission_4->retain();
	mission_5->retain();
	MissionList.push(mission_1);
	MissionList.push(mission_2);
	MissionList.push(mission_3);
	MissionList.push(mission_4);
	MissionList.push(mission_5);
	//根据任务进度完成已完成的任务
	while (!MissionList.empty() && MissionList.front()->id != GameDataManager::getInstance()->getArchiceData().MissionID)
	{
		log(u8"当前任务ID是%d", getMissionID());
		missionComPlete();
	}
	if (!MissionList.empty())
		MissionList.front()->Counter = GameDataManager::getInstance()->getArchiceData().MissionCount;
}

void MissionManager::countUp()
{
	if (!MissionList.empty())
	{
		MissionList.front()->countUp();
	}
}


void MissionManager::missionComPlete()
{
	if (!MissionList.empty())
	{
		MissionList.front()->release();
		MissionList.front() = nullptr;
		MissionList.pop();
	}
		
}

void MissionManager::unLoad()
{
	while (!MissionList.empty())
	{
		missionComPlete();
	}
	this->release();
}

int MissionManager::getMissionID()
{
	if (!MissionList.empty())
		return MissionList.front()->id;
	else
		return 0;
}

bool MissionManager::getCompleteState()
{
	return MissionList.front()->isComplete;
}
