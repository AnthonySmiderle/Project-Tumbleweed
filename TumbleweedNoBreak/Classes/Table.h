#pragma once
#include "GameObject.h"

namespace Sedna {
	class Potion;
	class Table : public GameObject  {//extends gameObject
	public:
		Table(float x, float y);//constructors
		Table(float x, float y,int p);
		void spriteSwitch();
		void collideTable(Table* table);//for colliding tables
		potionType getBeer();//getter
		void setBeer(potionType a);//setter
		bool knocked = false;
	private:
		Potion* beer;
	};
}