#include "Enemy.h"
namespace Sedna {

Sedna::Outlaw::Outlaw(float x, float y)
{
	
	sprite = cocos2d::Sprite::create("enemy1.png");

	hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);

		
}

HP Sedna::Outlaw::getHP() const
{
	return this->enemyHp;
}
void Outlaw::setHP(HP hp)
{
	enemyHp = hp;
}
}
