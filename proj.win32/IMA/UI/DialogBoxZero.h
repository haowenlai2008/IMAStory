#pragma once
#include "cocos2d.h"
#include <queue>
#include <functional>
USING_NS_CC;
class SentenceUnit
{
public:
	SentenceUnit() {};
	SentenceUnit(const std::string& sentence, const std::string& ico, const std::function<void()> &func) {
		this->sentence = sentence;
		this->ico = ico;
		this->func = func;
	};
	SentenceUnit(const std::string& sentence, const std::string& ico) {
		this->sentence = sentence;
		this->ico = ico;
		func = [](){};
	};
	SentenceUnit(const std::function<void()> &func) {
		this->sentence = std::string();
		this->ico = std::string();
		this->func = func;
	}
	~SentenceUnit() {};
	std::string sentence;
	std::string ico;
	std::function<void()> func;
};
class DialogBoxZero : public Node
{
public:
	CREATE_FUNC(DialogBoxZero);
	bool init();
	bool isFinish();
	void listenInit();
	void showDialog(const std::string& sentence);
	void showDialog(const std::string& sentence, const std::string& texture);
	void showDialog(const std::string& sentence, const std::string& texture, const std::function<void()> &func);
	void showDialog(const std::function<void()> &func);
	void hideDialog();
	void showSentence(float dt);
	void onMouseDown(Event *event);
	void onKeyDown(EventKeyboard::KeyCode keyCode, Event * event);
private:
	bool isHide;
	int charCounter;
	Sprite* ico;
	Sprite* box;
	Label* sentence;
	std::queue<SentenceUnit> sentenceQueue;
};

