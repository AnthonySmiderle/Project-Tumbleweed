#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "Projectile.h"
#include <vector>

namespace Sedna {
	class Player;
	class Table;
	class Outlaw : public GameObject {
	public:
		Outlaw(float x, float y);
	
		void shoot(float dt,cocos2d::Scene* s);
		void checkList();
		void removeProjectiles();
		void checkBCollision(Player* p);
		void checkBCollision(std::vector<Table*>& tableList);
	private:
		std::vector<Projectile*> eProjectiles;
		float eShootTimer = 0.0f;
		bool eHasShot = false;
	protected:
		int x = 0;

	};






	class Pete : public GameObject
	{
	public:
		Pete(float x, float y);
		void spawnDyna(float dt, cocos2d::Scene* s);
		void checkList();
		void removeDyna();
	private:
		std::vector<Projectile*> eDyna;
		float eDynaTimer = 0.0f;
		bool ehasDynaPlace = false;
	protected:
		int x = 0;

	};
	




}