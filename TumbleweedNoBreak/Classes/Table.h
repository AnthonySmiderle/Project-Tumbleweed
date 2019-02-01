#pragma once
#include "GameObject.h"

namespace Sedna {
	class Table  {
	public:
		Table();

		void spriteSwitch();
		GameObject getGameObject() const;

	private:
		GameObject* tableGameObject;
	};
}