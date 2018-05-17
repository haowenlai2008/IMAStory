#ifndef _SECONDSCENE_H_
#define _SECONDSCENE_H_
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::ui;
class SecondScene : public Layer
{
public:
	static Scene* createScene();//创建场景返回场景指针
	virtual bool init();//场景初始化
	CREATE_FUNC(SecondScene);//创建场景宏
private:
	SnakeNode* spHead;//蛇头
	Sprite* spfood;//食物指针
	Vector<Sprite* > allbody;//蛇身
	int m_score;//分数
	void SnakeMove(float delta);//蛇的移动
	void Setmenu();//设置菜单
	void popScene(Ref* pSender);//切换菜单回调函数
	void SetScoreLabel();//设置计分器
	void setBackGround();//用OpenGL画网格
	void creatsnake();//初始化蛇身
	void setListener();//设置键盘监听
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//释放按键回调函数
	void GameOver();//游戏结束事件
	bool DirChange;//判断方向是否改变过一次
	bool TouchSnake(float x, float y);//判断坐标是否与某节点重合
	bool Nodetouch(Point first, Point second);//判断坐标重合
};
#endif // !_SECONDSCENE_H_


