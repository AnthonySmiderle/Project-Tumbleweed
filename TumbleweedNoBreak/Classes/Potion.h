#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enums and Typdefs.h"
namespace Sedna {
	class Potion{
	public:
		Potion() : type(blank){}
		Potion(potionType t) : type(t) {}
		void pickUp(Player* p);
		~Potion();
		potionType getType();
		void setType(potionType a);
		
	private:
		potionType type;
	};


}