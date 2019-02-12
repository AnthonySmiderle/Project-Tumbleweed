#include "Player.h"

namespace Sedna {


	Player::Player(int wPlayer, float x, float y,XinputManager X)
	{
		if (wPlayer == playerOne) {
			sprite = cocos2d::Sprite::create("player1.png");
			hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);

			this->pController = X.getController(0);
		

		}
		else {

			sprite = cocos2d::Sprite::create("player1.png");
			hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);
			this->pController = X.getController(1);

		}

		

	}


	Player::~Player()
	{
		//delete this;
	}

	void Player::checkInput(float dt)
	{
		pController->updateSticks(pSticks);
		if (pSticks[0].x > 0.3f)
			this->getBox()->addForce(3, 0);

		else if (pSticks[0].x < -0.3f)
			this->getBox()->addForce(-3, 0);

		if (pSticks[0].y > 0.3f)
			this->getBox()->addForce(0, 3);

		else if (pSticks[0].y < -0.3f)
			this->getBox()->addForce(0, -3);

		if (pSticks[0].x > -0.3f && pSticks[0].x < 0.3f && pSticks[0].y > -0.3f && pSticks[0].y < 0.3f)
			this->getBox()->addForce(this->getBox()->getVelocity().x *-2.0f, this->getBox()->getVelocity().y*-2.0f);

		if (pController->isButtonPressed(Sedna::B)) {
			//std::cout << tumbleTimer <<std::endl;
			if (tumbleTimer > 3)
			{
				tumbleTimer = 0;
				isTumbling = false;
			}


			if (!tumbleTimer)
			{
				isTumbling = true;
				this->getBox()->setTumbling(true);
				if (pSticks[0].x < -0.3f)
					this->getBox()->addForce(-500, 0);
				else if (pSticks[0].x > 0.3f)
					this->getBox()->addForce(500, 0);
				if (pSticks[0].y < -0.3f)
					this->getBox()->addForce(0, -500);
				else if (pSticks[0].y > 0.3f)
					this->getBox()->addForce(0, 500);


			}
		}
		else {
			this->getBox()->setTumbling(false);
		}

		if (isTumbling)
			tumbleTimer += dt;
	}

	void Player::shoot(float dt, cocos2d::Scene* s)
	{
		pController->getTriggers(pTriggers);
		if (pTriggers.RT > 0) {

			if (gunTimer > 0.2f)
			{
				gunTimer = 0.0f;
				hasShot = false;
			}
			if (!gunTimer)
			{
				hasShot = true;
				if (pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x > 0.3f ||
					pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < -0.3f ||
					pSticks[1].y < -0.3f) {
				}
				else {

					Projectile* playerProjectile = new Sedna::Projectile(-1000, 0, Sedna::Ally);
					s->addChild(playerProjectile->getBox()->getDrawNode());
					s->addChild(playerProjectile->getSprite());

					pProjectiles.push_back(new Sedna::Projectile(*playerProjectile));

					pProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation());

					if (pSticks[1].x < -0.3f && pSticks[1].y > 0.3f)
						pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(-5, 5));
					if (pSticks[1].x > 0.3f && pSticks[1].y > 0.3f)
						pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(5, 5));
					if (pSticks[1].y > 0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f ||
						pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f)
						pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(0, 5));
				}
			}


		}
		if (hasShot)
			gunTimer += dt;

	}

	void Player::checkList()
	{
		if (pProjectiles.size() > 4) {
			pProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
			pProjectiles.front()->getSprite()->removeFromParent();
			pProjectiles.erase(pProjectiles.begin());
		}

		for (int i = 0; i < pProjectiles.size(); i++)
			pProjectiles[i]->updateGameObject();

		
	}

	void Player::checkBCollision(std::vector<Outlaw*>& outlawList)
	{
		for (int i = 0; i < pProjectiles.size(); i++) {
			for (int j = 0; j < outlawList.size(); j++) {
				if (pProjectiles[i]->getBox()->checkCollision(*outlawList[j]->getBox())) {

					outlawList[j]->setHP(outlawList[j]->getHP() - 1);
					pProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
					pProjectiles[i]->getSprite()->removeFromParent();
					pProjectiles.erase(pProjectiles.begin() + i);

					if (!outlawList[j]->getHP()) {
						outlawList[j]->removeProjectiles();
						outlawList[j]->getBox()->getDrawNode()->removeFromParent();
						outlawList[j]->getSprite()->removeFromParent();
						outlawList.erase(outlawList.begin() + j);
						j--;
					}

					i--;

				}

			}
		}
	}

	std::vector<Projectile*> Player::getpProjectile() const
	{
		return pProjectiles;
	}



}
