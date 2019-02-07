#pragma once
#include "GameObject.h"

namespace Sedna {
	class Table : public GameObject  {
	public:
		Table(float x, float y);// : hasDrink(false) {};

		void spriteSwitch();
		bool hasDrink;

	};
}