#pragma once
#include "cocos2d.h"
#include "Useful.h"
#include <map>
#define DATA_DEBUG
USING_NS_CC;
//���ݹ���Ա
class GameDataManager : public Ref
{
public:
	~GameDataManager() { this->unLoad(); };
	static GameDataManager* getInstance();//���ʵ��
	bool init();//��ʼ��
	void writeMapData();
	void writeArchiceData();
	void writeNPCData();
	void readMapData();
	void readArchice(int ArchiceNum);
	void readNPCData();
	void ArchiceInit();
	void Save();
	void SaveNPCData();
	void dataBaseInit();//���ݿ��ʼ��
	void dataUpdate();//���ݸ���
	void dataReset();//���ݳ�ʼ��
	void toLeft();
	void toRight();
	void unLoad();
	bool getMonsterRefreshState();
	int getLessMapID();
	int getMaxMapID();
	int getRecentMapID();
	int getLeftMapID();
	int getRightMapID();
	std::string& getRecentMap();
	std::string& getLeftMap();
	std::string& getRightMap();
	std::string& getMonsterName();
	ArchiceData getArchiceData();
	NPCData getNPCData(int ID);
	std::vector<NPCData> NPCDataMsg;
private:
	std::vector<MapMsg> mapmsg;
	ArchiceData archiceData;
	GameDataManager() {};
	GameDataManager(const GameDataManager& lhs) {};
	GameDataManager& operator=(const GameDataManager& lhs) {};
	static GameDataManager* m_dataManager;//ʵ��ָ��
};

