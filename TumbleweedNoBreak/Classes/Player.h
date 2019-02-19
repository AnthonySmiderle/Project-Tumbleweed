#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "XinputManager.h"
#include "Enemy.h"
#include "Guns.h"
#include "baseObjectManager.h"
#include "Table.h"
#include <vector>
namespace Sedna {



	class Player : public GameObject
	{
	public:
		Player() {}
		Player(int wPlayer, float x, float y,XinputManager MANAGER,Gun* CURRENTGUN);
		~Player();

		//extend member functions here

		void checkInput(float dt);
		void shoot(float dt, cocos2d::Scene* s);
		void checkList();
		void checkBCollision(std::vector<Outlaw*>& outlawList);
		void checkBCollision(std::vector<Table*>& tableList);
		void checkTableStuff(std::vector<Table*>& tableList);

		void setGun(Gun* g);
	
		std::vector<Projectile*> getpProjectile() const;
	private:
		XinputController* pController;
		Stick pSticks[2];
		Triggers pTriggers;

		Gun* currentGun;

		float tumbleTimer = 0.0f;
		bool isTumbling = false;

		

		std::vector<Projectile*> pProjectiles;

	};

}
