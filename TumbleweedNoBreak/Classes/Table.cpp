#include "Table.h"
namespace Sedna {

Sedna::Table::Table(float x, float y)   {
	this->sprite = cocos2d::Sprite::create("Table.png");
	sprite->setScale(0.9f);
	this->hitBox = new CirclePrimitive(cocos2d::Vec2(x, y),28,5,50);
	hitBox->getDrawNode()->setVisible(false);
	this->objectHp = 5;
}
void Sedna::Table::spriteSwitch()
{	
	sprite->setTexture("TableKnocked.png");
}

void Table::checkCollision(std::vector<Table*>& tableList)
{
}


}
