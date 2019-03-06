#include "Player.h"
#include <iostream>
namespace Sedna {


	Player::Player(int wPlayer, float x, float y, XinputManager MANAGER, Gun* CURRENTGUN)
	{
		auto localL1 = cocos2d::Label::create(std::to_string(CURRENTGUN->getAmmo()), "fonts/arial.ttf", 25);
		playerUI = new SednaUI(CURRENTGUN, 1,localL1);
		sprite = cocos2d::Sprite::create("player1.png");
		sprite->setScale(0.85f);
		if (wPlayer == playerOne) {
			hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 24, 5, 30);
			hitBox->getDrawNode()->setVisible(false);

			this->pController = MANAGER.getController(0);
			playerUI->getLabelList()[0]->setPosition(cocos2d::Vec2(100, 100));
		}
		else {
			hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 24, 5, 30);
			hitBox->getDrawNode()->setVisible(false);

			this->pController = MANAGER.getController(1);

		}
		currentGun = CURRENTGUN;

		

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
			if (tumbleTimer > 1.5)
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
				//sprite->setTexture("p1T.png");

			}
		}
		else {
			//sprite->setTexture("player1.png");
			this->getBox()->setTumbling(false);
		}

		if (isTumbling)
			tumbleTimer += dt;

		if (pController->isButtonPressed(Sedna::START))
			exit(0);
			
	}

	void Player::shoot(float dt, cocos2d::Scene* s)
	{
		if (pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f ||
			pSticks[1].y > 0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f) {
			sprite->setTexture("player1.png");
		}
		if (pSticks[1].x < -0.3f && pSticks[1].y > 0.3f)
			sprite->setTexture("p1L.png");
		if (pSticks[1].x > 0.3f && pSticks[1].y > 0.3f)
			sprite->setTexture("p1R.png");

		pController->getTriggers(pTriggers);
		if (pTriggers.RT > 0) {

			if (currentGun->getGunTimer() > currentGun->getRateOfFire())
			{
				currentGun->setGunTimer(0.0f);
				currentGun->setHasShot(false);
			}
			if (currentGun->getGunTimer() == 0)
			{
				currentGun->setHasShot(true);
				if (pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x > 0.3f ||
					pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < -0.3f ||
					pSticks[1].y < -0.3f) {
				}
				else {


					if (currentGun->getName() == "olReliable" || currentGun->getName() == "theBiggestIron") {
						Projectile* playerProjectile = new Sedna::Projectile(-1000, 0, Sedna::Ally);
						s->addChild(playerProjectile->getBox()->getDrawNode());
						s->addChild(playerProjectile->getSprite());
						BaseObjectManager::pProjectileBObjects.push_back(playerProjectile);


						pProjectiles.push_back(new Sedna::Projectile(*playerProjectile));

						pProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation());

						if (pSticks[1].x < -0.3f && pSticks[1].y > 0.3f)
							pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(-3.5, 3.5));

						if (pSticks[1].x > 0.3f && pSticks[1].y > 0.3f)
							pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(3.5, 3.5));

						if (pSticks[1].y > 0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f ||
							pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f)
							pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(0, 5));


					}
					else if (currentGun->getName() == "bloodyMary") {
						for (int i = 0; i < pProjectiles.size(); i++) {
							pProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
							pProjectiles[i]->getSprite()->removeFromParent();
							pProjectiles.erase(pProjectiles.begin() + i);
							BaseObjectManager::pProjectileBObjects.erase(BaseObjectManager::pProjectileBObjects.begin() + i);
						}
						Projectile* playerProjectile1 = new Sedna::Projectile(-1000, 0, Sedna::Ally);
						s->addChild(playerProjectile1->getBox()->getDrawNode());
						s->addChild(playerProjectile1->getSprite());
						BaseObjectManager::pProjectileBObjects.push_back(playerProjectile1);

						Projectile* playerProjectile2 = new Sedna::Projectile(-1000, 0, Sedna::Ally);
						s->addChild(playerProjectile2->getBox()->getDrawNode());
						s->addChild(playerProjectile2->getSprite());
						BaseObjectManager::pProjectileBObjects.push_back(playerProjectile2);

						Projectile* playerProjectile3 = new Sedna::Projectile(-1000, 0, Sedna::Ally);
						s->addChild(playerProjectile3->getBox()->getDrawNode());
						s->addChild(playerProjectile3->getSprite());
						BaseObjectManager::pProjectileBObjects.push_back(playerProjectile3);

						pProjectiles.push_back(new Sedna::Projectile(*playerProjectile1));
						pProjectiles.push_back(new Sedna::Projectile(*playerProjectile2));
						pProjectiles.push_back(new Sedna::Projectile(*playerProjectile3));

						pProjectiles[0]->getBox()->setLocation(this->getBox()->getLocation());
						pProjectiles[1]->getBox()->setLocation(this->getBox()->getLocation());
						pProjectiles[2]->getBox()->setLocation(this->getBox()->getLocation());



						if (pSticks[1].y > 0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f ||
							pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f) {
							pProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-3.5, 3.5));//projectile on the left
							pProjectiles[1]->getBox()->setForce(cocos2d::Vec2(0, 5));//projectiles in the middle
							pProjectiles[2]->getBox()->setForce(cocos2d::Vec2(3.5, 3.5));//projectile on the right

						}
						if (pSticks[1].x < -0.3f && pSticks[1].y > 0.3f) {
							pProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-5, 0));
							pProjectiles[1]->getBox()->setForce(cocos2d::Vec2(-3.5, 3.5));
							pProjectiles[2]->getBox()->setForce(cocos2d::Vec2(0, 5));

						}
						if (pSticks[1].x > 0.3f && pSticks[1].y > 0.3f) {
							pProjectiles[0]->getBox()->setForce(cocos2d::Vec2(0, 5));
							pProjectiles[1]->getBox()->setForce(cocos2d::Vec2(3.5, 3.5));
							pProjectiles[2]->getBox()->setForce(cocos2d::Vec2(5, 0));


						}
					}


				}
			}


		}
		if (currentGun->getHasShot())
			currentGun->setGunTimer(currentGun->getGunTimer() + dt);

	}

	void Player::checkList()
	{
		if (pProjectiles.size() > currentGun->getProjLimit()) {
			pProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
			pProjectiles.front()->getSprite()->removeFromParent();
			pProjectiles.erase(pProjectiles.begin());
			BaseObjectManager::pProjectileBObjects.erase(BaseObjectManager::pProjectileBObjects.begin());

		}


		for (int i = 0; i < pProjectiles.size(); i++)
			pProjectiles[i]->updateGameObject();


	}

	void Player::checkBCollision(std::vector<Outlaw*>& outlawList)
	{
		bool check = false;
		for (int i = 0; i < pProjectiles.size(); i++) {
			for (int j = 0; j < outlawList.size(); j++) {
				if (pProjectiles.empty())
					break;
				if (pProjectiles[i]->getBox()->checkCollision(*outlawList[j]->getBox())) {

					outlawList[j]->setHP(outlawList[j]->getHP() - currentGun->getDamage());
					pProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
					pProjectiles[i]->getSprite()->removeFromParent();
					pProjectiles.erase(pProjectiles.begin() + i);
					BaseObjectManager::pProjectileBObjects.erase(BaseObjectManager::pProjectileBObjects.begin() + i);
					check = true;
					break;

				}
				else
					check = false;
				if (outlawList[j]->getHP() <= 0) {
					outlawList[j]->removeProjectiles();
					outlawList[j]->getBox()->getDrawNode()->removeFromParent();
					outlawList[j]->getSprite()->removeFromParent();
					outlawList.erase(outlawList.begin() + j);
					j--;
				}


			}
			if (check) {
				i--;
				check = false;
			}
		}
	}
	void Player::checkBCollision(std::vector<Table*>& tableList)
	{
		bool check = false;
		for (int i = 0; i < pProjectiles.size(); i++) {
			for (int j = 0; j < tableList.size(); j++) {
				if (pProjectiles.empty())
					break;
				if (pProjectiles[i]->getBox()->checkCollision(*tableList[j]->getBox())) {

					tableList[j]->setHP(tableList[j]->getHP() - 1);
					pProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
					pProjectiles[i]->getSprite()->removeFromParent();
					pProjectiles.erase(pProjectiles.begin() + i);
					check = true;
					break;


				}
				else
					check = false;
				if (tableList[j]->getHP() <= 0) {
					tableList[j]->getBox()->getDrawNode()->removeFromParent();
					tableList[j]->getSprite()->removeFromParent();
					tableList.erase(tableList.begin() + j);
					BaseObjectManager::tableBObjects.erase(BaseObjectManager::tableBObjects.begin() + j);
					j--;
				}

				if (check) {
					i--;
					check = false;
				}
			}
		}
	}

	void Player::checkTableStuff(std::vector<Table*>& tableList)
	{
		for (int i = 0; i < tableList.size(); i++) {
			if (pController->isButtonPressed(Sedna::A) && this->getBox()->checkCollision(*tableList[i]->getBox())) {
				cocos2d::Vec2 distanceVector((tableList[i]->getBox()->getLocation().x - this->getBox()->getLocation().x),
					(tableList[i]->getBox()->getLocation().y - this->getBox()->getLocation().y));
				tableList[i]->spriteSwitch();
				//times 2 to give a better feel to kicking the table
				tableList[i]->getBox()->addForce(distanceVector.x * 2, distanceVector.y * 2);

			}
			if (tableList[i]->getBox()->getVelocity() != cocos2d::Vec2(0, 0)) {

				tableList[i]->getBox()->addForce(
					tableList[i]->getBox()->getVelocity().x * -1,
					tableList[i]->getBox()->getVelocity().y * -1);
			}
			if (this->getBox()->checkCloseTouching(*tableList[i]->getBox())) {
				cocos2d::Vec2 distanceVector((this->getBox()->getLocation().x - tableList[i]->getBox()->getLocation().x),
					(this->getBox()->getLocation().y - tableList[i]->getBox()->getLocation().y));
				this->getBox()->addForce(((distanceVector.x * 2) / 2), (distanceVector.y * 2) / 2);
			}
		}
	}

	SednaUI * Player::getUI() const
	{
		return playerUI;
	}


	void Player::setGun(Gun * g)
	{
		currentGun = g;
	}

	std::vector<Projectile*> Player::getpProjectile() const
	{
		return pProjectiles;
	}



	////////////////////////////////////////
	////////////////////////////////////////
	/////////ui ui ui ui ui ui ui///////////
	/////////ui ui ui ui ui ui ui///////////
	/////////ui ui ui ui ui ui ui///////////
	/////////ui ui ui ui ui ui ui///////////
	/////////ui ui ui ui ui ui ui///////////
	////////////////////////////////////////
	////////////////////////////////////////






	SednaUI::SednaUI(Gun * CurrentGun, int args, ...)
	{
		va_list LIST;
		va_start(LIST, args);
		for (int i = 0; i < args; i++) {
			labelList.push_back(va_arg(LIST, cocos2d::Label*));
		}
		va_end(LIST);


		this->currentGun = CurrentGun;

		if (this->currentGun->getName() == "olReliable") {
			uiGunSprite = cocos2d::Sprite::create("gun1.png");
		}
		else if(this->currentGun->getName() == "bloodyMary")
			uiGunSprite = cocos2d::Sprite::create("gun2.png");
		else if (this->currentGun->getName() == "theBiggestIron")
			uiGunSprite = cocos2d::Sprite::create("gun3.png");
		//else make the other guns work
#ifdef _DEBUG
		else
			uiGunSprite = nullptr;
#endif

	}

	std::vector<cocos2d::Label*> SednaUI::getLabelList() const
	{
		return labelList;
	}

	cocos2d::Sprite * SednaUI::getUIGunSprite() const
	{
		return uiGunSprite;
	}

	void SednaUI::updateList()
	{
		//write code for updating numbers
	}

}
