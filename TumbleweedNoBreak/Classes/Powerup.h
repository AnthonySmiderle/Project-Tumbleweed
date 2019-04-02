#pragma once
#include "GameObject.h"

namespace Sedna {
	class Player;
	class Gun;
	class Powerup : public GameObject {
	public:
		Powerup(const char* s, Gun* GUN, Gun* GUN2, float x, float y);
		~Powerup();

		void pickUp(Player* p);
		Gun* getGun() const;

	private:

		Gun* gun;
		Gun* gun2;

	};

}