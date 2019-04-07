#include "Potion.h"
namespace Sedna {



	Sedna::Potion::~Potion()
	{

	}
	potionType Potion::getType()
	{
		return type;//getter
	}
	void Potion::setType(potionType a)
	{
		type = a;//setter
	}
}
