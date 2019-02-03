#pragma once
#include "GameObject.h"

namespace Sedna {
	class Table  {
	public:
		Table();

		void spriteSwitch(cocos2d::Scene* myB);
		GameObject *getGameObject() const;

	private:
		GameObject* tableGameObject;
	};
}