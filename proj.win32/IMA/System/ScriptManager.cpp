#include "ScriptManager.h"
#include "GameManager.h"
#include "MissionManager.h"
#include "DialogBoxZero.h"
#include "NPC.h"
#include "Boss.h"
#include "NPCManager.h"
#include "GameDataManager.h"
ScriptManager * ScriptManager::m_scriptManager = nullptr;

//bool ScriptSign[10] = { false, false, false, false, false, false, false, false, false,false };
ScriptManager * ScriptManager::getInstance()
{
	if (!m_scriptManager)
	{
		m_scriptManager = new (std::nothrow)ScriptManager();
		if (!m_scriptManager->init())
		{
			CC_SAFE_DELETE(m_scriptManager);
			return m_scriptManager;
		}
		m_scriptManager->autorelease();
	}
	return m_scriptManager;
}
bool ScriptManager::init()
{
	this->retain();
	ScripteSign = bitset<10>(GameDataManager::getInstance()->getArchiceData().ScripteSign);
	return true;
}
void ScriptManager::refresh()
{
	ScripteSign = bitset<10>(GameDataManager::getInstance()->getArchiceData().ScripteSign);
}
void ScriptManager::pushSentence(int id)
{
	if (getDialog())
	{
		auto Mm = GameManager::getInstance()->getMainheroine();
		auto missionManager = MissionManager::getInstance();
		auto fun = []() { GameManager::getInstance()->getBoss()->getSprite()->setFlippedX(true); };
		auto fun2 = []() { GameManager::getInstance()->getBoss()->setEnable(true); };
		auto fun3 = []() {
			GameManager::getInstance()->getBoss()->getSprite()->setTexture("DarkKnight2.png"); };
		auto fun4 = []() { 
			auto gdm = GameDataManager::getInstance(); 
		gdm->NPCDataMsg[0].TextureName = "MainHeroine3.png";
		GameManager::getInstance()->getMainheroine()->getSprite()->setTexture("MainHeroine3.png"); };
		switch (id)
		{
		case 0:
			dialog->showDialog(u8"我的名字叫Joker.Jokey", "ICO01.png");
			dialog->showDialog(u8"我从一个叫做地球的地方穿越来到这个萨纳罗大陆", "ICO01.png");
			dialog->showDialog(u8"生前我是个学生，24岁", "ICO01.png");
			dialog->showDialog(u8"穿越过来后我发现这是个二维的世界，我居然是个纸片人！", "ICO01.png");
			dialog->showDialog(u8"这个村庄平静祥和，有一群充满灵性的人", "ICO01.png");
			dialog->showDialog(u8"虽然我只看到我和我的青梅竹马", "ICO01.png");
			dialog->showDialog(u8"大概是画师又偷懒了，找青梅竹马了解下情况吧", "ICO01.png");
			break;
		case 1:
			dialog->showDialog(u8"青梅竹马酱，我杀史莱姆回来了", "ICO01.png");
			dialog->showDialog(u8"人呢？难道是跑到别的图层了？", "ICO01.png");
			dialog->showDialog(u8"没有啊，好像也不是BUG，难道被坏人抓走了？去东边看看吧", "ICO01.png");
			break;
		case 2:
			dialog->showDialog(u8"!!!放开那个女孩！", "ICO01.png", fun);
			dialog->showDialog(u8".....啧，被追上了吗", "ICO03.png");
			dialog->showDialog(u8"...老哥你这有点惨，是不是得罪了画师啊，脸都没画", "ICO01.png");
			dialog->showDialog(u8"额台词错了，你这家伙，抓我的青梅竹马干嘛", "ICO01.png");
			dialog->showDialog(u8"虽然因为画师偷懒，这货动作都没有", "ICO01.png");
			dialog->showDialog(u8"但是她是在这个栅格化的世界上陪着我的重要的纸片人", "ICO01.png");
			dialog->showDialog(u8"不交出来的话。。。", "ICO01.png");
			dialog->showDialog(u8"勇者之力吗。。巧了", "ICO03.png");
			dialog->showDialog(u8"尝尝这个", "ICO03.png",fun3);
			dialog->showDialog(u8"什么，这股力量是。。你也是勇者？！", "ICO01.png");
			dialog->showDialog(u8"身为勇者，你却要保护转生的魔王吗", "ICO03.png");
			dialog->showDialog(u8"。。。。你果然也看得出来么", "ICO01.png");
			dialog->showDialog(u8"你既然知道为什么要阻止我", "ICO03.png");
			dialog->showDialog(u8"仪式已经开始了，再不杀了她的话。。三次冲击就要来了", "ICO03.png");
			dialog->showDialog(u8"5000年前，魔王问世，整个大陆失去了颜色。。。", "ICO03.png");
			dialog->showDialog(u8"就像我现在这样。。。", "ICO03.png");
			dialog->showDialog(u8"即使是这样，我也有不得不保护的东西啊，\n因为我是她的Darling啊！", "ICO01.png");
			dialog->showDialog(u8"这很轻小说。。。。既然这样的话", "ICO03.png");
			dialog->showDialog(u8"我不做人了jojo!", "ICO03.png", fun2);
			break;
		case 3:
			dialog->showDialog(u8"不错嘛，这样也许能打出HappyEnding", "ICO03.png");
			dialog->showDialog(u8"你说什么？", "ICO01.png");
			dialog->showDialog(u8"如果是现在的你的话，也许能够拯救她。。。", "ICO03.png");
			dialog->showDialog(u8"未来已经改变了吧。。。", "ICO03.png");
			dialog->showDialog(u8"你到底在说什么？！", "ICO01.png");
			dialog->showDialog(u8"听好了jojo,连接上一切吧，即使在血月之日,世界将面临灾难", "ICO03.png");
			dialog->showDialog(u8"但这是到达伊甸园的必经之路", "ICO03.png");
			dialog->showDialog(u8"。。。。。。。血月之日。。", "ICO01.png");
			dialog->showDialog(u8"我们会再见的。。", "ICO03.png");
			dialog->showDialog(u8"这之后的未来吗。。。", "ICO01.png");
			dialog->showDialog(u8"jojo?", "ICO02.png");
			dialog->showDialog(u8"???", "ICO01.png");
			dialog->showDialog(u8"封印被压制了？", "ICO01.png", fun4);
			dialog->showDialog(u8"那个家伙。。。到底是谁", "ICO01.png");
			break;
		default:
			break;
		}
	}
	
}

void ScriptManager::pushSentence(int id, int NPCID)
{
	if (getDialog())
	{
		auto missionManager = MissionManager::getInstance();
		switch (NPCID)
		{
		case 0:
			if (missionManager->getMissionID() == 1 && !ScripteSign[1])
			{
				dialog->showDialog(u8"噢？是Joker.Jokey啊", "ICO02.png");
				dialog->showDialog(u8"(这位就是我来到这个世界后的青梅竹马)", "ICO01.png");
				dialog->showDialog(u8"(虽然我也不知道为什么是青梅竹马，可能这就是设定吧)", "ICO01.png");
				dialog->showDialog(u8"话说你的名字太难听了，以后就叫你JoJo好了", "ICO02.png");
				dialog->showDialog(u8"!?你是怎么知道那个梗的？", "ICO01.png");
				dialog->showDialog(u8"好饿啊，快去杀几只史莱姆回来吃。 史莱姆(0/5)", "ICO02.png");
				missionManager->countUp();
				missionManager->missionComPlete();
				ScripteSign[1] = true;
			}
			break;
		default:
			break;
		}
	}
}

void ScriptManager::unLoad()
{
	this->release();
}
