#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "Projectile.h"
#include <vector>

namespace Sedna {
	
	class Outlaw : public GameObject {
	public:
		Outlaw(float x, float y);
	
		void shoot(float dt,cocos2d::Scene* s);
		void checkList();
		void removeProjectiles();
	private:
		std::vector<Projectile*> eProjectiles;
		float eShootTimer = 0.0f;
		bool eHasShot = false;
	protected:
		int x = 0;

	};

	




}