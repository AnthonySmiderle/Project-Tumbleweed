#include "Projectile.h"
namespace Sedna{
Projectile::Projectile(float x, float y, Team t)
{
	sprite = cocos2d::Sprite::create("bullet2.png");
	hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 3, 5, 30);
	team = t;
}

Projectile::Projectile()
{
}

void Projectile::setDamage(unsigned int DAMAGE)
{
}
unsigned int Projectile::getDamage() const
{
	return damage;
}

}
