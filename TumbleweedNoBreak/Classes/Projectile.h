#pragma once
#include "GameObject.h"
namespace Sedna {
	enum Team {
		Ally,
		Enemy

	};
class Projectile {
public:

	Projectile();
	~Projectile();

	void setDamage(unsigned int DAMAGE);
	unsigned int getDamage() const;

protected:
	GameObject *projectileGameObject;
	unsigned int team;
	unsigned int damage;

};

class PistolBullet : Projectile {
public:

	PistolBullet();
	~PistolBullet();

private:


};
}