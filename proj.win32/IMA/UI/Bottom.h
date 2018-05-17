#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Bottom :public MenuItemImage
{
public:
	//virtual bool init();
	void setBottomSize(Size size);
	static Bottom *create(const std::string& name, const ccMenuCallback& callback);
	static Bottom *CircalBottionCreate(const std::string& name, const ccMenuCallback& callback);
	CREATE_FUNC(Bottom);
};

