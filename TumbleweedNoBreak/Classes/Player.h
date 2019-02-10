#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "XinputManager.h"
namespace Sedna {


	
class Player : public GameObject
{
public:
	Player() {}
	Player(int wPlayer, float x, float y);
	~Player();

	//extend member functions here
	
	void shoot();
private:


};

}
