#include "Guns.h"
namespace Sedna {

	Sedna::Gun::Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, unsigned int AMMO, float RATEOFFIRE) :
		name(NAME),
		damage(DAMAGE),
		rateOfFire(RATEOFFIRE),
		projLimit(PROJLIMIT),
		ammo(AMMO)
	{
		originalAmmo = ammo;
		if (name == "olReliable")
			sprite = cocos2d::Sprite::create("gun1.png");
		else if (name == "bloodyMary")
			sprite = cocos2d::Sprite::create("gun2.png");
		else if (name == "theBiggestIron")
			sprite = cocos2d::Sprite::create("gun3.png");
#ifdef _DEBUG
		else
			exit(std::stoi("no sprite created"));
#endif

	}

	Sedna::Gun::Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, float RATEOFFIRE) :
		name(NAME),
		damage(DAMAGE),
		rateOfFire(RATEOFFIRE),
		projLimit(PROJLIMIT),
		ammo(100000000000)//"unlmited ammo"
	{
		originalAmmo = ammo;
		sprite = cocos2d::Sprite::create("gun1.png");
	}

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

	unsigned int Gun::getOriginalAmmo() const
	{
		return originalAmmo;
	}

	Gun* Guns::olReliable = new Gun("olReliable", 2, 4, 0.35f);
	Gun* Guns::bloodyMary = new Gun("bloodyMary", 3, 10, 10, 0.85f);
	Gun* Guns::theBiggestIron = new Gun("theBiggestIron", 1, 10, 100, 0.089f);

}
