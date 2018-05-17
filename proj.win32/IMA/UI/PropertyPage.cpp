#include "PropertyPage.h"
#include "GameManager.h"
#include "character.h"
bool PropertyPage::init()
{
	return true;
}

void PropertyPage::PropertyUpdate()
{
	if (!HP || !EXP || !ATK)
	{
		auto character = GameManager::getInstance()->getCharacter();
		box = Sprite::create("PBox.png");
		box->setAnchorPoint(Vec2::ZERO);
		this->addChild(box);
		auto ico = Sprite::create("ICO01.png");
		ico->setPosition(box->getContentSize().width / 2, box->getContentSize().height - ico->getContentSize().height / 2 - 20);
		this->addChild(ico);
		Name = Label::createWithSystemFont(StringUtils::format("Name:Joker.Jokey"), "Arial", 20);
		Name->setPosition(Vec2(30, 130));
		Name->setAnchorPoint(Vec2::ZERO);
		this->addChild(Name);
		HP = Label::createWithSystemFont(StringUtils::format("HP: %d / %d", character->getRealHp(), character->getMaxHP()), "Arial", 20);
		HP->setPosition(Vec2(30, 100));
		HP->setAnchorPoint(Vec2::ZERO);
		this->addChild(HP);
		EXP = Label::createWithSystemFont(StringUtils::format("Lv: %d  EXP: %d / %d", character->getLevel(), character->getEXP(), character->getMaxEXP()), "Arial", 20);
		EXP->setPosition(Vec2(30, 70));
		EXP->setAnchorPoint(Vec2::ZERO);
		this->addChild(EXP);
		ATK = Label::createWithSystemFont(StringUtils::format("Atk: %d", character->getATK()), "Arial", 20);
		ATK->setPosition(Vec2(30, 40));
		ATK->setAnchorPoint(Vec2::ZERO);
		this->addChild(ATK);
	}
	auto character = GameManager::getInstance()->getCharacter();
	HP->setString(StringUtils::format("HP: %d / %d", character->getRealHp(), character->getMaxHP()));
	EXP->setString(StringUtils::format("Lv %d  %d / %d", character->getLevel(), character->getEXP(), character->getMaxEXP()));
	ATK->setString(StringUtils::format("Atk: %d", character->getATK()));
}
