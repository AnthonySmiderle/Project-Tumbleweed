#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
namespace Sedna {


	//inherited deconstrucotr...no memory leaks here!
	class Projectile : public GameObject {
	public:
		Projectile(float x, float y, Team t);
		Projectile();

	protected:
		unsigned int team;

	};



}