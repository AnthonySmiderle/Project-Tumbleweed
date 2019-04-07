#include "Projectile.h"
namespace Sedna{
Projectile::Projectile(float x, float y, Team t)
{
	//in the end, the team aspect of projectiles was never used but yeah this is all the projectiles are
	sprite = cocos2d::Sprite::create("bullet2.png");
	hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 3, 5, 30);
	team = t;
}

Projectile::Projectile()
{
}


}
