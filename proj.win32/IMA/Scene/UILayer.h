#pragma once
#include "cocos2d.h"
#include "MissionManager.h"
#include "PropertyPage.h"
#include "MissionPage.h"
USING_NS_CC;
class Bottom;
class DialogBoxZero;
class MissionPage;
#define SHOW_HIDE_FUNC(TYPE_NAME, VAR_NAME, FUN_NAME) \
protected : TYPE_NAME* VAR_NAME;\
public: void show##FUN_NAME() \
{ \
    VAR_NAME->setVisible(true);\
}\
public: void hide##FUN_NAME() \
{ \
    VAR_NAME->setVisible(false);\
}

class UILayer : public Layer
{
public:
	CREATE_FUNC(UILayer);
	SHOW_HIDE_FUNC(MissionPage, missionPage, MissionPage);
	SHOW_HIDE_FUNC(PropertyPage, propertyPage, PropertyPage);
	bool init();
	void MenuInit();
	void smallMapInit();
	void dialogInit();
	void missionManagerInit();
	void PropertyPageInit();
	void listenInit();
	void update(float delta);
	void smallMapUpdate(float delta);
	void menu_showMenu(Ref* pSender);
	void menu_showAttribute(Ref* pSender);
	void menu_showMission(Ref* pSender);
	void menu_showBag(Ref* pSender);
	void menu_Save(Ref* pSender);
	void menu_Back(Ref* pSender);
	void onKeyDown(EventKeyboard::KeyCode keyCode, Event * event);
private:
	bool isMenuBarHide;
	bool isMissionPageHide;
	bool isPropertyPageHide;
	Sprite* smallMap;
	Sprite* MenuBar;
	Bottom* ShowMenu;
	Bottom* Bottom_Attribute;
	Bottom* Bottom_Mission;
	Bottom* Bottom_Bag;
	Bottom* Bottom_Save;
	Bottom* Bottom_Back;
	DialogBoxZero* dialog;
	//MissionManager* missionManager;
};

