#pragma once
#include "GameObject.h"
namespace Sedna {
	enum Team {
		Ally,
		Enemy

	};

///<projectiles>
class Projectile : GameObject {
public:

	Projectile();
	~Projectile();

	void setDamage(unsigned int DAMAGE);
	unsigned int getDamage() const;

protected:
	unsigned int team;
	unsigned int damage;

};


///<might not need this>
class PistolBullet : Projectile {
public:

	PistolBullet();
	~PistolBullet();

private:


};
}