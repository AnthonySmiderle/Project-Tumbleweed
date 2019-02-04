#include "Table.h"

Sedna::Table::Table(float x, float y)   {
	this->sprite = cocos2d::Sprite::create("Table.png");
	this->hitBox = new CirclePrimitive(cocos2d::Vec2(x, y),20,5,50);
}
void Sedna::Table::spriteSwitch()
{	
	sprite->setTexture("TableKnocked.png");
}

