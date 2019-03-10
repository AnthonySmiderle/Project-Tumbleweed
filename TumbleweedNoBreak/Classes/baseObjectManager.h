#pragma once
#include <vector>
namespace Sedna {
	class Projectile;
	class Outlaw;
	class Table;
	class Gun;
	class Powerup;
	class BaseObjectManager {
	public:
		static std::vector<Gun*>gunBObjects;
		static std::vector<Table*>tableBObjects;
		static std::vector<Projectile*>eProjectileBObjects;
		static std::vector<Projectile*> pProjectileBObjects;
		static std::vector<Outlaw*> outlawBObjects;
	private:
		BaseObjectManager();

	};
	
}