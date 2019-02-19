#pragma once
#include "GameObject.h"
#include "Projectile.h"

namespace Sedna {

	class Gun : public GameObject {
	public:
		Gun(const char* NAME,unsigned int DAMAGE, unsigned int PROJLIMIT,float RATEOFFIRE);
		Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, unsigned int AMMO,float RATEOFFIRE);


		const char* getName() const;
		void setGunTimer(float t);
		float getGunTimer() const;
		bool getHasShot() const;
		void setHasShot(bool YN);
		unsigned int getAmmo() const;
		unsigned int getDamage() const;
		unsigned int getProjLimit() const;
		float getRateOfFire() const;
	protected:
		const char* name;
		unsigned int ammo;
		unsigned int damage;
		unsigned int projLimit;
		float rateOfFire;

		float gunTimer = 0.0f;
		bool hasShot = false;
	};

	



}


