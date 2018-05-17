#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameDataManager.h"
#include "GameBase.h"
#include "ScriptManager.h"
#include "MissionManager.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene; 
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("background.png");
	background->setContentSize(visibleSize);
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);
	MenuItemImage* closeItem = MenuItemImage::create(
		"ExitNormal.png",
		"Exit_selected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback,this)
	);
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	MenuItemImage* gameStartItem = MenuItemImage::create(
		"StartNormal.png",
		"Start_selected.png",
		CC_CALLBACK_1(HelloWorld::menuGameStartcallback, this)
	);
	MenuItemImage* gameContinueItem = MenuItemImage::create(
		"ContinueS.png",
		"ContinueP.png",
		CC_CALLBACK_1(HelloWorld::menuGameContinuecallback, this)
	);
	gameStartItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	gameContinueItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - gameContinueItem->getContentSize().height * 2));
    auto menu = Menu::create(closeItem, gameStartItem, gameContinueItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto title = Sprite::create("Title.png");

    //Label* label = Label::createWithSystemFont(u8"小F战记", "Arial", 40); 
	
    // position the label on the center of the screen
	title->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - title->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(title, 1);
   
    return true;
}



void HelloWorld::menuGameStartcallback(Ref * p)
{
	GameDataManager::getInstance()->ArchiceInit();
	GameDataManager::getInstance()->dataReset();
	ScriptManager::getInstance()->refresh();
	MissionManager::getInstance()->MissionInit();
	Director::getInstance()->purgeCachedData();
	Scene* scene = GameBase::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::menuGameContinuecallback(Ref * pSender)
{
	GameDataManager::getInstance()->dataReset();
	ScriptManager::getInstance()->refresh();
	MissionManager::getInstance()->MissionInit();
	log(u8"2现在任务编号是:%d", MissionManager::getInstance()->getMissionID());
	Director::getInstance()->purgeCachedData();
	Scene* scene = GameBase::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
