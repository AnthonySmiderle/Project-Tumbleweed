#pragma once
#include "GameObject.h"
namespace Sedna {
	enum Team {
		Ally,
		Enemy

	};

///<projectiles>
class Projectile : public GameObject {
public:

	Projectile(float x, float y);
	Projectile();
	~Projectile();

	void setDamage(unsigned int DAMAGE);
	unsigned int getDamage() const;

protected:
	unsigned int team;
	unsigned int damage;

};



}