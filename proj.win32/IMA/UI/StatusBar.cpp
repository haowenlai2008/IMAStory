#include "StatusBar.h"

StatusBar * StatusBar::create(int value, int MaxValue, const std::string& name, Color3B color)
{
	StatusBar* statusBar = StatusBar::create();
	statusBar->setMaxValue(MaxValue);
	statusBar->setRealValue(value);
	statusBar->setTag(name);
	statusBar->setArticleColor(color);
	return statusBar;
}
//×´Ì¬Ìõ³õÊ¼»¯
bool StatusBar::init()
{
	box = Sprite::create("BarBox.png");
	Article = Sprite::create("Bar.png");
	Article->setAnchorPoint(Vec2(0, 0.5));
	Article->setPosition(Vec2(-box->getContentSize().width / 2, 0));
	this->addChild(box);
	this->addChild(Article);
	return true;
}

void StatusBar::setArticleColor(Color3B color)
{
	Article->setColor(color);
}

void StatusBar::setMaxValue(int value)
{
	MaxValue = value;
}

void StatusBar::setRealValue(int value)
{
	RealValue = value;
	if (Article && box)
	{
		Article->setContentSize(Size(box->getContentSize().width * (float)RealValue / (float)MaxValue, box->getContentSize().height));
		if (!ValueText)
		{
			ValueText = Label::createWithSystemFont(StringUtils::format("%d / %d", RealValue, MaxValue), "Arial", 7);
			ValueText->setPosition(Vec2(0, 0));
			this->addChild(ValueText, 1);
		}
		else
		{
			ValueText->setString(StringUtils::format("%d / %d", RealValue, MaxValue));
		}
	}
	

}

void StatusBar::setTag(const std::string& tag)
{
	if (!Tag)
	{
		Tag = Label::createWithSystemFont(tag, "Arial", 9);
		Tag->setPosition(Vec2(-box->getContentSize().width / 2 - Tag->getContentSize().width / 2, 0));
		this->addChild(Tag);
	}
	else
	{
		Tag->setString(tag);
	}
}

void StatusBar::increase(int value)
{
	if (RealValue + value >= MaxValue)
	{
		setRealValue(MaxValue);
	}
	else
	{
		setRealValue(RealValue + value);
	}
}

void StatusBar::reduce(int value)
{
	if (RealValue - value < 0)
	{
		setRealValue(MaxValue);
	}
	else
	{
		setRealValue(RealValue - value);
	}
}

Size StatusBar::getBarSize()
{
	return Size(box->getContentSize().width + Tag->getContentSize().width, box->getContentSize().height);
}
