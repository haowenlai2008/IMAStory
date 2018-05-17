#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
USING_NS_CC;
using namespace cocos2d::ui;
#define PTM (32)
class Box2DTestLayer : public Layer
{
private:
	Texture2D* _spriteTexture;
	b2World* world;
public:
	CREATE_FUNC(Box2DTestLayer);
	static Scene* createScene();
	~Box2DTestLayer();
	virtual bool init();
	void initPhysics();
	void createResetButton();
	void addNewSpriteAtPosition(Vec2 p);
	void update(float dt);
	void onMouseUp(Event* event);
	void onAcceleration(Acceleration* acc, Event* event);
//#if CC_ENABLE_BOX2D_INTEGRATION
//protected:
//	kmMat4 _modelViewMV;
//	void onDraw();
//	CustomCommand _customCommand;
//#endif
};

