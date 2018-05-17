#pragma once
#include "cocos2d.h"
USING_NS_CC;
using std::string;
class Mission : public Ref
{
public:
	static Mission* create(int id, int Counter, int Targetnum, bool isComplete, const string& MissionName, const string& Script);
	Mission(int id, int Counter, int Targetnum, bool isComplete, const string& MissionName, const string& Script);
	void countUp();//计数+1
	int id;//任务id
	int Counter;//任务计数
	int Targetnum;//完成任务所需计数
	bool isComplete;//任务是否完成
	string MissionName;//任务名
	string Script;//描述
};