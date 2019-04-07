#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enums and Typdefs.h"
namespace Sedna {
	class Potion{
	public:
		Potion() : type(blank){}
		Potion(potionType t) : type(t) {}
		~Potion();
		potionType getType();
		void setType(potionType a);
		
	private:
		potionType type;//this is the potion object it basically just stores a type of data, more features were planned and cut so they still have their own class
	};


}