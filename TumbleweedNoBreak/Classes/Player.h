#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "XinputManager.h"
#include "Enemy.h"
#include "Guns.h"
#include "Table.h"
#include <vector>
#include "Animations.h"
namespace Sedna {

	class Powerup;

	class SednaUI {
	public:
		SednaUI(Gun* currentGun, Player* p, int args, ...);


		std::vector<cocos2d::Label*> getLabelList() const;
		cocos2d::Sprite* getUIGunSprite() const;
		std::vector<cocos2d::Sprite*> getHPSprites() const;
		void setUIGunSprite(cocos2d::Sprite* s);


		void updatePosition(cocos2d::Vec2 p);
		void updateList();
	private:
		Player* p;
		cocos2d::Sprite* hp1;
		cocos2d::Sprite* hp2;
		cocos2d::Sprite* hp3;
		std::vector<cocos2d::Sprite*> hpSprites;
		std::vector<cocos2d::Label*> labelList;
		Gun* currentGun;
		cocos2d::Sprite* uiGunSprite;


	};

	class Player : public GameObject
	{
	public:
		Player() {}
		Player(int wPlayer, float x, float y, XinputManager MANAGER, Gun* CURRENTGUN);
		~Player();

		//extend member functions here

		XinputController* getController() const { return pController; }//getters
		Gun* getCurrentGun() const { return currentGun; }
		int getPlayerNumber() const { return playerNumber; }
		unsigned int getScore() const;
		void die();//a helpful function to kill the player
		void setCurrentGun(Gun* g);//setter
		void checkInput();//player input
		void shoot(cocos2d::Scene* s);
		void checkList();
		void checkBCollision(std::vector<Outlaw*>& outlawList, Powerup* power1, Powerup* power2, cocos2d::Scene* s);
		void checkBCollision(std::vector<Table*>& tableList);
		void checkTableStuff(std::vector<Table*>& tableList, Sedna::Player*);//collisions
		void updateInvince();//invincibility frames
		bool getInvinc()const;//getter
		void wasHurt();
		bool isDead();//getter
		void setScore(const unsigned int);//score setter
		SednaUI* getUI() const;

		void setGun(Gun* g);

		std::vector<Projectile*> getpProjectile() const;

		///<used for tutorial purposes only>
		bool usedBt = false;
		bool hasMoved() const { return moved; }
		bool usedShot() const { return shot; }
		///<not to be confused with xinput>
		bool pressedA() const { return kickedTable; }

	private:
		///<used for tutorial purposes only>
		bool moved = false;
		bool shot = false;
		bool kickedTable = false;

		std::vector<cocos2d::ParticleExplosion*> particles;
		bool isAimingLeft = false;//what direction the player is aiming at
		bool isAimingRight = false;
		float animationTimer = 0.0f;
		bool hasAnimation = false;//animations
		float vibrationTimer = 0.0f;
		int playerNumber;
		unsigned int score = 0;
		bool takeInputs = true;
		SednaUI* playerUI;
		XinputController* pController;
		Stick pSticks[2];
		Triggers pTriggers;
		Gun* currentGun;

		float invincTimer = 0.0f;

		std::vector<Projectile*> pProjectiles;

	};

}
