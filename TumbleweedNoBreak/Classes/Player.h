#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "XinputManager.h"
#include "Projectile.h"
#include "Enemy.h"
#include "baseObjectManager.h"
#include <vector>
namespace Sedna {



	class Player : public GameObject
	{
	public:
		Player() {}
		Player(int wPlayer, float x, float y,XinputManager X);
		~Player();

		//extend member functions here

		void checkInput(float dt);
		void shoot(float dt, cocos2d::Scene* s);
		void checkList();
		void checkBCollision(std::vector<Outlaw*>& outlawList);
	
		std::vector<Projectile*> getpProjectile() const;
	private:
		XinputController* pController;
		Stick pSticks[2];
		Triggers pTriggers;

		float tumbleTimer = 0.0f;
		bool isTumbling = false;

		float gunTimer = 0.0f;
		bool hasShot = false;

		std::vector<Projectile*> pProjectiles;

	};

}
