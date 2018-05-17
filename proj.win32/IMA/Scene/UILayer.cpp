#include "UILayer.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Bottom.h"
#include "DialogBoxZero.h"
#include "GameManager.h"
#include "GameDataManager.h"
#include "MonsterManager.h"
#include "DialogBoxZero.h"
#include "NPCManager.h"
#include "MissionPage.h"
#include "ScriptManager.h"
#include "character.h"
#include "Monster.h"
#include "NPC.h"
bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	MenuInit();
	smallMapInit();
	dialogInit();
	missionManagerInit();
	PropertyPageInit();
	listenInit();
	this->schedule(schedule_selector(UILayer::smallMapUpdate), 0.05f);
	return true;
}

void UILayer::MenuInit()
{
	isMenuBarHide = true;
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();
	ShowMenu = Bottom::CircalBottionCreate(u8"菜单", CC_CALLBACK_1(UILayer::menu_showMenu, this));
	ShowMenu->setPosition(Vec2(origin.x + ShowMenu->getContentSize().width / 2, 
		origin.y + size.height - ShowMenu->getContentSize().height / 2));
	auto StaticMenu = Menu::create(ShowMenu, NULL);
	StaticMenu->setPosition(Vec2::ZERO);
	Bottom_Attribute = Bottom::create(u8"属性", CC_CALLBACK_1(UILayer::menu_showAttribute, this));
	Bottom_Attribute->setPosition(Vec2(0.75 * Bottom_Attribute->getContentSize().width, 0));
	Bottom_Bag = Bottom::create(u8"背包", CC_CALLBACK_1(UILayer::menu_showBag, this));
	Bottom_Bag->setPosition(Vec2(1.75 * Bottom_Bag->getContentSize().width, 0));
	Bottom_Mission = Bottom::create(u8"任务", CC_CALLBACK_1(UILayer::menu_showMission, this));
	Bottom_Mission->setPosition(Vec2(2.75 * Bottom_Bag->getContentSize().width, 0));
	Bottom_Save = Bottom::create(u8"存档", CC_CALLBACK_1(UILayer::menu_Save, this));
	Bottom_Save->setPosition(Vec2(3.75 * Bottom_Save->getContentSize().width, 0));
	Bottom_Back = Bottom::create(u8"返回", CC_CALLBACK_1(UILayer::menu_Back, this));
	Bottom_Back->setPosition(Vec2(4.75 * Bottom_Back->getContentSize().width, 0));
	auto DyMenu = Menu::create(Bottom_Attribute, Bottom_Bag, Bottom_Mission, Bottom_Save, Bottom_Back, NULL);
	
	MenuBar = Sprite::create("MenuBar.png");
	DyMenu->setPosition(Vec2(0, MenuBar->getContentSize().height / 2));
	MenuBar->addChild(DyMenu);
	//StaticMenu->setPosition(Vec2(0, MenuBar->getContentSize().height / 2));
	MenuBar->setPosition(Vec2(origin.x  - MenuBar->getContentSize().width / 2, origin.y + size.height - MenuBar->getContentSize().height / 2));
	this->addChild(MenuBar);
	this->addChild(StaticMenu);
}

void UILayer::smallMapInit()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();
	smallMap = Sprite::create("smallmap.png");
	smallMap->setPosition(Vec2(origin.x + size.width - smallMap->getContentSize().width,
		origin.y + size.height - smallMap->getContentSize().height));
	smallMap->setAnchorPoint(Vec2::ZERO);
	this->addChild(smallMap);
}

void UILayer::dialogInit()
{
	dialog = DialogBoxZero::create();
	this->addChild(dialog, 1);
	ScriptManager::getInstance()->setDialog(dialog);
	if (!ScriptManager::getInstance()->ScripteSign[0])
	{
		ScriptManager::getInstance()->ScripteSign[0] = true;
		ScriptManager::getInstance()->pushSentence(0);
	}
	//ScriptManager::getInstance()->ScripteSign[5] = true;
}

void UILayer::missionManagerInit()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();
	missionPage = MissionPage::create();
	missionPage->setPosition(Vec2(origin.x + size.width - missionPage->getBoxSize().width,
		origin.y + size.height - missionPage->getBoxSize().height));
	this->addChild(missionPage);
	isMissionPageHide = true;
	hideMissionPage();
	GameManager::getInstance()->setMissionPage(missionPage);
}

void UILayer::PropertyPageInit()
{
	propertyPage = PropertyPage::create();
	propertyPage->setPosition(300, 200);
	propertyPage->setVisible(false);
	isPropertyPageHide = true;
	this->addChild(propertyPage);
}

void UILayer::listenInit()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(UILayer::onKeyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void UILayer::update(float delta)
{
}

void UILayer::smallMapUpdate(float delta)
{
	smallMap->removeAllChildren();
	auto gm = GameManager::getInstance();
	auto characterIns = gm->getCharacter();
	auto monsterManager = gm->getMonsterManager();
	auto npcManager = gm->getNPCManager();
	Size mapSize = gm->getMapSize();
	Size smallmapSize = Size(smallMap->getContentSize() * 8 / 9);
	auto characterPoint = Sprite::create("CharacterPoint.png");
	int x = smallmapSize.width  * (characterIns->getPositionX() / mapSize.width) + 20;
	int y = smallmapSize.height * (characterIns->getPositionY() / mapSize.height) + 20;
	characterPoint->setPosition(x, y);
	smallMap->addChild(characterPoint);
	//NPC的点
	for (auto p : npcManager->NPCList)
	{
		if (p)
		{
			auto npc = Sprite::create("NPCPoint.png");
			int x = smallmapSize.width * (p->getPosition().x / mapSize.width) + 20;
			int y = smallmapSize.height * (p->getPosition().y / mapSize.height) + 20;
			npc->setPosition(x, y);
			smallMap->addChild(npc);
		}
	}
	//怪物的点
	for (auto p : monsterManager->MonsterList)
	{
		if (p)
		{
			auto monster = Sprite::create("MonsterPoint.png");
			int x = smallmapSize.width * (p->getPosition().x / mapSize.width) + 20;
			int y = smallmapSize.height * (p->getPosition().y / mapSize.height) + 20;
			monster->setPosition(x, y);
			smallMap->addChild(monster);
		}
	}
}

void UILayer::menu_showMenu(Ref * pSender)
{
	if (isMenuBarHide)
	{
		MenuBar->runAction(MoveBy::create(0.1, Vec3(MenuBar->getContentSize().width + ShowMenu->getContentSize().width, 0, 0)));
		isMenuBarHide = false;
	}
	else
	{
		MenuBar->runAction(MoveBy::create(0.1, Vec3(-MenuBar->getContentSize().width - ShowMenu->getContentSize().width, 0, 0)));
		isMenuBarHide = true;
	}
}

void UILayer::menu_showAttribute(Ref * pSender)
{
	if (isPropertyPageHide)
	{
		missionPage->missionScriptUpdate();
		propertyPage->PropertyUpdate();
		showPropertyPage();
		isPropertyPageHide = false;
	}
	else
	{
		hidePropertyPage();
		isPropertyPageHide = true;
	}
}

void UILayer::menu_showMission(Ref * pSender)
{
	if (isMissionPageHide)
	{
		missionPage->missionScriptUpdate();
		showMissionPage();
		isMissionPageHide = false;
	}
	else
	{
		hideMissionPage();
		isMissionPageHide = true;
	}
}

void UILayer::menu_showBag(Ref * pSender)
{
}

void UILayer::menu_Save(Ref * pSender)
{
	GameDataManager::getInstance()->Save();
}

void UILayer::menu_Back(Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	Director::getInstance()->purgeCachedData();
	Scene* scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void UILayer::onKeyDown(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		hideMissionPage();
		hidePropertyPage();
		isPropertyPageHide = true;
		isMissionPageHide = true;
	}
}
