#include "Enemy.h"
#include "baseObjectManager.h"
#include "Player.h"
#include "AudioEngine.h"
#include "Table.h"
#include <iostream>
namespace Sedna {

	Sedna::Outlaw::Outlaw(float x, float y)
	{

		sprite = cocos2d::Sprite::create("enemy1.png");
		sprite->setScale(spriteScale);

		hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 24, 5, 30);
		hitBox->getDrawNode()->setVisible(false);

		this->objectHp = 3;
	}
	Outlaw::~Outlaw()
	{

	}
	void Outlaw::shoot(float dt, cocos2d::Scene* s)
	{
		if (eShootTimer > 0.4f) {
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

			eProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-8, 0));
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
	void Outlaw::animate(float dt)
	{
		if (animationTimer > 0.3f) {
			this->getSprite()->setTexture("outlawLl.png");

			hasAnimation = false;
		}
		if (animationTimer > 0.6f) {
			animationTimer = 0.0f;
		}
		if (!animationTimer) {
			this->getSprite()->setTexture("outlawRl.png");
			hasAnimation = true;
		}
		animationTimer += dt;
	}
	void Outlaw::checkBCollision(Player * p)
	{

		for (int i = 0; i < eProjectiles.size(); i++) {
			if (eProjectiles.empty())
				break;


			if (eProjectiles[i]->getBox()->checkCollision(*p->getBox())) {
#ifdef _DEBUG
				if (p->getController()->isButtonReleased(Sedna::LB)) {
					p->setHP(p->getHP() - 1);
					srand(rand() % time(0));
					int random = (rand() %  3) + 1;
					if (p->getPlayerNumber() == 1) {
						if (random == 1)
							cocos2d::experimental::AudioEngine::play2d("p1Hurt.mp3");
						if (random == 2)
							cocos2d::experimental::AudioEngine::play2d("p1Hurt2.mp3");
						if (random == 3)
							cocos2d::experimental::AudioEngine::play2d("p1Hurt3.mp3");
					}
					else {
						if (random == 1)
							cocos2d::experimental::AudioEngine::play2d("p2Hurt.mp3");
						if (random == 2)
							cocos2d::experimental::AudioEngine::play2d("p2Hurt2.mp3");
						if (random == 3)
							cocos2d::experimental::AudioEngine::play2d("p2Hurt3.mp3");
					}
					p->getController()->setVibration(1, 1);///some cheeky shit that might not work
					for (int j = 0; j < p->getUI()->getHPSprites().size(); j++) {
						if (p->getUI()->getHPSprites()[j]->getZOrder() == 21) {
							p->getUI()->getHPSprites()[j]->setZOrder(20);
							p->getUI()->getHPSprites()[j]->setTexture("brokenHeart.png");
							break;
						}
					}
				}
#endif
#ifdef _RELEASE

				p->setHP(p->getHP() - 1);

				for (int j = 0; j < p->getUI()->getHPSprites().size(); j++) {
					if (p->getUI()->getHPSprites()[j]->getZOrder() == 21) {
						p->getUI()->getHPSprites()[j]->setZOrder(20);
						p->getUI()->getHPSprites()[j]->setTexture("brokenHeart.png");
						break;
						}
					}
				}
#endif
			eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
			eProjectiles[i]->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin() + i);
			BaseObjectManager::eProjectileBObjects.erase(BaseObjectManager::eProjectileBObjects.begin() + i);
			if (p->getHP() <= 0)
				p->die();
			}
		}

	}
void Outlaw::checkBCollision(std::vector<Table*>& tableList)
{
	bool check = false;
	for (int i = 0; i < eProjectiles.size(); i++) {
		for (int j = 0; j < tableList.size(); j++) {
			if (eProjectiles.empty())
				break;
			if (eProjectiles[i]->getBox()->checkCollision(*tableList[j]->getBox())) {

				tableList[j]->setHP(tableList[j]->getHP() - 1);
				eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
				eProjectiles[i]->getSprite()->removeFromParent();
				eProjectiles.erase(eProjectiles.begin() + i);
				BaseObjectManager::eProjectileBObjects.erase(BaseObjectManager::eProjectileBObjects.begin() + i);
				check = true;
				break;


			}
			else
				check = false;
			if (tableList[j]->getHP() <= 0) {
				tableList[j]->getBox()->getDrawNode()->removeFromParent();
				tableList[j]->getSprite()->removeFromParent();
				tableList.erase(tableList.begin() + j);
				j--;
			}

			if (check) {
				i--;
				check = false;
			}
		}
	}
}





ShotgunOutlaw::ShotgunOutlaw(float x, float y) :Outlaw(x, y)
{
	points = 200;

	this->getSprite()->setTexture("shotgunOutlaw.png");
}
void Sedna::ShotgunOutlaw::animate(float dt)
{
	
}
void ShotgunOutlaw::shoot(float dt, cocos2d::Scene * s)
{

	if (eShootTimer > 0.9f) {
		eShootTimer = 0.0f;
		eHasShot = false;
	}
	if (!eShootTimer) {
		for (int i = 0; i < eProjectiles.size(); i++) {
			eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
			eProjectiles[i]->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin() + i);
			BaseObjectManager::eProjectileBObjects.erase(BaseObjectManager::eProjectileBObjects.begin() + i);
		}
		eHasShot = true;
		Projectile* eBaseProjectile = new Sedna::Projectile(-1000, 10, Enemy);
		s->addChild(eBaseProjectile->getBox()->getDrawNode());
		s->addChild(eBaseProjectile->getSprite());

		Projectile* eBaseProjectile2 = new Sedna::Projectile(-1000, 10, Enemy);
		s->addChild(eBaseProjectile2->getBox()->getDrawNode());
		s->addChild(eBaseProjectile2->getSprite());

		Projectile* eBaseProjectile3 = new Sedna::Projectile(-1000, 10, Enemy);
		s->addChild(eBaseProjectile3->getBox()->getDrawNode());
		s->addChild(eBaseProjectile3->getSprite());

		Projectile* eBaseProjectile4 = new Sedna::Projectile(-1000, 10, Enemy);
		s->addChild(eBaseProjectile4->getBox()->getDrawNode());
		s->addChild(eBaseProjectile4->getSprite());

		Projectile* eBaseProjectile5 = new Sedna::Projectile(-1000, 10, Enemy);
		s->addChild(eBaseProjectile5->getBox()->getDrawNode());
		s->addChild(eBaseProjectile5->getSprite());


		eProjectiles.push_back(new Sedna::Projectile(*eBaseProjectile));
		BaseObjectManager::eProjectileBObjects.push_back(eBaseProjectile);

		eProjectiles.push_back(new Sedna::Projectile(*eBaseProjectile2));
		BaseObjectManager::eProjectileBObjects.push_back(eBaseProjectile2);

		eProjectiles.push_back(new Sedna::Projectile(*eBaseProjectile3));
		BaseObjectManager::eProjectileBObjects.push_back(eBaseProjectile3);

		eProjectiles.push_back(new Sedna::Projectile(*eBaseProjectile4));
		BaseObjectManager::eProjectileBObjects.push_back(eBaseProjectile4);

		eProjectiles.push_back(new Sedna::Projectile(*eBaseProjectile5));
		BaseObjectManager::eProjectileBObjects.push_back(eBaseProjectile5);


		eProjectiles[0]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
		eProjectiles[1]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
		eProjectiles[2]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
		eProjectiles[3]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
		eProjectiles[4]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));

		//eProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-3.25, -3.25));
		//eProjectiles[1]->getBox()->setForce(cocos2d::Vec2(-1.75, -4.5));
		//eProjectiles[2]->getBox()->setForce(cocos2d::Vec2(0, -5.06));
		//eProjectiles[3]->getBox()->setForce(cocos2d::Vec2(1.75, -4.5));
		//eProjectiles[4]->getBox()->setForce(cocos2d::Vec2(3.25, -3.25));

		if (this->getBox()->getLocation().x < 250) {
			this->getSprite()->setTexture("shotgunOutlaw1.png");
			eProjectiles[0]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-22, 0));
			eProjectiles[1]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-22, 0));
			eProjectiles[2]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-22, 0));
			eProjectiles[3]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-22, 0));
			eProjectiles[4]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-22, 0));


			eProjectiles[0]->getBox()->setForce(cocos2d::Vec2(0, -5.06));//projectile on the left
			eProjectiles[1]->getBox()->setForce(cocos2d::Vec2(1.75, -4.5));
			eProjectiles[2]->getBox()->setForce(cocos2d::Vec2(3.35, -3.35));//projectiles in the middle
			eProjectiles[3]->getBox()->setForce(cocos2d::Vec2(4.5, -1.75));
			eProjectiles[4]->getBox()->setForce(cocos2d::Vec2(5.06, 0));//projectile on the right
		}
		else if (this->getBox()->getLocation().x > 250) {
			this->getSprite()->setTexture("shotgunOutlaw.png");
			eProjectiles[0]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
			eProjectiles[1]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
			eProjectiles[2]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
			eProjectiles[3]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
			eProjectiles[4]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));

			eProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-5.06, 0));//projectile on the left
			eProjectiles[1]->getBox()->setForce(cocos2d::Vec2(-4.5, -1.75));
			eProjectiles[2]->getBox()->setForce(cocos2d::Vec2(-3.35, -3.35));//projectiles in the middle
			eProjectiles[3]->getBox()->setForce(cocos2d::Vec2(-1.75, -4.5));
			eProjectiles[4]->getBox()->setForce(cocos2d::Vec2(0, -5.06));//projectile on the right
		}


	}
	if (eHasShot)
		eShootTimer += dt;
}
void ShotgunOutlaw::checkList()
{
	if (eProjectiles.size() > 10) {
		eProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
		eProjectiles.front()->getSprite()->removeFromParent();
		eProjectiles.erase(eProjectiles.begin());
	}
	for (int i = 0; i < eProjectiles.size(); i++)
		eProjectiles[i]->updateGameObject();
}







RifleOutlaw::RifleOutlaw(float x, float y) : Outlaw(x, y)
{
	points = 300;
	this->getSprite()->setRotation(10.0f);
	track = cocos2d::Vec2(0, 0);
}

void Sedna::RifleOutlaw::animate(float dt)
{
	if (animationTimer > 0.3f) {
		this->getSprite()->setTexture("rifleLl.png");

		hasAnimation = false;
	}
	if (animationTimer > 0.6f) {
		animationTimer = 0.0f;
	}
	if (!animationTimer) {
		this->getSprite()->setTexture("rifleRl.png");
		hasAnimation = true;
	}
	animationTimer += dt;
}

void Sedna::RifleOutlaw::shoot(float dt, cocos2d::Scene * s)
{

	if (eShootTimer > 0.9f) {
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

		eProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
		auto direction = track / sqrt(track.x*track.x + track.y*track.y);
		eProjectiles.back()->getBox()->setForce(cocos2d::Vec2(direction) * 10);
	}
	if (eHasShot)
		eShootTimer += dt;

}

void Sedna::RifleOutlaw::checkList()
{
	if (eProjectiles.size() > 4) {
		eProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
		eProjectiles.front()->getSprite()->removeFromParent();
		eProjectiles.erase(eProjectiles.begin());
	}
	for (int i = 0; i < eProjectiles.size(); i++)
		eProjectiles[i]->updateGameObject();
}
void Sedna::RifleOutlaw::setTrack(Player * p)
{
	track = (p->getBox()->getLocation() - this->getBox()->getLocation());
}
cocos2d::Vec2 Sedna::RifleOutlaw::getTrack() const
{
	return track;
}
}
