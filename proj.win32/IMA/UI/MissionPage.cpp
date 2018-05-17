#include "MissionPage.h"
#include "MissionManager.h"
#include "Mission.h"
#include "Bottom.h"
bool MissionPage::init()
{
	missionManager = MissionManager::getInstance();
	UIInit();
	missionScriptUpdate();
	return true;
}

void MissionPage::UIInit()
{
	this->setAnchorPoint(Vec2::ZERO);
	Box = Sprite::create("MissionBox.png");
	Box->setAnchorPoint(Vec2::ZERO);
	//Box->setPosition(Vec2(Box->getContentSize().width / 2, Box->getContentSize().height / 2));
	this->addChild(Box);

	MissionName = LabelTTF::create(u8"日常", "Arial", 15);
	MissionName->setAnchorPoint(Vec2::ZERO);
	MissionName->setPosition(Vec2(44, 500));
	//MissionName->setDimensions(198, 75);
	this->addChild(MissionName, 1);

	MissionScript = LabelTTF::create(u8"找你的青梅竹马解释一下设定吧", "Arial", 15);
	MissionScript->setAnchorPoint(Vec2::ZERO);
	MissionScript->setPosition(Vec2(250, 450));
	//MissionScript->setDimensions(265, 374);
	this->addChild(MissionScript, 1);

	CompleteBottom = Bottom::create(u8"完成", CC_CALLBACK_1(MissionPage::menu_Complete, this));
	CompleteBottom->setPosition(Vec2(350, 65));
	auto menu = Menu::create(CompleteBottom, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}


void MissionPage::missionScriptUpdate()
{
	if (!missionManager->MissionList.empty())
	{
		MissionName->setString(StringUtils::format("%d.", missionManager->MissionList.front()->id) + missionManager->MissionList.front()->MissionName);
		MissionScript->setString(missionManager->MissionList.front()->Script + StringUtils::format("(%d / %d)", missionManager->MissionList.front()->Counter, missionManager->MissionList.front()->Targetnum));
	}
	
}

Size MissionPage::getBoxSize()
{
	return Box->getContentSize();
}

void MissionPage::menu_Complete(Ref * pSender)
{
	if (!missionManager->MissionList.empty())
	{
		if (missionManager->MissionList.front()->isComplete)
		{
			missionManager->MissionList.front()->release();
			missionManager->MissionList.front() = nullptr;
			missionManager->MissionList.pop();
			if (!MissionCompleteTest)
			{
				MissionCompleteTest = Label::createWithSystemFont(u8"任务完成", "Arial", 15);
				MissionCompleteTest->setPosition(Vec2(45, 60));
				CompleteBottom->addChild(MissionCompleteTest);
			}
			else
			{
				MissionCompleteTest->setString(u8"任务完成");
				MissionCompleteTest->setVisible(true);
			}
			missionScriptUpdate();
		}
		else
		{
			if (!MissionCompleteTest)
			{
				MissionCompleteTest = Label::createWithSystemFont(u8"任务未完成", "Arial", 15);
				MissionCompleteTest->setPosition(Vec2(45, 60));
				CompleteBottom->addChild(MissionCompleteTest);
			}
			else
			{
				MissionCompleteTest->setString(u8"任务未完成");
				MissionCompleteTest->setVisible(true);
			}
		}
		auto delay = DelayTime::create(2);
		auto callback = CallFunc::create([&]() {MissionCompleteTest->setVisible(false); });
		MissionCompleteTest->runAction(Sequence::create(delay, callback, nullptr));
	}
}
