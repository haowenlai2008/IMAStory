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
	bool init();//初始化
	void refresh();//重置
	void pushSentence(int id);//实现剧情
	void pushSentence(int id, int NPCID);//实现剧情
	void unLoad();
	static ScriptManager* getInstance();//获得实例
	bitset<10> ScripteSign;//剧情标记
private:
	ScriptManager() {};
	static ScriptManager* m_scriptManager;
};