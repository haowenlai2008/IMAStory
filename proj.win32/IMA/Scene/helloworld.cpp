#include "helloworld.h"
#include "GameBase.h"


Scene * helloworld::createScene()
{
	//��������
	Scene* scene = Scene::create();

	//ʹ��helloworld���create()��������ͼ��
	Layer* layer = helloworld::create();

	//��helloworld���ͼ����Ϊ�ӽڵ���볡��
	scene->addChild(layer);

	//���س�����ָ��
	return scene;
}


bool helloworld::init()
{
	if (!Layer::init())
	{
		return false;
	} 
	Size visibleSize = Director::getInstance()->getVisibleSize();	//�����ͼ�ĳߴ磨�� �ߣ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();		//���ԭ��
	//��������
	Sprite* box = Sprite::create("Box.png");						//�½�����
	box->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));	//�ѱ�����������ͼ�е�
	this->addChild(box, 1);//��ӱ���Ϊͼ����ӽڵ㣬���ȼ�Ϊ1

	//��������
	Sprite* background = Sprite::create("background2.png");//�½�һ�����飬������background2.png
	background->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));//�ѱ������õ��е�
	this->addChild(background,0);//���ȼ�Ϊ0



	//�����˵���Ͳ˵�
	MenuItemImage* exit = MenuItemImage::create("Exit.png", "Exit.png", CC_CALLBACK_1(helloworld::menuCloseCallback, this));//�����˵���
	exit->setPosition(Vec2(visibleSize.width * 5 / 6, exit->getContentSize().height / 2 + 20));//��������
	exit->setColor(Color3B(255,255,255));//������ɫ
	Menu* menu = Menu::create(exit, NULL);//�����˵�
	menu->setPosition(Vec2::ZERO);//��������
	this->addChild(menu, 1);//��Ӳ˵�Ϊͼ����ӽڵ�

	return true;
}



void helloworld::menuCloseCallback(Ref* pSender)
{
	Sprite* sprite = Sprite::create("pixiv62468048.png");//��������
	sprite->setPosition(Vec2(300, 400));//��������
	sprite->setContentSize(Size(300, 300));//���óߴ�
	this->addChild(sprite);//��Ӿ���Ϊ��ͼ����ӽڵ�
}