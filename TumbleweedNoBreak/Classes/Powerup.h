#pragma once
#include "GameObject.h"

namespace Sedna {
	class Player;
	class Gun;
	class Powerup : public GameObject {
	public:
		Powerup(const char* s,Gun* GUN, float x, float y);
		~Powerup() override;

		void pickUp(Player* p);
		Gun* getGun() const;

	private:
		
		Gun* gun;

	};
	
}