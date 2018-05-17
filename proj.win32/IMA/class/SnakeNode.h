#ifndef SNAKE_NODE_H_
#define SNAKE_NODE_H_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/UIScale9Sprite.h"
USING_NS_CC;
using namespace cocos2d::ui;
enum  class ENUM_DIR
{
	Dir_up,
    Dir_down,
	Dir_right,
	Dir_left,
	Dir_stop
};
class SnakeNode
{
public:
	ENUM_DIR m_dir;
	Sprite* sprite;
	int m_x, m_y;
	SnakeNode(int x, int y);
	~SnakeNode();
	void SetSpriteSize(void);
	void setPositionRC(int x, int y);
};
#endif // !GAMESCENE_H_
