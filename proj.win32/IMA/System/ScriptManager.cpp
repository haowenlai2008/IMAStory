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
			dialog->showDialog(u8"�ҵ����ֽ�Joker.Jokey", "ICO01.png");
			dialog->showDialog(u8"�Ҵ�һ����������ĵط���Խ������������޴�½", "ICO01.png");
			dialog->showDialog(u8"��ǰ���Ǹ�ѧ����24��", "ICO01.png");
			dialog->showDialog(u8"��Խ�������ҷ������Ǹ���ά�����磬�Ҿ�Ȼ�Ǹ�ֽƬ�ˣ�", "ICO01.png");
			dialog->showDialog(u8"�����ׯƽ����ͣ���һȺ�������Ե���", "ICO01.png");
			dialog->showDialog(u8"��Ȼ��ֻ�����Һ��ҵ���÷����", "ICO01.png");
			dialog->showDialog(u8"����ǻ�ʦ��͵���ˣ�����÷�����˽��������", "ICO01.png");
			break;
		case 1:
			dialog->showDialog(u8"��÷��������ɱʷ��ķ������", "ICO01.png");
			dialog->showDialog(u8"���أ��ѵ����ܵ����ͼ���ˣ�", "ICO01.png");
			dialog->showDialog(u8"û�а�������Ҳ����BUG���ѵ�������ץ���ˣ�ȥ���߿�����", "ICO01.png");
			break;
		case 2:
			dialog->showDialog(u8"!!!�ſ��Ǹ�Ů����", "ICO01.png", fun);
			dialog->showDialog(u8".....������׷������", "ICO03.png");
			dialog->showDialog(u8"...�ϸ������е�ң��ǲ��ǵ����˻�ʦ��������û��", "ICO01.png");
			dialog->showDialog(u8"��̨�ʴ��ˣ�����һץ�ҵ���÷�������", "ICO01.png");
			dialog->showDialog(u8"��Ȼ��Ϊ��ʦ͵�������������û��", "ICO01.png");
			dialog->showDialog(u8"�������������դ�񻯵������������ҵ���Ҫ��ֽƬ��", "ICO01.png");
			dialog->showDialog(u8"���������Ļ�������", "ICO01.png");
			dialog->showDialog(u8"����֮���𡣡�����", "ICO03.png");
			dialog->showDialog(u8"�������", "ICO03.png",fun3);
			dialog->showDialog(u8"ʲô����������ǡ�����Ҳ�����ߣ���", "ICO01.png");
			dialog->showDialog(u8"��Ϊ���ߣ���ȴҪ����ת����ħ����", "ICO03.png");
			dialog->showDialog(u8"�����������ȻҲ���ó���ô", "ICO01.png");
			dialog->showDialog(u8"���Ȼ֪��ΪʲôҪ��ֹ��", "ICO03.png");
			dialog->showDialog(u8"��ʽ�Ѿ���ʼ�ˣ��ٲ�ɱ�����Ļ��������γ����Ҫ����", "ICO03.png");
			dialog->showDialog(u8"5000��ǰ��ħ��������������½ʧȥ����ɫ������", "ICO03.png");
			dialog->showDialog(u8"��������������������", "ICO03.png");
			dialog->showDialog(u8"��ʹ����������Ҳ�в��ò������Ķ�������\n��Ϊ��������Darling����", "ICO01.png");
			dialog->showDialog(u8"�����С˵����������Ȼ�����Ļ�", "ICO03.png");
			dialog->showDialog(u8"�Ҳ�������jojo!", "ICO03.png", fun2);
			break;
		case 3:
			dialog->showDialog(u8"���������Ҳ���ܴ��HappyEnding", "ICO03.png");
			dialog->showDialog(u8"��˵ʲô��", "ICO01.png");
			dialog->showDialog(u8"��������ڵ���Ļ���Ҳ���ܹ�������������", "ICO03.png");
			dialog->showDialog(u8"δ���Ѿ��ı��˰ɡ�����", "ICO03.png");
			dialog->showDialog(u8"�㵽����˵ʲô����", "ICO01.png");
			dialog->showDialog(u8"������jojo,������һ�аɣ���ʹ��Ѫ��֮��,���罫��������", "ICO03.png");
			dialog->showDialog(u8"�����ǵ�������԰�ıؾ�֮·", "ICO03.png");
			dialog->showDialog(u8"��������������Ѫ��֮�ա���", "ICO01.png");
			dialog->showDialog(u8"���ǻ��ټ��ġ���", "ICO03.png");
			dialog->showDialog(u8"��֮���δ���𡣡���", "ICO01.png");
			dialog->showDialog(u8"jojo?", "ICO02.png");
			dialog->showDialog(u8"???", "ICO01.png");
			dialog->showDialog(u8"��ӡ��ѹ���ˣ�", "ICO01.png", fun4);
			dialog->showDialog(u8"�Ǹ��һ����������˭", "ICO01.png");
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
				dialog->showDialog(u8"�ޣ���Joker.Jokey��", "ICO02.png");
				dialog->showDialog(u8"(��λ���������������������÷����)", "ICO01.png");
				dialog->showDialog(u8"(��Ȼ��Ҳ��֪��Ϊʲô����÷��������������趨��)", "ICO01.png");
				dialog->showDialog(u8"��˵�������̫�����ˣ��Ժ�ͽ���JoJo����", "ICO02.png");
				dialog->showDialog(u8"!?������ô֪���Ǹ����ģ�", "ICO01.png");
				dialog->showDialog(u8"�ö�������ȥɱ��ֻʷ��ķ�����ԡ� ʷ��ķ(0/5)", "ICO02.png");
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
