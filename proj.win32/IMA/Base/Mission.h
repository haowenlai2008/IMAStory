#pragma once
#include "cocos2d.h"
USING_NS_CC;
using std::string;
class Mission : public Ref
{
public:
	static Mission* create(int id, int Counter, int Targetnum, bool isComplete, const string& MissionName, const string& Script);
	Mission(int id, int Counter, int Targetnum, bool isComplete, const string& MissionName, const string& Script);
	void countUp();//����+1
	int id;//����id
	int Counter;//�������
	int Targetnum;//��������������
	bool isComplete;//�����Ƿ����
	string MissionName;//������
	string Script;//����
};