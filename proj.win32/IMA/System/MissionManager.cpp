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
	Mission* mission_1 = Mission::create(1, 0, 1, false, u8"�ճ�", u8"�������÷�����˽����趨��\n");
	Mission* mission_2 = Mission::create(2, 0, 5, false, u8"��ʳ", u8"��ʳ���㣬ȥɱ����ʷ��ķ��\n");
	Mission* mission_3 = Mission::create(3, 0, 1, false, u8"��ʧ����÷����", u8"��÷�������ˣ���ȥ���߿���\n");
	Mission* mission_4 = Mission::create(4, 0, 1, false, u8"��ܺ�Ӱ", u8"��ܺ�Ӱ���Ȼ���÷����\n");
	Mission* mission_5 = Mission::create(5, 0, 1, false, u8"����һ��", u8"δ���������ء�������\n");
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
	//������������������ɵ�����
	while (!MissionList.empty() && MissionList.front()->id != GameDataManager::getInstance()->getArchiceData().MissionID)
	{
		log(u8"��ǰ����ID��%d", getMissionID());
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
