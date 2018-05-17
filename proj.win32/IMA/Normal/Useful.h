#pragma once
#include "cocos2d.h"
USING_NS_CC;
namespace Common
{
	float Getlength(Vec2 lhs, Vec2 rhs);
}
enum class State
{
	Running,
	Attacked,
	BeingAttacked,
	QTE,
	Staying
};

enum class Dir
{
	DIR_LEFT,
	DIR_RIGHT
};
struct MapMsg
{
	MapMsg(int LeftMapID, int RightMapID, int MonsterID, bool Refresh, const std::string& Name)
	{
		this->LeftMapID = LeftMapID;
		this->RightMapID = RightMapID;
		this->MonsterID = MonsterID;
		this->Refresh = Refresh;
		this->Name = Name;
	}
	int LeftMapID;
	int RightMapID;
	int MonsterID;
	bool Refresh;
	std::string Name;
};

struct ArchiceData
{
	ArchiceData() {};
	ArchiceData(int HP, int Level, int EXP, int MapID, int MissionID, int MissionCount, const std::string& ScripteSign)
	{
		this->HP = HP;
		this->Level = Level;
		this->EXP = EXP;
		this->MapID = MapID;
		this->MissionID = MissionID;
		this->MissionCount = MissionCount;
		this->ScripteSign = ScripteSign;
	}
	int HP;
	int Level;
	int EXP;
	int MapID;
	int MissionID;
	int MissionCount;
	std::string ScripteSign;
};
struct NPCData
{
	NPCData() {};
	NPCData(int ID, int MapID, float position_x, float position_y,bool exist,
		const std::string& Name, const std::string& TextureName)
	{
		this->ID = ID;
		this->MapID = MapID;
		this->position_x = position_x;
		this->position_y = position_y;
		this->exist = exist;
		this->Name = Name;
		this->TextureName = TextureName;
	}
	int ID;
	int MapID;
	float position_x;
	float position_y;
	bool exist;
	std::string Name;
	std::string TextureName;
};