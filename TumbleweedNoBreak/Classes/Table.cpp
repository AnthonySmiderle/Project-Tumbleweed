#include "Table.h"

Sedna::Table::Table(){

	tableGameObject = new GameObject("Table.png", cocos2d::Vec2(200, 200), 10, 5, 50);
	//this->setSprite("TableKnocked.png");
	//this->setCircle(Sedna::CirclePrimitive(cocos2d::Vec2(300, 300), 10, 5, 50));
}
void Sedna::Table::spriteSwitch()
{
	auto temp = cocos2d::Sprite::create("TableKnocked.png");
	this->getGameObject()->setSprite(temp);
}

Sedna::GameObject* Sedna::Table::getGameObject() const
{
	return this->tableGameObject;
}
