#include "character.h"
#include "Controller.h"
#include "GameManager.h"
#include "GameDataManager.h"
#include "DBUtil.h"

State character::getState()//���״̬
{
	if (m_Controller)
	{
		return m_Controller->getState();
	}
	else
		return State::Staying;
}

Dir character::getDir()//���1����
{
	if (m_Controller)
		return m_Controller->getDir();
	else
		return Dir::DIR_LEFT;
}

void character::setDir(Dir dir)//���÷���
{
	if (m_Controller)
		m_Controller->setDir(dir);
}

void character::setState(State state)//����״̬
{
	if (m_Controller)
		m_Controller->setState(state);
}


void character::readDataFromDB()
{
	DBUtil::initDB("IMAStory.db");
	setMaxHP(DBUtil::getIntDataByName("Character", "Frost", (int)characterData::MaxHP));
	setRealHp(DBUtil::getIntDataByName("Character", "Frost", (int)characterData::RealHP));
	setMaxEXP(DBUtil::getIntDataByName("Character", "Frost", (int)characterData::MaxEXP));
	setEXP(DBUtil::getIntDataByName("Character", "Frost", (int)characterData::EXP));
	setLevel(DBUtil::getIntDataByName("Character", "Frost", (int)characterData::Level));
	setATK(DBUtil::getIntDataByName("Character", "Frost", (int)characterData::ATK));

	log(u8"�������ֵ:%d", getMaxHP());
	log(u8"����ֵ:%d", getRealHp());
	log(u8"�������辭��ֵ:%d", getMaxEXP());
	log(u8"��ǰ����ֵ:%d", getEXP());
	log(u8"�ȼ�:%d", getLevel());
	log(u8"������:%d", getATK());
}
void character::readDataFromJson()
{
	auto archice = GameDataManager::getInstance()->getArchiceData();
	setLevel(archice.Level);
	setMaxHP(1000 + 100 * (archice.Level - 1));
	setRealHp(archice.HP);
	setMaxEXP(500 + 100 * (archice.Level - 1));
	setEXP(archice.EXP);
	setATK(100 + 5 * (archice.Level - 1));
	log(u8"�������ֵ:%d", getMaxHP());
	log(u8"����ֵ:%d", getRealHp());
	log(u8"�������辭��ֵ:%d", getMaxEXP());
	log(u8"��ǰ����ֵ:%d", getEXP());
	log(u8"�ȼ�:%d", getLevel());
	log(u8"������:%d", getATK());
}
void character::ReLife()
{
	this->setPosition(Director::getInstance()->getVisibleOrigin());
	this->setRealHp(getMaxHP());
	this->HPUIupdate();
	this->setIsDead(false);
}
void character::Flip()
{
	switch (getDir())
	{
	case Dir::DIR_LEFT:
		do
		{
			if (getIsRight())
			{
				m_sprite->setFlippedX(true);
				setIsRight(false);
			}
		} while (false);
		break;
	case Dir::DIR_RIGHT:
		do
		{
			if (!getIsRight())
			{
				m_sprite->setFlippedX(false);
				setIsRight(true);
			}
		} while (false);
		break;
	default:
		break;
	}
}
//
//void character::setTiledMap(TMXTiledMap * map)
//{
//	this->m_map = map;
//}



void character::setTagPosition(float x, float y)
{

}

void character::LoadAction()
{
}

void character::AttributesInit()
{
}

void character::Move()
{
}

void character::Stay()
{
}

void character::Attack()
{
}

void character::BeingAttack()
{
}

void character::QTE()
{
}


