#pragma once
#include "GameObject.h"
#include "Projectile.h"

namespace Sedna {

	class Gun : public GameObject {
	public:
		Gun(const char* NAME,unsigned int DAMAGE, unsigned int PROJLIMIT,float RATEOFFIRE);
		Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, unsigned int AMMO,float RATEOFFIRE);

		~Gun();

		const char* getName() const;
		void setGunTimer(float t);
		float getGunTimer() const;
		bool getHasShot() const;
		void setHasShot(bool YN);
		void setAmmo(unsigned int AMMO);
		unsigned int getAmmo() const;
		unsigned int getDamage() const;
		unsigned int getProjLimit() const;
		float getRateOfFire() const;

		unsigned int getOriginalAmmo() const;
	protected:
		const char* name;
		unsigned int originalAmmo;
		unsigned int ammo;
		unsigned int damage;
		unsigned int projLimit;
		float rateOfFire;

		float gunTimer = 0.0f;
		bool hasShot = false;
	};

	class Guns {
	public:
		~Guns() {
			delete olReliable;
			delete bloodyMary;
			delete theBiggestIron;
			delete olReliable2;
			delete bloodyMary2;
			delete theBiggestIron2;
		}
		static Gun* olReliable;
		static Gun* bloodyMary;
		static Gun* theBiggestIron;
		static Gun* olReliable2;
		static Gun* bloodyMary2;
		static Gun* theBiggestIron2;
	};



}


