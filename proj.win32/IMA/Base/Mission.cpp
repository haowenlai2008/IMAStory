#include "Mission.h"



Mission * Mission::create(int id, int Counter, int Targetnum, bool isComplete, const string & MissionName, const string & Script)
{
	Mission* mission = new Mission(id, Counter, Targetnum, isComplete, MissionName, Script);
	if (mission)
	{
		mission->autorelease();
		return mission;
	}
	return nullptr;
}

Mission::Mission(int id, int Counter, int Targetnum, bool isComplete, const string& MissionName, const string& Script)
{
	this->id = id;
	this->Counter = Counter;
	this->Targetnum = Targetnum;
	this->isComplete = isComplete;
	this->MissionName = MissionName;
	this->Script = Script;
}

void Mission::countUp()
{
	if (Counter < Targetnum)
		Counter++;
	if (Counter == Targetnum)
		isComplete = true;
}
