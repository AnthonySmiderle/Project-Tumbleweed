#include "Projectile.h"
namespace Sedna{
Projectile::Projectile()
{
	//projectileGameObject = new GameObject("table.jpg",)
}
Projectile::~Projectile()
{
}
void Projectile::setDamage(unsigned int DAMAGE)
{
}
unsigned int Projectile::getDamage() const
{
	return damage;
}
PistolBullet::PistolBullet()
{
}
PistolBullet::~PistolBullet()
{
	//delete this; lol
}
}
