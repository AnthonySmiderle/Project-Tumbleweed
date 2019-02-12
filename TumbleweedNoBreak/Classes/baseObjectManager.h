#pragma once
#include <vector>
namespace Sedna {
	class Projectile;
	class Outlaw;
	class BaseObjectManager {
	public:
		BaseObjectManager();
		static std::vector<Projectile*>eProjectileBObjects;
		static std::vector<Projectile*> pProjectileBObjects;
		static std::vector<Outlaw*> outlawBObjects;


	};
	
}