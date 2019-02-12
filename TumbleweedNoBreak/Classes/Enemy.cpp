#include "Enemy.h"
#include "baseObjectManager.h"
namespace Sedna {

Sedna::Outlaw::Outlaw(float x, float y)
{
	
	sprite = cocos2d::Sprite::create("enemy1.png");

	hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);

		
}

HP Sedna::Outlaw::getHP() const
{
	return this->enemyHp;
}
void Outlaw::setHP(HP hp)
{
	enemyHp = hp;
}
void Outlaw::shoot(float dt,cocos2d::Scene* s)
{
	if (eShootTimer > 0.3f) {
		eShootTimer = 0.0f;
		eHasShot = false;
	}
	if (!eShootTimer) {
		eHasShot = true;
		Projectile* eBaseProjectile = new Sedna::Projectile(-1000, 10, Enemy);
		s->addChild(eBaseProjectile->getBox()->getDrawNode());
		s->addChild(eBaseProjectile->getSprite());

		eProjectiles.push_back(new Sedna::Projectile(*eBaseProjectile));
		BaseObjectManager::eProjectileBObjects.push_back(eBaseProjectile);

		eProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation());
		eProjectiles.back()->getBox()->setForce(cocos2d::Vec2(0, -5));
	}
	if (eHasShot)
		eShootTimer += dt;
}
void Outlaw::checkList()
{
	if (eProjectiles.size() > 4) {
		eProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
		eProjectiles.front()->getSprite()->removeFromParent();
		eProjectiles.erase(eProjectiles.begin());
	}
	for (int i = 0; i < eProjectiles.size(); i++)
		eProjectiles[i]->updateGameObject();
}
void Outlaw::removeProjectiles()
{
	for (int i = 0; i < eProjectiles.size(); i++) {
		eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
		eProjectiles[i]->getSprite()->removeFromParent();
		eProjectiles.erase(eProjectiles.begin() + i);
		BaseObjectManager::eProjectileBObjects.erase(BaseObjectManager::eProjectileBObjects.begin() + i);
		i--;
	}
}
}		
