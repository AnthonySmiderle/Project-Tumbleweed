#include "baseObjectManager.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Table.h"
namespace Sedna {

	std::vector<Table*> BaseObjectManager::tableBObjects;
	std::vector<Projectile*> BaseObjectManager::eProjectileBObjects;
	std::vector<Projectile*> BaseObjectManager::pProjectileBObjects;
	std::vector<Outlaw*> BaseObjectManager::outlawBObjects;
	Sedna::BaseObjectManager::BaseObjectManager()
	{

	}
}
