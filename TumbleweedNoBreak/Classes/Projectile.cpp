#include "Projectile.h"
namespace Sedna{
Projectile::Projectile(float x,float y)
{
	//projectileGameObject = new GameObject("table.jpg")
	sprite = cocos2d::Sprite::create("bullet.jpg");
	hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);
}
Projectile::~Projectile()
{
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
