#include "Biology.h"
#include "Controller.h"
static float bloodLength = 0;
static float EXPLength = 0;

//设置名称
void Biology::setName(const std::string & text)
{
	if (m_sprite)
	{
		Name = Label::createWithSystemFont(text, "Arial", 20);
		Vec2 position = Vec2(0, m_sprite->getContentSize().height + 20);
		Name->setColor(Color3B(0x00, 0x00, 0x00));
		Name->setPosition(position);
		this->addChild(Name, 2);
	}
}
//改变纹理
void Biology::changeTexture(const std::string & filename)
{
	m_sprite->setTexture(filename);
}

//绑定精灵
void Biology::bindSprite(Sprite * sprite)
{
	m_sprite = sprite;
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	this->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(m_sprite,1);
}

//绑定控制器
void Biology::bindController(Controller * controller)
{
	m_Controller = controller;
	this->addChild(m_Controller);
}

//受到伤害
void Biology::receiveDamage(int damage)
{
	setRealHp(getRealHp() - damage);
	if (getRealHp() <= 0)
	{
		Dead = true;
		setRealHp(0);
	}
	log("blood = %d", getRealHp());
	if (Blood)
	{
		Blood->setContentSize(Size(((float)getRealHp() / getMaxHP()) * bloodLength, Blood->getContentSize().height));
		HPUIupdate();
	}
	
}

void Biology::LoadAction()
{
}

void Biology::AttributesInit()
{
}



//加血
void Biology::cure(int hp)
{
	if (getRealHp() + hp < getMaxHP())
		setRealHp(getRealHp() + hp);
	else
	{
		setRealHp(getMaxHP());
	}
	Blood->setContentSize(Size(((float)getRealHp() / getMaxHP()) * bloodLength, Blood->getContentSize().height));
	HPUIupdate();
}

void Biology::LevelUp()
{
	setLevel(getLevel() + 1);//升级
	setMaxHP(getMaxHP() + 100);//增加血量上限
	setRealHp(getMaxHP());//增加血量
	Blood->setContentSize(Size(((float)getRealHp() / getMaxHP()) * bloodLength, Blood->getContentSize().height));
	EXP_sprite->setContentSize(Size(((float)getEXP() / getMaxEXP()) * bloodLength, EXP_sprite->getContentSize().height));
	setATK(getATK() + 20);//增加攻击力
	setMaxEXP(getMaxEXP() + 100);//增加升级所需经验值
}

void Biology::ExpUp(int exp)
{
	if (getEXP() + exp >= getMaxEXP())
	{
		while (getEXP() + exp >= getMaxEXP())
		{
			setEXP(getEXP() + exp - getMaxEXP());
			LevelUp();
		}
	}
	else
	{
		setEXP(getEXP() + exp);
		EXP_sprite->setContentSize(Size(((float)getEXP() / getMaxEXP()) * bloodLength, EXP_sprite->getContentSize().height));
	}
	EXPUIupdate();
	HPUIupdate();
}


void Biology::UIinit()
{
	if (m_sprite)
	{
		//经验条部分初始化
		EXP_Box = Sprite::create("EXPBox.png");
		EXP_Box->setPosition(Vec2(0, m_sprite->getContentSize().height));
		EXPLength = EXP_Box->getContentSize().width;
		this->addChild(EXP_Box, 2);
		EXP_sprite = Sprite::create("EXP.png");
		EXP_sprite->setPosition(Vec2(-EXP_sprite->getContentSize().width / 2, m_sprite->getContentSize().height - EXP_sprite->getContentSize().height / 2));
		EXP_sprite->setContentSize(Size(((float)getEXP() / getMaxEXP()) * EXPLength, EXP_sprite->getContentSize().height));
		EXP_sprite->setAnchorPoint(Vec2::ZERO);
		this->addChild(EXP_sprite, 1);
		EXPUIupdate();
		//血条部分初始化
		Blood_Box = Sprite::create("bloodBox.png");
		Blood_Box->setPosition(Vec2(0, m_sprite->getContentSize().height + EXP_sprite->getContentSize().height));
		bloodLength = Blood_Box->getContentSize().width;
		this->addChild(Blood_Box, 2);
		Blood = Sprite::create("blood.png");
		Blood->setPosition(Vec2(-Blood->getContentSize().width / 2, m_sprite->getContentSize().height + Blood->getContentSize().height / 2));
		Blood->setContentSize(Size(((float)getRealHp() / getMaxHP()) * bloodLength, Blood->getContentSize().height));
		Blood->setAnchorPoint(Vec2::ZERO);
		this->addChild(Blood, 1);
		HPUIupdate();
	}
	
}

void Biology::HPUIupdate()
{
	if (HPMsg)
	{
		HPMsg->setString(StringUtils::format(" %d / %d", getRealHp(), getMaxHP()));
		Blood->setContentSize(Size(((float)getRealHp() / getMaxHP()) * bloodLength, Blood->getContentSize().height));
	}
	else
	{
		HPMsg = Label::createWithSystemFont(StringUtils::format(" %d / %d", getRealHp(), getMaxHP()), "Arial", 20);
		HPMsg->setPosition(Vec2(Blood_Box->getContentSize().width / 2, Blood_Box->getContentSize().height / 2));
		
		Blood_Box->addChild(HPMsg,3);
	}
	
	
	
}

void Biology::EXPUIupdate()
{
	if (EXPMsg)
	{
		EXPMsg->setString(StringUtils::format("Lv %d  %d / %d", getLevel(), getEXP(), getMaxEXP()));
	}
	else
	{
		EXPMsg = Label::createWithSystemFont(StringUtils::format("Lv %d  %d / %d", getLevel(), getEXP(), getMaxEXP()), "Arial", 20);
		EXPMsg->setPosition(Vec2(EXP_Box->getContentSize().width / 2, EXP_Box->getContentSize().height / 2));
		EXP_Box->addChild(EXPMsg, 3);
	}
	
}
