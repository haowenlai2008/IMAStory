#include "GameDataManager.h"
#include <fstream>
#include "GameManager.h"
#include "MissionManager.h"
#include "ScriptManager.h"
#include "character.h"
#include "DBUtil.h"
#include "json.h"
//#include "Useful.h"
#pragma execution_character_set("utf-8")
GameDataManager* GameDataManager::m_dataManager = NULL;
GameDataManager * GameDataManager::getInstance()
{
	if (!m_dataManager)
	{
		m_dataManager = new(std::nothrow) GameDataManager();
		m_dataManager->init();
	}
	return m_dataManager;
}


bool GameDataManager::init()
{
	this->retain();
	readMapData();
	readArchice(0);
	readNPCData();
	dataBaseInit();
	return true;
}

void GameDataManager::writeMapData()
{
	Json::FastWriter writer;
	Json::Value root;
	root["map"][std::move(0)]["left"] = 0xff;
	root["map"][std::move(0)]["right"] = 1;
	root["map"][std::move(0)]["refresh"] = false;
	root["map"][std::move(0)]["MonsterID"] = 0xff;
	root["map"][std::move(0)]["name"] = "Villae.tmx";
	root["map"][std::move(1)]["left"] = 0;
	root["map"][std::move(1)]["right"] = 2;
	root["map"][std::move(1)]["refresh"] = true;
	root["map"][std::move(1)]["MonsterID"] = 1;
	root["map"][std::move(1)]["name"] = "Egg.tmx";
	root["map"][std::move(2)]["left"] = 1;
	root["map"][std::move(2)]["right"] = 3;
	root["map"][std::move(2)]["refresh"] = false;
	root["map"][std::move(2)]["MonsterID"] = 0xff;
	root["map"][std::move(2)]["name"] = "Egg.tmx";
	root["map"][std::move(3)]["left"] = 2;
	root["map"][std::move(3)]["right"] = 0xff;
	root["map"][std::move(3)]["refresh"] = true;
	root["map"][std::move(3)]["MonsterID"] = 1;
	root["map"][std::move(3)]["name"] = "Egg.tmx";
	std::ofstream out("MapData.json", std::ios::binary);
	if (out.is_open())
	{
		std::string data = writer.write(root);
		out << data;
		log("地图数据写入成功");
	}
	else
	{
		log("地图文件打开错误");
	}
	out.close();
}

void GameDataManager::writeArchiceData()
{
	Json::FastWriter writer;
	Json::Value root;
	root["Archice"][std::move(0)]["HP"] = 1000;
	root["Archice"][std::move(0)]["Level"] = 1;
	root["Archice"][std::move(0)]["EXP"] = 100;
	root["Archice"][std::move(0)]["MapID"] = 0;
	root["Archice"][std::move(0)]["MissionID"] = 1;
	root["Archice"][std::move(0)]["MissionCount"] = 0;
	root["Archice"][std::move(0)]["ScriptSign"] = "0000000000";
	std::ofstream out("Archice.json", std::ios::binary);
	if (out.is_open())
	{
		std::string data = writer.write(root);
		out << data;
		log(u8"存档数据写入成功");
	}
	else
	{
		log("存档文件打开错误");
	}
	out.close();
}

void GameDataManager::writeNPCData()
{
	Json::FastWriter writer;
	Json::Value root;
	root["NPC"][std::move(0)]["ID"] = 0;
	root["NPC"][std::move(0)]["MapID"] = 0;
	root["NPC"][std::move(0)]["position_x"] = 600;
	root["NPC"][std::move(0)]["position_y"] = 300;
	root["NPC"][std::move(0)]["exist"] = true;
	root["NPC"][std::move(0)]["Name"] = "Frost";
	root["NPC"][std::move(0)]["TextureName"] = "MainHeroine.png";

	root["NPC"][std::move(1)]["ID"] = 1;
	root["NPC"][std::move(1)]["MapID"] = 2;
	root["NPC"][std::move(1)]["position_x"] = 400;
	root["NPC"][std::move(1)]["position_y"] = 300;
	root["NPC"][std::move(1)]["exist"] = false;
	root["NPC"][std::move(1)]["Name"] = "DarkKnight";
	root["NPC"][std::move(1)]["TextureName"] = "DarkKnight.png";
	std::ofstream out("NPC.json", std::ios::binary);
	if (out.is_open())
	{
		std::string data = writer.write(root);
		out << data;
		log(u8"NPC数据写入成功");
	}
	else
	{
		log("NPC文件打开错误");
	}
	out.close();
}

void GameDataManager::readMapData()
{
	Json::Value root;
	Json::Reader reader;
	std::ifstream in("MapData.json", std::ios::binary);
	mapmsg.clear();
	if (!in.is_open())
	{
		return;
	}
	if (reader.parse(in, root, false) == true)
	{
		int size = root["map"].size();
		for (int i = 0; i < size; i++)
		{
			int left = root["map"][i]["left"].asInt();
			int right = root["map"][i]["right"].asInt();
			int MonsterID = root["map"][i]["MonsterID"].asInt();
			bool refresh = root["map"][i]["refresh"].asBool();
			std::string name = root["map"][i]["name"].asString();
			mapmsg.push_back(MapMsg(left, right, MonsterID, refresh, name));
			log("第%d图: 左:%d, 右:%d, 怪物:%d, refresh:%d, name:%s", i, left, right, MonsterID, refresh, name.c_str());
		}
		log(u8"地图数据读取成功");
	}
	in.close();
}

void GameDataManager::readArchice(int ArchiceNum)
{
	Json::Value root;
	Json::Reader reader;
	std::ifstream in("Archice.json", std::ios::binary);
	if (!in.is_open())
	{
		return;
	}
	if (reader.parse(in, root, false) == true)
	{
		archiceData.HP = root["Archice"][ArchiceNum]["HP"].asInt();
		archiceData.Level = root["Archice"][ArchiceNum]["Level"].asInt();
		archiceData.EXP = root["Archice"][ArchiceNum]["EXP"].asInt();
		archiceData.MapID = root["Archice"][ArchiceNum]["MapID"].asInt();
		archiceData.MissionID = root["Archice"][ArchiceNum]["MissionID"].asInt();
		archiceData.MissionCount = root["Archice"][ArchiceNum]["MissionCount"].asInt();
		archiceData.ScripteSign = root["Archice"][ArchiceNum]["ScriptSign"].asString();
		log("存档读取成功");
	}
	in.close();
}

void GameDataManager::readNPCData()
{
	Json::Value root;
	Json::Reader reader;
	std::ifstream in("NPC.json", std::ios::binary);
	NPCDataMsg.clear();
	if (!in.is_open())
	{
		return;
	}
	if (reader.parse(in, root, false) == true)
	{
		int size = root["NPC"].size();
		for (int i = 0; i < size; i++)
		{
			int id = root["NPC"][i]["ID"].asInt();
			int mapid = root["NPC"][i]["MapID"].asInt();
			float x = root["NPC"][i]["position_x"].asDouble();
			float y = root["NPC"][i]["position_y"].asDouble();
			bool exist = root["NPC"][i]["exist"].asBool();
			string name = root["NPC"][i]["Name"].asString();
			string texture = root["NPC"][i]["TextureName"].asString();
			NPCDataMsg.push_back(NPCData(id, mapid, x, y, exist, name, texture));
		}
		log(u8"NPC数据读取成功");
	}
	in.close();
}

void GameDataManager::ArchiceInit()
{
	writeMapData();
	writeArchiceData();
	writeNPCData();
}
//保存游戏的接口
void GameDataManager::Save()
{
	auto chara = GameManager::getInstance()->getCharacter();
	auto missionM = MissionManager::getInstance();
	auto scriptM = ScriptManager::getInstance();
	if (chara && missionM && scriptM)
	{
		archiceData.Level = chara->getLevel();
		archiceData.HP = chara->getRealHp();
		archiceData.EXP = chara->getEXP();
		archiceData.MapID = getRecentMapID();
		archiceData.MissionID = missionM->getMissionID();
		archiceData.MissionCount = missionM->MissionList.front()->Counter;
		archiceData.ScripteSign = scriptM->ScripteSign.to_string();
	}
	SaveNPCData();
	dataUpdate();
}

void GameDataManager::SaveNPCData()
{
	Json::FastWriter writer;
	Json::Value root;
	for (int i = 0; i < NPCDataMsg.size(); i++)
	{
		root["NPC"][i]["ID"] = NPCDataMsg[i].ID;
		root["NPC"][i]["MapID"] = NPCDataMsg[i].MapID;
		root["NPC"][i]["position_x"] = NPCDataMsg[i].position_x;
		root["NPC"][i]["position_y"] = NPCDataMsg[i].position_y;
		root["NPC"][i]["exist"] = NPCDataMsg[i].exist;
		root["NPC"][i]["Name"] = NPCDataMsg[i].Name;
		root["NPC"][i]["TextureName"] = NPCDataMsg[i].TextureName;
	}
	std::ofstream out("NPC.json", std::ios::binary);
	if (out.is_open())
	{
		std::string data = writer.write(root);
		out << data;
		log(u8"NPC数据保存成功");
	}
	else
	{
		log("NPC文件打开错误");
	}
	out.close();
}

void GameDataManager::dataBaseInit()
{
	
#ifdef DATA_DEBUG

#endif // DATA_DEBUG
}

void GameDataManager::dataUpdate()
{
	Json::FastWriter writer;
	Json::Value root;
	root["Archice"][std::move(0)]["HP"] = archiceData.HP;
	root["Archice"][std::move(0)]["Level"] = archiceData.Level;
	root["Archice"][std::move(0)]["EXP"] = archiceData.EXP;
	root["Archice"][std::move(0)]["MapID"] = archiceData.MapID;
	root["Archice"][std::move(0)]["MissionID"] = archiceData.MissionID;
	root["Archice"][std::move(0)]["MissionCount"] = archiceData.MissionCount;
	root["Archice"][std::move(0)]["ScriptSign"] = archiceData.ScripteSign;
	std::ofstream out("Archice.json", std::ios::binary);
	if (out.is_open())
	{
		std::string data = writer.write(root);
		out << data;
		log(u8"存档数据写入成功");
	}
	else
	{
		log("存档文件打开错误");
	}
	out.close();
}

//读取数据
void GameDataManager::dataReset()
{
	readMapData();
	readArchice(0);
	readNPCData();
	dataUpdate();
}

void GameDataManager::toLeft()
{
	if (archiceData.MapID > 0)
		archiceData.MapID -= 1;
}

void GameDataManager::toRight()
{
	if (archiceData.MapID < 3)
		archiceData.MapID += 1;
}

void GameDataManager::unLoad()
{
	this->release();
}

bool GameDataManager::getMonsterRefreshState()
{
	return mapmsg[archiceData.MapID].Refresh;
}

int GameDataManager::getLessMapID()
{
	return 0;
}

int GameDataManager::getMaxMapID()
{
	return mapmsg.size() - 1;
}

int GameDataManager::getRecentMapID()
{
	return archiceData.MapID;
}

int GameDataManager::getLeftMapID()
{
	return mapmsg[getRecentMapID()].LeftMapID;
}

int GameDataManager::getRightMapID()
{
	return mapmsg[getRecentMapID()].RightMapID;
}

std::string & GameDataManager::getRecentMap()
{
	return mapmsg[archiceData.MapID].Name;
}

std::string & GameDataManager::getLeftMap()
{
	return mapmsg[getLeftMapID()].Name;
}

std::string & GameDataManager::getRightMap()
{
	return mapmsg[getRightMapID()].Name;
}

std::string & GameDataManager::getMonsterName()
{
	//return mapmsg[archiceData.MapID].MonsterID
	return std::string();
}

ArchiceData GameDataManager::getArchiceData()
{
	return archiceData;
}

NPCData GameDataManager::getNPCData(int ID)
{
	if (ID >= NPCDataMsg.size() || ID < 0)
		return NPCData();
	return NPCDataMsg[ID];
}

