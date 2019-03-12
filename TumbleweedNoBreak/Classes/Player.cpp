#include "Player.h"
#include <iostream>
#include "AudioEngine.h"
#include "Powerup.h"
#define BULLETSPEED 1.5f
#define BULLETSPEED1 3
#define UIDISPOSITION 360

namespace Sedna {


	Player::Player(int wPlayer, float x, float y, XinputManager MANAGER, Gun* CURRENTGUN)
	{
		this->playerNumber = wPlayer;
		this->setHP(3);
		score = 0;


		auto localL1 = cocos2d::Label::create(CURRENTGUN->getName() == "olReliable" ? "" : std::to_string(CURRENTGUN->getAmmo()), "fonts/Montague.ttf", 15);
		auto localL2 = cocos2d::Label::create(std::to_string(score), "fonts/Montague.ttf", 15);
		playerUI = new SednaUI(CURRENTGUN, this, 2, localL1, localL2);



		//if (wPlayer == playerOne) {
			sprite = cocos2d::Sprite::create("player1.png");//CHANGE THIS WITH ANIMATION STUFF
			sprite->setScale(spriteScale);
			hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);
			hitBox->getDrawNode()->setVisible(false);

			this->pController = MANAGER.getController(playerNumber - 1);
			playerUI->getUIGunSprite()->setPosition(cocos2d::Vec2(100 - 40 + (UIDISPOSITION*(playerNumber - 1)), 130 - 70));
			playerUI->getLabelList()[0]->setAnchorPoint(cocos2d::Vec2(0, 0));
			playerUI->getLabelList()[0]->setPosition(cocos2d::Vec2(112 - 40 + (UIDISPOSITION*(playerNumber - 1)), 116 - 70));
			playerUI->getLabelList()[1]->setAnchorPoint(cocos2d::Vec2(0, 0));
			playerUI->getLabelList()[1]->setPosition(cocos2d::Vec2(112 - 40 + (UIDISPOSITION*(playerNumber - 1)), 116 - 80));


			playerUI->getHPSprites()[0]->setPosition(cocos2d::Vec2((60 - 40)+(80*(playerNumber - 1)) + (UIDISPOSITION*(playerNumber - 1)), 116 - 70));
			playerUI->getHPSprites()[1]->setPosition(cocos2d::Vec2((60 - 40)+(80*(playerNumber - 1)) + (UIDISPOSITION*(playerNumber - 1)), playerUI->getHPSprites()[0]->getPosition().y + 20));
			playerUI->getHPSprites()[2]->setPosition(cocos2d::Vec2((60 - 40)+(80*(playerNumber - 1)) + (UIDISPOSITION*(playerNumber - 1)), playerUI->getHPSprites()[1]->getPosition().y + 20));
/*
		//}
		//else {
			//sprite = cocos2d::Sprite::create("player2.png");
			//sprite->setScale(spriteScale);
			//hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);
			//hitBox->getDrawNode()->setVisible(false);

			//this->pController = MANAGER.getController(playerNumber - 1);
			//playerUI->getLabelList()[0]->setPosition(cocos2d::Vec2(100, 100));//was not me

			//playerUI->getUIGunSprite()->setPosition(cocos2d::Vec2(60 + (UIDISPOSITION*playerNumber-1), 130 - 70));
			//playerUI->getLabelList()[0]->setAnchorPoint(cocos2d::Vec2(0, 0));
			//playerUI->getLabelList()[0]->setPosition(cocos2d::Vec2(72 + (UIDISPOSITION*playerNumber - 1), 116 - 70));


			//playerUI->getHPSprites()[0]->setPosition(cocos2d::Vec2(100, 116 - 70));
			//playerUI->getHPSprites()[1]->setPosition(cocos2d::Vec2(100, playerUI->getHPSprites()[0]->getPosition().y + 20));
			//playerUI->getHPSprites()[2]->setPosition(cocos2d::Vec2(100, playerUI->getHPSprites()[1]->getPosition().y + 20));


		//}
			*/
		currentGun = CURRENTGUN;



	}


	Player::~Player()
	{
		//delete this;
	}

	unsigned int Player::getScore() const
	{
		return score;
	}

	void Player::die()
	{
		takeInputs = false;
		this->getBox()->setForce(cocos2d::Vec2(0, 0));
		this->sprite->setRotation(90);
	}

	void Player::setCurrentGun(Gun * g)
	{
		currentGun = g;
		if (g->getName() == "olReliable") {
			playerUI->getUIGunSprite()->setTexture("gun1.png");
			playerUI->getLabelList()[0]->setString(" ");
		}

	}

	void Player::checkInput(float dt)
	{
		if (pController->isVibrating()) {
			vibrationTimer += dt;
			if (vibrationTimer >= 0.2f) {
				pController->setVibration(0, 0);
				vibrationTimer = 0;
			}
		}
		if (takeInputs) {
			if (this->getBox()->getVelocity() != cocos2d::Vec2(0,0)) {
				if (animationTimer > 0.3f && !isAimingLeft && !isAimingRight) {
					this->getSprite()->setTexture("p1w2.png");
					hasAnimation = false;
				}
				 if (animationTimer > 0.3f && isAimingRight) {
					this->getSprite()->setTexture("p1wl2.png");
					hasAnimation = false;
				}
				 if (animationTimer > 0.3f && isAimingLeft) {///
					this->getSprite()->setTexture("p1wr2.png");
					hasAnimation = false;
				}

				if (animationTimer > 0.6f)
				{
					animationTimer = 0.0f;
				}

				if (!animationTimer && !isAimingLeft && !isAimingRight) {
					hasAnimation = true;
					this->getSprite()->setTexture("p1w1.png");
				}
				 if (!animationTimer && isAimingRight) {
					hasAnimation = true;
					this->getSprite()->setTexture("p1wl1.png");
				}
				 if (!animationTimer && isAimingLeft) {///
					hasAnimation = true;
					this->getSprite()->setTexture("p1wr1.png");
				}
				animationTimer += dt;
			}

			pController->updateSticks(pSticks);
			if (pSticks[0].x > 0.3f){
				this->getBox()->addForce(3, 0);
				
			}

			else if (pSticks[0].x < -0.3f)
				this->getBox()->addForce(-3, 0);

			if (pSticks[0].y > 0.3f) {
				this->getBox()->addForce(0, 3);
				
					
			}

			else if (pSticks[0].y < -0.3f)
				this->getBox()->addForce(0, -3);

			if (pSticks[0].x > -0.3f && pSticks[0].x < 0.3f && pSticks[0].y > -0.3f && pSticks[0].y < 0.3f)
				this->getBox()->addForce(this->getBox()->getVelocity().x *-2.0f, this->getBox()->getVelocity().y*-2.0f);

			if (pController->isButtonPressed(Sedna::START))
				exit(0);

		}
	}
	void Player::shoot(float dt, cocos2d::Scene* s)
	{
		if (takeInputs) {
			if (pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f ||
				pSticks[1].y > 0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f) {
				isAimingLeft = false;
				isAimingRight = false;
				//if (playerNumber == 1)
				//	sprite->setTexture("player1.png");
			}
			if (pSticks[1].x < -0.3f)
				isAimingLeft = true;
			if (pSticks[1].x > 0.3f)
				isAimingRight = true;
				//	if (playerNumber == 1)
			//		sprite->setTexture("p1L.png");
			//if (pSticks[1].x > 0.3f)
			//	if (playerNumber == 1)
			//		sprite->setTexture("p1R.png");

			pController->getTriggers(pTriggers);
			if (pTriggers.RT > 0) {

				if (currentGun->getGunTimer() > currentGun->getRateOfFire())
				{
					currentGun->setGunTimer(0.0f);
					currentGun->setHasShot(false);
				}
				if (currentGun->getGunTimer() == 0)
				{

					//comment this if statement out for omnidirectional
					if (pSticks[1].y < -0.3f) {

					}
					//comment this else statement out for omidirectional
					else {
						cocos2d::experimental::AudioEngine::play2d("revolver1.mp3", false, 0.5f);
						//else if (this->currentGun->getName() == "theBiggestIron") {
						//	static auto last = cocos2d::experimental::AudioEngine::play2d("gattling.mp3", false, 0.5f);
						//	cocos2d::experimental::AudioEngine::stop(last);
						//	cocos2d::experimental::AudioEngine::play2d("gattling.mp3", false, 0.5f);
						//}

						currentGun->setAmmo(currentGun->getAmmo() - 1);
						playerUI->updateList();
						currentGun->setHasShot(true);
						auto test = cocos2d::Vec2(pSticks[1].x, pSticks[1].y);
						auto test2 = test / sqrt(test.x*test.x + test.y*test.y);
						if (currentGun->getName() == "olReliable" || currentGun->getName() == "theBiggestIron") {
							Projectile* playerProjectile = new Sedna::Projectile(-1000, 0, Sedna::Ally);
							s->addChild(playerProjectile->getBox()->getDrawNode());
							s->addChild(playerProjectile->getSprite());
							BaseObjectManager::pProjectileBObjects.push_back(playerProjectile);


							pProjectiles.push_back(new Sedna::Projectile(*playerProjectile));

							pProjectiles.back()->getSprite()->setTexture("pBullet.png");
							pProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation());
							//uncomment this for omnidirectional
							if (currentGun->getName() == "theBiggestIron")
								pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(test2)*BULLETSPEED1 * 2.5);

							//comment out this region to enable omnidirectional shooting
							else {

#pragma region 3DirectionShooting
								if (pSticks[1].x < -0.3f) {
									pProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));

									//pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(test2)*BULLETSPEED1*2);

									pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(-3.5, 3.5)*BULLETSPEED);
								}

								if (pSticks[1].x > 0.3f) {
									pProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));

									//pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(test2)*BULLETSPEED1*2);

									pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(3.5, 3.5)*BULLETSPEED);
								}

								if (pSticks[1].y > 0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f ||
									pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f)
									pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(0, 5)*BULLETSPEED);
								//pProjectiles.back()->getBox()->setForce(cocos2d::Vec2(test2)*BULLETSPEED1*2);


							}
						}
#pragma endregion
						
						else if (currentGun->getName() == "bloodyMary") {
							cocos2d::experimental::AudioEngine::play2d("shotgun.mp3", false, 0.5f);

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

							Projectile* playerProjectile4 = new Sedna::Projectile(-1000, 0, Sedna::Ally);
							s->addChild(playerProjectile4->getBox()->getDrawNode());
							s->addChild(playerProjectile4->getSprite());
							BaseObjectManager::pProjectileBObjects.push_back(playerProjectile4);

							Projectile* playerProjectile5 = new Sedna::Projectile(-1000, 0, Sedna::Ally);
							s->addChild(playerProjectile5->getBox()->getDrawNode());
							s->addChild(playerProjectile5->getSprite());
							BaseObjectManager::pProjectileBObjects.push_back(playerProjectile5);

							pProjectiles.push_back(new Sedna::Projectile(*playerProjectile1));
							pProjectiles.push_back(new Sedna::Projectile(*playerProjectile2));
							pProjectiles.push_back(new Sedna::Projectile(*playerProjectile3));
							pProjectiles.push_back(new Sedna::Projectile(*playerProjectile4));
							pProjectiles.push_back(new Sedna::Projectile(*playerProjectile5));

							pProjectiles[0]->getBox()->setLocation(this->getBox()->getLocation());
							pProjectiles[1]->getBox()->setLocation(this->getBox()->getLocation());
							pProjectiles[2]->getBox()->setLocation(this->getBox()->getLocation());
							pProjectiles[3]->getBox()->setLocation(this->getBox()->getLocation());
							pProjectiles[4]->getBox()->setLocation(this->getBox()->getLocation());

							pProjectiles[0]->getSprite()->setTexture("pBullet.png");
							pProjectiles[1]->getSprite()->setTexture("pBullet.png");
							pProjectiles[2]->getSprite()->setTexture("pBullet.png");
							pProjectiles[3]->getSprite()->setTexture("pBullet.png");
							pProjectiles[4]->getSprite()->setTexture("pBullet.png");



							if (pSticks[1].y > 0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f ||
								pSticks[1].y < 0.3f && pSticks[1].y > -0.3f && pSticks[1].x < 0.3f && pSticks[1].x > -0.3f) {
								pProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-3.25, 3.25)*BULLETSPEED);//projectile on the left
								pProjectiles[1]->getBox()->setForce(cocos2d::Vec2(-1.75, 4.5)*BULLETSPEED);
								pProjectiles[2]->getBox()->setForce(cocos2d::Vec2(0, 5.06)*BULLETSPEED);//projectiles in the middle
								pProjectiles[3]->getBox()->setForce(cocos2d::Vec2(1.75, 4.5)*BULLETSPEED);
								pProjectiles[4]->getBox()->setForce(cocos2d::Vec2(3.25, 3.25)*BULLETSPEED);//projectile on the right

							}
							if (pSticks[1].x < -0.3f) {

								pProjectiles[0]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
								pProjectiles[1]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
								pProjectiles[2]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
								pProjectiles[3]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
								pProjectiles[4]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));

								pProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-5.06, 0)*BULLETSPEED);//projectile on the left
								pProjectiles[1]->getBox()->setForce(cocos2d::Vec2(-4.5, 1.75)*BULLETSPEED);
								pProjectiles[2]->getBox()->setForce(cocos2d::Vec2(-3.35, 3.35)*BULLETSPEED);//projectiles in the middle
								pProjectiles[3]->getBox()->setForce(cocos2d::Vec2(-1.75, 4.5)*BULLETSPEED);
								pProjectiles[4]->getBox()->setForce(cocos2d::Vec2(0, 5.06)*BULLETSPEED);//projectile on the right

							}
							if (pSticks[1].x > 0.3f) {

								pProjectiles[0]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
								pProjectiles[1]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
								pProjectiles[2]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
								pProjectiles[3]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));
								pProjectiles[4]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));

								pProjectiles[0]->getBox()->setForce(cocos2d::Vec2(0, 5.06)*BULLETSPEED);//projectile on the left
								pProjectiles[1]->getBox()->setForce(cocos2d::Vec2(1.75, 4.5)*BULLETSPEED);
								pProjectiles[2]->getBox()->setForce(cocos2d::Vec2(3.35, 3.35)*BULLETSPEED);//projectiles in the middle
								pProjectiles[3]->getBox()->setForce(cocos2d::Vec2(4.5, 1.75)*BULLETSPEED);
								pProjectiles[4]->getBox()->setForce(cocos2d::Vec2(5.06, 0)*BULLETSPEED);//projectile on the right


							}
						}
					}
				}
			}



			if (currentGun->getHasShot())
				currentGun->setGunTimer(currentGun->getGunTimer() + dt);

		}
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

	void Player::checkBCollision(std::vector<Outlaw*>& outlawList, Powerup* power1, Powerup* power2)
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
					score += outlawList[j]->points;
					srand(time(0));
					if (rand() % 10 + 1 <= 2) {
						if (rand() % 2 == 0) {
							power1->getBox()->setLocation(outlawList[j]->getBox()->getLocation());
							power1->updateGameObject();
						}
						else {
							power2->getBox()->setLocation(outlawList[j]->getBox()->getLocation());
							power2->updateGameObject();
						}

					}



					playerUI->updateList();
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
				//POWERUP CODE
				if (tableList[i]->getBeer() != blank)
				{
					if (tableList[i]->getBeer() == health)
					{
						for (int j = this->getUI()->getHPSprites().size() - 1; j >= 0; j--) {
							if (this->getUI()->getHPSprites()[j]->getZOrder() == 20) {
								this->getUI()->getHPSprites()[j]->setZOrder(21);
								this->getUI()->getHPSprites()[j]->setTexture("fullHeart.png");
								break;
							}
						}
						if (this->getHP() < 3)
							this->setHP(this->getHP() + 1);
					}
					if (tableList[i]->getBeer() == invinc)
					{
						invincTimer = 20.0f;
					}
					if (tableList[i]->getBeer() == rapid)
					{

					}
					score += 200;
					tableList[i]->setBeer(blank);
				}

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






	SednaUI::SednaUI(Gun * CurrentGun, Player* p, int args, ...)
	{
		va_list LIST;
		va_start(LIST, args);
		for (int i = 0; i < args; i++) {
			labelList.push_back(va_arg(LIST, cocos2d::Label*));
		}
		va_end(LIST);

		this->p = p;

		labelList[1]->enableWrap(true);

		hp1 = cocos2d::Sprite::create("fullHeart.png");
		hp2 = cocos2d::Sprite::create("fullHeart.png");
		hp3 = cocos2d::Sprite::create("fullHeart.png");

		hpSprites.push_back(hp1);
		hpSprites.push_back(hp2);
		hpSprites.push_back(hp3);

		hpSprites[0]->setZOrder(21);
		hpSprites[1]->setZOrder(21);
		hpSprites[2]->setZOrder(21);

		this->currentGun = CurrentGun;

		if (this->currentGun->getName() == "olReliable") {
			uiGunSprite = cocos2d::Sprite::create("gun1.png");
		}
		else if (this->currentGun->getName() == "bloodyMary")
			uiGunSprite = cocos2d::Sprite::create("gun2.png");
		else if (this->currentGun->getName() == "theBiggestIron")
			uiGunSprite = cocos2d::Sprite::create("gun3.png");
		//else make the other guns work

		uiGunSprite->setScale(0.85f);

	}

	std::vector<cocos2d::Label*> SednaUI::getLabelList() const
	{
		return labelList;
	}

	cocos2d::Sprite * SednaUI::getUIGunSprite() const
	{
		return uiGunSprite;
	}

	std::vector<cocos2d::Sprite*> SednaUI::getHPSprites() const
	{
		return hpSprites;
	}

	void SednaUI::setUIGunSprite(cocos2d::Sprite * s)
	{
		this->uiGunSprite = s;
	}

	void SednaUI::updatePosition(cocos2d::Vec2 p)
	{
		for (int i = 0; i < labelList.size(); i++)
			labelList[i]->setPosition(labelList[i]->getPosition() + p);

		uiGunSprite->setPosition(uiGunSprite->getPosition() + p);
		for (int i = 0; i < hpSprites.size(); i++)
			hpSprites[i]->setPosition(hpSprites[i]->getPosition() + p);
	}


	void SednaUI::updateList()
	{
		this->currentGun = p->getCurrentGun();
		for (int i = 0; i < labelList.size(); i++) {
			labelList[0]->setString(std::to_string(currentGun->getAmmo()));
			labelList[1]->setString(std::to_string(p->getScore()));
		}
	}

}
