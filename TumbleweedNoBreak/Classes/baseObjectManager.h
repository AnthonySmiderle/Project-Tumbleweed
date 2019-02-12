#pragma once
#include <vector>
namespace Sedna {
	class Projectile;
	class Outlaw;
	class Table;
	class BaseObjectManager {
	public:
		BaseObjectManager();
		static std::vector<Table*>tableBObjects;
		static std::vector<Projectile*>eProjectileBObjects;
		static std::vector<Projectile*> pProjectileBObjects;
		static std::vector<Outlaw*> outlawBObjects;


	};
	
}