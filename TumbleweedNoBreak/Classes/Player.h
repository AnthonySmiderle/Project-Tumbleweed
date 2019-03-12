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


	
	class SednaUI {
	public:
		SednaUI(Gun* currentGun,Player* p, int args, ...);
		//a ui has
		//a sprite
		//labels
		//bars - make bar class later

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
		Player(int wPlayer, float x, float y,XinputManager MANAGER,Gun* CURRENTGUN);
		~Player();

		//extend member functions here

		XinputController* getController() const { return pController; }
		Gun* getCurrentGun() const { return currentGun; }
		
		int getPlayerNumber() const { return playerNumber; }
		unsigned int getScore() const;
		void die();
		void setCurrentGun(Gun* g);
		void checkInput(float dt);
		void shoot(float dt, cocos2d::Scene* s);
		void checkList();
		void checkBCollision(std::vector<Outlaw*>& outlawList,Powerup* power1,Powerup* power2);
		void checkBCollision(std::vector<Table*>& tableList);
		void checkTableStuff(std::vector<Table*>& tableList);
		void update(float dt);
		
		SednaUI* getUI() const;

		void setGun(Gun* g);
	
		std::vector<Projectile*> getpProjectile() const;
	private:
		float animationTimer = 0.0f;
		bool hasAnimation = false;
		float vibrationTimer = 0.0f;
		int playerNumber;
		unsigned int score = 0;
		bool takeInputs = true;
		SednaUI* playerUI;
		XinputController* pController;
		Stick pSticks[2];
		Triggers pTriggers;
		Gun* currentGun;

		float tumbleTimer = 0.0f;
		bool isTumbling = false;
		float invincTimer = 0.0f;

		std::vector<Projectile*> pProjectiles;

	};

}
