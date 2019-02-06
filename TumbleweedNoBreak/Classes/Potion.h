#pragma once
#include "GameObject.h"
#include "Player.h"
namespace Sedna {
	enum potionType
	{
		health,
		rapid,
		invinc
	};
	class Potion : public GameObject{
	public:
		Potion(potionType t, cocos2d::Vec2 pos);
		void pickUp(Player* p);
		~Potion();
		
	private:
		const std::string potionNameList[3] = {"healthPotion.png","rapidPotion.png","invinciblePotion.png"};
		potionType type;
	};


}