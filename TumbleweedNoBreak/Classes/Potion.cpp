#include "Potion.h"


Sedna::Potion::Potion(potionType t, cocos2d::Vec2 pos)
{
	type = t;
	sprite = cocos2d::Sprite::create(potionNameList[t]);
	hitBox = new CirclePrimitive(pos, 20, 5, 30);
}

void Sedna::Potion::pickUp(Player * p)
{
	
}

Sedna::Potion::~Potion()
{
}
