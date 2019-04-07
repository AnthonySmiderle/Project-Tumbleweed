#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "Projectile.h"
#include <vector>

namespace Sedna {
	//forward declaring these classes
	class Player;
	class Table;

	//base class
	class Outlaw : public GameObject {
	public:
		Outlaw(float x, float y);
		virtual ~Outlaw();

		//get projectiles 
		std::vector<Projectile*> getEProjectiles() const { return eProjectiles; }
		//virtual functions
		virtual void shoot(float dt, cocos2d::Scene* s);
		virtual void checkList();
		virtual void removeProjectiles();
		virtual void animate(float dt);

		//check the collision of the bullets with the player passed in
		void checkBCollision(Player* p);
		//check bullet collision with tables
		void checkBCollision(std::vector<Table*>& tableList);
		unsigned int points = 100;//this is public because there really isn't a reason to keep it private

	protected:
		float animationTimer = 0.0f;
		bool hasAnimation = false;
		
		//projectiles that the outlaw has
		std::vector<Projectile*> eProjectiles;
		float eShootTimer = 0.0f;
		bool eHasShot = false;

	};

	class ShotgunOutlaw : public Outlaw {
	public:
		ShotgunOutlaw(float x, float y);
		void animate(float dt) override;
		void shoot(float dt, cocos2d::Scene* s) override;
		void checkList() override;
		//checks the position relative to the player
		void onLeftSideOf(Player*p);
	private:
		bool onLeft = false;

	};

	class RifleOutlaw : public Outlaw {
	public:
		RifleOutlaw(float x, float y);
		void animate(float dt) override;
		void shoot(float dt, cocos2d::Scene* s) override;

		//gets the tracking vector
		cocos2d::Vec2 getTrack() const;
		void setTrack(Player* p);
	private:
		cocos2d::Vec2 track;

	};


	class CrazyPete : public Outlaw {
	public:
		CrazyPete(float x, float y);
		~CrazyPete();
		void animate(float dt) override;
		void removeProjectiles() override;
		void shoot(float dt, cocos2d::Scene* s) override;
		void checkList() override;

		void updateDyn(float dt, cocos2d::Scene* s);
		Projectile* getDyn() const { return dynamite; }
	private:
		Projectile* dynamite;
	};


	class Goldman : public Outlaw {
	public:
		Goldman(float x, float y);
		~Goldman();
		void shoot(float dt, cocos2d::Scene*s, CirclePrimitive* c);
		void animate(float dt) override;
		void checkList() override;
		SquarePrimitive* getHealthBar() const;
	private:
		bool playedMadSound = false;
		cocos2d::Vec2 phase2Vec{ -5,0 };
		SquarePrimitive* healthBar;
		bool switche = false;
		bool phase1 = true;
		bool phase2 = false;
		bool phase3 = false;
	};



}