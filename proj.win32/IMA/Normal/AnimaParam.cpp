#include "AnimaParam.h"



AnimaParam::AnimaParam()
{
	this->Frame = 0;
	this->Speed = 0.0f;
	this->AnimateName = std::string();
}

AnimaParam::AnimaParam(int Frame, float Speed, const std::string& AnimateName)
{
	this->Frame = Frame;
	this->Speed = Speed;
	this->AnimateName = AnimateName;
}


AnimaParam::~AnimaParam()
{
}
