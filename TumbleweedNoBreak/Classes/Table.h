#pragma once
#include "GameObject.h"
//#include "Enums and Typdefs.h"

namespace Sedna {
	class Potion;
	class Table : public GameObject  {
	public:
		Table(float x, float y);// : hasDrink(false) {};

		void spriteSwitch();
		void collideTable(Table* table);
		potionType getBeer();
		void setBeer(potionType a);
		bool knocked = false;
	private:
		Potion* beer;
	};
}