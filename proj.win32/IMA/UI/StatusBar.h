#pragma once
#include "cocos2d.h"
#include <cocos2d.h>
USING_NS_CC;
class StatusBar : public Node
{
public:
	CREATE_FUNC(StatusBar);
	static StatusBar* create(int value, int MaxValue, const std::string& name, Color3B color);
	bool init();
	void setArticleColor(Color3B color);
	void setMaxValue(int value);
	void setRealValue(int value);
	void setTag(const std::string& tag);
	void increase(int value);
	void reduce(int value);
	Size getBarSize();
private:
	int MaxValue;
	int RealValue;
	Sprite* box;
	Sprite* Article;
	Label* Tag;
	Label* ValueText;
};

