#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include <cstdlib>
#include <random>
#include <ctime>
namespace Sedna {
	class Outlaw : public GameObject {
	public:
		Outlaw(float x, float y);
		
		HP getHP() const;
		void setHP(HP hp);
	protected:
		HP enemyHp = 3;
		int x = 0;

	};

	




}