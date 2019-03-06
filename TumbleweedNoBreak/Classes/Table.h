#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"
#include "Potion.h"

namespace Sedna {
	class Table : public GameObject  {
	public:
		Table(float x, float y);// : hasDrink(false) {};
		Potion beer;
		void spriteSwitch();
		void collideTable(Table* table);
	private:
		
	};
}