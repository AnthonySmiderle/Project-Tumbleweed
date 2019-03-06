#include "Guns.h"
namespace Sedna {

	Sedna::Gun::Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, unsigned int AMMO, float RATEOFFIRE) :
		name(NAME),
		damage(DAMAGE), 
		rateOfFire(RATEOFFIRE), 
		projLimit(PROJLIMIT),
		ammo(AMMO) {}

	Sedna::Gun::Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, float RATEOFFIRE) :
		name(NAME),
		damage(DAMAGE),
		rateOfFire(RATEOFFIRE),
		projLimit(PROJLIMIT),
		ammo(100000000000)//"unlmited ammo"
	{}

	const char * Gun::getName() const
	{
		return name;
	}

	void Gun::setGunTimer(float t)
	{
		gunTimer = t;
	}

	float Gun::getGunTimer() const
	{
		return gunTimer;
	}

	bool Gun::getHasShot() const
	{
		return hasShot;
	}

	void Gun::setHasShot(bool YN)
	{
		hasShot = YN;
	}

	void Gun::setAmmo(unsigned int AMMO)
	{
		ammo = AMMO;
	}

	unsigned int Gun::getAmmo() const
	{
		return ammo;
	}

	unsigned int Sedna::Gun::getDamage() const
{
	return damage;
}

unsigned int Sedna::Gun::getProjLimit() const
{
	return projLimit;
}

float Sedna::Gun::getRateOfFire() const
{
	return rateOfFire;
}
}
