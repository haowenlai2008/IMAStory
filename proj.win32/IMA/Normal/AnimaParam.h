#pragma once
#include "cocos2d.h"
class AnimaParam
{
public:
	int Frame;
	float Speed;
	std::string AnimateName;
	AnimaParam();
	AnimaParam(int Frame, float Speed, const std::string& AnimateName);
	~AnimaParam();
};

