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
		virtual ~Outlaw();

		virtual void shoot(float dt,cocos2d::Scene* s);
		virtual void checkList();
		virtual void removeProjectiles();
		virtual void checkBCollision(Player* p);
		virtual void checkBCollision(std::vector<Table*>& tableList);
		unsigned int points = 100;//this is public because there really isn't a reason to keep it private
	protected:
		std::vector<Projectile*> eProjectiles;
		float eShootTimer = 0.0f;
		bool eHasShot = false;

	};

	class ShotgunOutlaw : public Outlaw {
	public:
		ShotgunOutlaw(float x, float y);
		void shoot(float dt, cocos2d::Scene* s) override;
		void checkList() override;

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