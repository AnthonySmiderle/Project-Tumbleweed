#pragma once
#include "GameObject.h"
#include "Enums and Typdefs.h"

namespace Sedna {
	class Table : public GameObject  {
	public:
		Table(float x, float y);// : hasDrink(false) {};
		
		void spriteSwitch();
		void collideTable(Table* table);
	private:
	};
}