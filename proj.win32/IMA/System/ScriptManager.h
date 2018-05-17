#pragma once
#include "cocos2d.h"
#include <bitset>
USING_NS_CC;
using std::bitset;
class DialogBoxZero;
class ScriptManager : public Ref
{
public:
	CC_SYNTHESIZE(DialogBoxZero*, dialog, Dialog);
	~ScriptManager() { this->unLoad(); };
	bool init();//��ʼ��
	void refresh();//����
	void pushSentence(int id);//ʵ�־���
	void pushSentence(int id, int NPCID);//ʵ�־���
	void unLoad();
	static ScriptManager* getInstance();//���ʵ��
	bitset<10> ScripteSign;//������
private:
	ScriptManager() {};
	static ScriptManager* m_scriptManager;
};