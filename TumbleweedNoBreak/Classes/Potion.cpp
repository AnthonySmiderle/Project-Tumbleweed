#include "Potion.h"
namespace Sedna {


	void Sedna::Potion::pickUp(Player * p)
	{

	}

	Sedna::Potion::~Potion()
	{

	}
	potionType Potion::getType()
	{
		return type;
	}
	void Potion::setType(potionType a)
	{
		type = a;
	}
}
