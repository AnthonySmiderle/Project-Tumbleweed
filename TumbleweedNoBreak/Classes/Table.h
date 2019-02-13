#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"

namespace Sedna {
	class Table : public GameObject  {
	public:
		Table(float x, float y);// : hasDrink(false) {};

		void spriteSwitch();
		bool hasDrink;
		void checkCollision(std::vector<Table*>& tableList);
	private:
		
	};
}