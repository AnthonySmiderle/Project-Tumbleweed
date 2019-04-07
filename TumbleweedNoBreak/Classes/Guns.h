#pragma once
#include "GameObject.h"
#include "Projectile.h"

namespace Sedna {

	class Gun : public GameObject {
	public:
		//one constructor for guns that have infinite ammo
		Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, float RATEOFFIRE);

		//and another for ones that dont
		Gun(const char* NAME, unsigned int DAMAGE, unsigned int PROJLIMIT, unsigned int AMMO, float RATEOFFIRE);

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
		unsigned originalAmmo;
		unsigned ammo;
		unsigned damage;
		unsigned projLimit;
		float rateOfFire;

		float gunTimer = 0.0f;
		bool hasShot = false;
	};

	class Guns {
	public:
		//this is a special class that we made because in our game, there are only 3 guns
		//there are six guns here because we made each player have the ability to access one
		//the reason why these guns are static is so that we can make sure that no data is lost in between when the player picks up and drops their guns
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


