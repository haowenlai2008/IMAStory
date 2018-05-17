#include "GameStart.h"
#include "HelloWorldScene.h"

static char texture[2][10] = { "white.jpg","black.jpg" };

GameStart::GameStart()
{
}


GameStart::~GameStart()
{
	//if (file)
	//{
	//	fclose(file);
	//}
}

Scene * GameStart::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = GameStart::create();
	scene->addChild(layer);
	return scene;
}

bool GameStart::init()
{
	if (!Layer::init())
		return false;
	//if (!(file = fopen("isleagle2", "rb")))
	//{
	//	log("open test.txt failed");
	//	return false;
	//}
	//int n = 0;
	//fscanf(file, "%d", &n);
	//log("n = %d", n);
	//for (int i = 0; i < 32; i++)
	//{
	//	log("%d", (n << i & 0x80000000) >> 31);
	//}
	gameLevel = 0;
	matrixSize = 2;
	//readLevel();
	gameOver = false;
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	////初始化矩阵
	//for (int i = 0; i < matrixSize; i++)
	//{
	//	for (int j = 0; j < matrixSize; j++)
	//	{
	//		matrix[i][j] = false;
	//	}
	//}
	
	//设置背景
	Sprite* background = Sprite::create("background.png");
	background->setContentSize(visibleSize);
	background->setColor(Color3B(0x70, 0x70, 0x70));
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);
	//设置菜单
	MenuItemImage* backItem = MenuItemImage::create(
		"BackNormal.png",
		"BackSelected.png",
		CC_CALLBACK_1(GameStart::menuBackcall, this)
	);
	backItem->setPosition(Vec2(origin.x + visibleSize.width - backItem->getContentSize().width / 2,
		origin.y + backItem->getContentSize().height / 2));
	Menu* menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			matrix[i][j] = false;
		}
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	matrix[rand() % matrixSize][rand() % matrixSize] = true;
	Vec2 midPoint = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	originPoint = Vec2(midPoint.x - length * matrixSize / 2, midPoint.y - length * matrixSize / 2);
	Vec2 firstPoint;
	firstPoint.x = originPoint.x + 0.5 * length;
	firstPoint.y = originPoint.y + 0.5 * length;
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			spriteMatrix[i][j] = Sprite::create(texture[matrix[i][j]]);
			spriteMatrix[i][j]->setContentSize(Size(length, length));
			spriteMatrix[i][j]->setPosition(firstPoint.x + i*length, firstPoint.y + j*length);
			this->addChild(spriteMatrix[i][j]);
		}
	}
	createListener();//创建监听
	return true;
}

void GameStart::createListener()
{
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(GameStart::click, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameStart::click(Event * event)
{
	int i = 0;
	EventMouse* e = (EventMouse*)event;
	Vec2 cursorPosition = Vec2(e->getCursorX(), e->getCursorY());
	if (cursorPosition.x > originPoint.x + matrixSize * length ||
		cursorPosition.y > originPoint.y + matrixSize * length ||
		cursorPosition.x < originPoint.x ||
		cursorPosition.y < originPoint.y ||
		gameOver
		)
		return;
	log("%f,%f\n", cursorPosition.x, cursorPosition.y);
	int x = abs(int((cursorPosition.x - originPoint.x) / length));
	int y = abs(int((cursorPosition.y - originPoint.y) / length));
	log("%d,%d\n", y, x);
	
	matrix[x][y] = !matrix[x][y];
	Sprite* sprite = Sprite::create(texture[matrix[x][y]]);
	Texture2D* t = sprite->getTexture();
	spriteMatrix[x][y]->setTexture(t);
	if (x > 0)
	{
		matrix[x - 1][y] = !matrix[x - 1][y];
		Sprite* sprite = Sprite::create(texture[matrix[x - 1][y]]);
		Texture2D* t = sprite->getTexture();
		spriteMatrix[x - 1][y]->setTexture(t);
	}
	if (y > 0)
	{
		matrix[x][y - 1] = !matrix[x][y - 1];
		Sprite* sprite = Sprite::create(texture[matrix[x][y - 1]]);
		Texture2D* t = sprite->getTexture();
		spriteMatrix[x][y - 1]->setTexture(t);
	}
	if (x < matrixSize - 1)
	{
		matrix[x + 1][y] = !matrix[x + 1][y];
		Sprite* sprite = Sprite::create(texture[matrix[x + 1][y]]);
		Texture2D* t = sprite->getTexture();
		spriteMatrix[x + 1][y]->setTexture(t);
	}
	if (y < matrixSize - 1)
	{
		matrix[x][y + 1] = !matrix[x][y + 1];
		Sprite* sprite = Sprite::create(texture[matrix[x][y + 1]]);
		Texture2D* t = sprite->getTexture();
		spriteMatrix[x][y + 1]->setTexture(t);
	}
	bool p = **matrix;
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			if (matrix[i][j] != p)
				return;
			if (i == matrixSize - 1 && j == matrixSize - 1)
			{
				//Sprite* win = Sprite::create("Win.png");
				//win->setPosition(Vec2(origin.x + visibleSize.width / 2, win->getContentSize().height));
				//this->addChild(win);
				resetMatrix();
				/*readLevel();*/
				matrixSize++;
				paint();
				return;
			}
		}
	}
}
void GameStart::menuBackcall(Ref * pSender)
{
	Director::getInstance()->purgeCachedData();
	Scene* scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameStart::paint()
{
	Vec2 midPoint = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	originPoint = Vec2(midPoint.x - (visibleSize.width / 12) * matrixSize / 2, midPoint.y - (visibleSize.width / 12) * matrixSize / 2);
	Vec2 firstPoint;
	firstPoint.x = originPoint.x + 0.5 * (visibleSize.width / 12);
	firstPoint.y = originPoint.y + 0.5 * (visibleSize.width / 12);
	Size boxSize = Size((visibleSize.width / 12), (visibleSize.width / 12));
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			spriteMatrix[i][j] = Sprite::create(texture[matrix[i][j]]);
			spriteMatrix[i][j]->setContentSize(boxSize);
			spriteMatrix[i][j]->setPosition(firstPoint.x + i*(visibleSize.width / 12), firstPoint.y + j*(visibleSize.width / 12));
			this->addChild(spriteMatrix[i][j]);
		}
	}
}

void GameStart::readLevel()
{
	int temp = 0;
	int data = 0;
	if (!fread(&data, 4, 1, file))
	{
		gameOver = true;
		return;
	}
	//读取关卡矩阵边长
	temp |= data & 0x11;
	switch (temp)
	{
	case 0x00:matrixSize = 2; break;
	case 0x01:matrixSize = 3; break;
	case 0x10:matrixSize = 4; break;
	case 0x11:matrixSize = 5; break;
	default:
		break;
	}
	log("%d", matrixSize);
	//对齐
	data >>= 2;
	//根据文件内容设置矩阵
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			matrix[i][j] = (data >> (i * matrixSize + j)) & 0x01;
		}
	}
}

void GameStart::resetMatrix()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			matrix[i][j] = false;
		}
	}
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			spriteMatrix[i][j]->removeFromParent();
			spriteMatrix[i][j] = nullptr;
		}
	}
}

