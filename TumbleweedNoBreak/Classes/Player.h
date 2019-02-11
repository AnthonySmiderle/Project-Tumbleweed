#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "XinputManager.h"
#include "Projectile.h"
#include <vector>
namespace Sedna {


	
class Player : public GameObject
{
public:
	Player() {}
	Player(int wPlayer, float x, float y, XinputController* PCONTROLLER,Stick pSticks[2],Triggers pTriggers);
	~Player();

	//extend member functions here
	
	void checkInput(float dt);
	void shoot(float dt, cocos2d::Scene* s);
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
