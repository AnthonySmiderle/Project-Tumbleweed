#pragma once
#include "GameObject.h"

namespace Sedna {
	class Table : public GameObject  {
	public:
		Table(float x, float y);

		void spriteSwitch();

	};
}