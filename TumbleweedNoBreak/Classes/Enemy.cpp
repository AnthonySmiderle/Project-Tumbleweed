#include "Enemy.h"
#include "Player.h"
#include "AudioEngine.h"
#include "Table.h"
#include <iostream>
namespace Sedna {

	Sedna::Outlaw::Outlaw(float x, float y)
	{
		//set up the hitbox and sprite
		sprite = cocos2d::Sprite::create("outlawLl.png");
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

			//make a new projectile
			eProjectiles.push_back(new Sedna::Projectile(-1000, 10, Enemy));
			s->addChild(eProjectiles.back()->getBox()->getDrawNode());
			s->addChild(eProjectiles.back()->getSprite());

			//create the illusion that the outlaw is "shooting"
			eProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-8, 0));
			eProjectiles.back()->getBox()->setForce(cocos2d::Vec2(0, -5));

			//play a sound
			cocos2d::experimental::AudioEngine::play2d("outlawNormal.mp3");
		}
		if (eHasShot)
			eShootTimer += dt;
	}
	void Outlaw::checkList()
	{
		//if there are more than 4 bullets on the screen, clear them
		if (eProjectiles.size() > 4) {
			eProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
			eProjectiles.front()->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin());
		}
		//update the projectiles
		for (int i = 0; i < eProjectiles.size(); i++)
			eProjectiles[i]->updateGameObject();
	}
	void Outlaw::removeProjectiles()
	{
		//clear projectiles
		for (int i = 0; i < eProjectiles.size(); i++) {
			eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
			eProjectiles[i]->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin() + i);
			i--;
		}
	}
	void Outlaw::animate(float dt)
	{
		//animate the outlaws
		if (animationTimer > 0.3f)
			this->getSprite()->setTexture("outlawLl.png");

		if (animationTimer > 0.6f)
			animationTimer = 0.0f;

		if (!animationTimer)
			this->getSprite()->setTexture("outlawRl.png");
		animationTimer += dt;
	}
	void Outlaw::checkBCollision(Player * p)
	{
		//check to see if the projectiles are colliding with the player
		for (int i = 0; i < eProjectiles.size(); i++) {
			if (eProjectiles.empty())
				break;


			if (eProjectiles[i]->getBox()->checkCollision(*p->getBox())) {
				if (!(p->getInvinc())) {

					p->setHP(p->getHP() - 1);
					srand(rand() % time(0));
					int random = (rand() % 3) + 1;

					//play a random sound
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
					//vibrate the player's controller
					p->getController()->setVibration(1, 1);
					//reset the invincibility timer
					p->wasHurt();
					for (int j = 0; j < p->getUI()->getHPSprites().size(); j++) {
						if (p->getUI()->getHPSprites()[j]->getZOrder() == 21) {
							p->getUI()->getHPSprites()[j]->setZOrder(20);
							p->getUI()->getHPSprites()[j]->setTexture("brokenHeart.png");
							break;
						}
					}
				}
				//remove the bullet
				eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
				eProjectiles[i]->getSprite()->removeFromParent();
				eProjectiles.erase(eProjectiles.begin() + i);
				if (p->getHP() <= 0)
					p->die();
			}
		}





	}
	void Outlaw::checkBCollision(std::vector<Table*>& tableList)
	{
		//check to see if a bullet is colliding with a table
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
		onLeft = false;
	}
	void Sedna::ShotgunOutlaw::animate(float dt)
	{
		//this enemy has no animations
	}
	void ShotgunOutlaw::shoot(float dt, cocos2d::Scene * s)
	{

		if (eShootTimer > 0.9f) {
			eShootTimer = 0.0f;
			eHasShot = false;
		}
		//if the timer is 0
		if (!eShootTimer) {
			for (int i = 0; i < eProjectiles.size(); i++) {
				eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
				eProjectiles[i]->getSprite()->removeFromParent();
				eProjectiles.erase(eProjectiles.begin() + i);
				i--;
			}
			eHasShot = true;

			for (int i = 0; i < 5; i++) {
				eProjectiles.push_back(new Projectile(-1000, 10, Enemy));
				s->addChild(eProjectiles.back()->getBox()->getDrawNode());
				s->addChild(eProjectiles.back()->getSprite());
			}





			for (unsigned i = 0; i < 5; ++i)
				eProjectiles[i]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));


			if (/*this->getBox()->getLocation().x < 250*/ onLeft) {
				this->getSprite()->setTexture("shotgunOutlaw1.png");

				for (unsigned i = 0; i < 5; ++i)
					eProjectiles[i]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-22, 0));

				//set the projectiles to move in a certain direction
				eProjectiles[0]->getBox()->setForce(cocos2d::Vec2(0, -5.06));//projectile on the left
				eProjectiles[1]->getBox()->setForce(cocos2d::Vec2(1.75, -4.5));
				eProjectiles[2]->getBox()->setForce(cocos2d::Vec2(3.35, -3.35));//projectiles in the middle
				eProjectiles[3]->getBox()->setForce(cocos2d::Vec2(4.5, -1.75));
				eProjectiles[4]->getBox()->setForce(cocos2d::Vec2(5.06, 0));//projectile on the right
			}
			else if (/*this->getBox()->getLocation().x > 250*/!onLeft) {
				this->getSprite()->setTexture("shotgunOutlaw.png");

				for (unsigned i = 0; i < 5; ++i)
					eProjectiles[i]->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(16, 0));


				eProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-5.06, 0));//projectile on the left
				eProjectiles[1]->getBox()->setForce(cocos2d::Vec2(-4.5, -1.75));
				eProjectiles[2]->getBox()->setForce(cocos2d::Vec2(-3.35, -3.35));//projectiles in the middle
				eProjectiles[3]->getBox()->setForce(cocos2d::Vec2(-1.75, -4.5));
				eProjectiles[4]->getBox()->setForce(cocos2d::Vec2(0, -5.06));//projectile on the right
			}
			cocos2d::experimental::AudioEngine::play2d("outlawShotgun.mp3");


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

	void Sedna::ShotgunOutlaw::onLeftSideOf(Player * p)
	{
		if (this->getBox()->getLocation().x - p->getBox()->getLocation().x < 0)
			onLeft = true;
		else if (this->getBox()->getLocation().x - p->getBox()->getLocation().x > 0)
			onLeft = false;

	}







	RifleOutlaw::RifleOutlaw(float x, float y) : Outlaw(x, y)
	{
		points = 300;
		track = cocos2d::Vec2(0, 0);
	}

	void Sedna::RifleOutlaw::animate(float dt)
	{
		if (animationTimer > 0.3f)
			this->getSprite()->setTexture("rifleLl.png");

		if (animationTimer > 0.6f)
			animationTimer = 0.0f;

		if (!animationTimer)
			this->getSprite()->setTexture("rifleRl.png");

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
			//get the normalized vector in the direction of the player
			auto direction = track / sqrt(track.x*track.x + track.y*track.y);
			if (direction.y > 0)
				return;
			for (int i = 0; i < 5; i++) {
				eProjectiles.push_back(new Projectile(-1000, 10, Enemy));
				s->addChild(eProjectiles.back()->getBox()->getDrawNode());
				s->addChild(eProjectiles.back()->getSprite());
			}



			eProjectiles.back()->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-16, 0));
			eProjectiles.back()->getBox()->setForce(direction * 8);
			cocos2d::experimental::AudioEngine::play2d("outlawRifle.mp3");

		}
		if (eHasShot)
			eShootTimer += dt;

	}


	void Sedna::RifleOutlaw::setTrack(Player * p)
	{
		track = (p->getBox()->getLocation() - this->getBox()->getLocation());
	}
	cocos2d::Vec2 Sedna::RifleOutlaw::getTrack() const
	{
		return track;
	}






	//                         (                  
	//    (                      )\ )        )      
	//    )\  (      )    (     (()/(  (  ( /(  (   
	//  (((_) )(  ( /( (  )\ )   /(_))))\ )\())))\  
	//  )\___(()\ )(_)))\(()/(  (_)) /((_|_))//((_) 
	// ((/ __|((_|(_)_((_))(_)) | _ (_)) | |_(_))   
	//  | (__| '_/ _` |_ / || | |  _/ -_)|  _/ -_)  
	//   \___|_| \__,_/__|\_, | |_| \___| \__\___|  
	//                    |__/                      

	CrazyPete::CrazyPete(float x, float y) : Outlaw(x, y)
	{
		this->setHP(3);
		points = 1000;
		this->getSprite()->setTexture("CrazyPete.png");
		dynamite = new Projectile(getBox()->getLocation().x, getBox()->getLocation().y, Enemy);
		dynamite->getSprite()->setTexture("a.png");
	}

	Sedna::CrazyPete::~CrazyPete()
	{
		delete dynamite;
		delete sprite;
		delete hitBox;
	}

	void Sedna::CrazyPete::animate(float dt)
	{
		if (animationTimer > 0.3f)
			this->getSprite()->setTexture("CrazyPete.png");

		if (animationTimer > 0.6f)
			animationTimer = 0.0f;

		if (!animationTimer)
			this->getSprite()->setTexture("CrazyPete2.png");

		animationTimer += dt;
	}

	void Sedna::CrazyPete::removeProjectiles()
	{
		for (int i = 0; i < eProjectiles.size(); i++) {
			eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
			eProjectiles[i]->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin() + i);
			i--;
		}
		dynamite->getBox()->getDrawNode()->removeFromParent();
		dynamite->getSprite()->removeFromParent();
	}




	void Sedna::CrazyPete::updateDyn(float dt, cocos2d::Scene * s)
	{
		//move crazy pete across the screen
		this->getBox()->setLocation(this->getBox()->getLocation() + cocos2d::Vec2(-1, 0));
		if (eShootTimer > 2.0f) {
			eShootTimer = 0.0f;
			eHasShot = false;
		}
		if (!eShootTimer) {
			eHasShot = true;
			dynamite->getBox()->setForce(cocos2d::Vec2(0, -4));
		}

		if (eHasShot) {
			eShootTimer += dt;
			dynamite->getBox()->setForce(cocos2d::Vec2(0, -4));
		}
		if (this->getBox()->getLocation().y - dynamite->getBox()->getLocation().y >= 150) {
			shoot(dt, s);
			dynamite->getBox()->setLocation(this->getBox()->getLocation());
			dynamite->getBox()->setForce(cocos2d::Vec2(0, 0));

		}


	}

	void Sedna::CrazyPete::shoot(float dt, cocos2d::Scene * s)
	{
		//remove all past bullets
		for (int i = 0; i < eProjectiles.size(); i++) {
			eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
			eProjectiles[i]->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin() + i);
			i--;
		}
		//make new bullets
		for (int i = 0; i < 8; i++) {
			eProjectiles.push_back(new Projectile(dynamite->getBox()->getLocation().x, dynamite->getBox()->getLocation().y, Enemy));
			s->addChild(eProjectiles.back()->getBox()->getDrawNode());
			s->addChild(eProjectiles.back()->getSprite());
		}



		auto speed = 6;

		//set the force of all new bullets

		eProjectiles[0]->getBox()->setForce(cocos2d::Vec2(-1, 0)*speed);
		eProjectiles[1]->getBox()->setForce(cocos2d::Vec2(1, 0) *speed);
		eProjectiles[2]->getBox()->setForce(cocos2d::Vec2(0, 1) *speed);
		eProjectiles[3]->getBox()->setForce(cocos2d::Vec2(0, -1)*speed);

		eProjectiles[4]->getBox()->setForce(cocos2d::Vec2(-0.5f, -0.5f)*speed);
		eProjectiles[5]->getBox()->setForce(cocos2d::Vec2(-0.5f, 0.5f) *speed);
		eProjectiles[6]->getBox()->setForce(cocos2d::Vec2(0.5f, -0.5f) *speed);
		eProjectiles[7]->getBox()->setForce(cocos2d::Vec2(0.5f, 0.5f)  *speed);

		cocos2d::experimental::AudioEngine::play2d("peteBomb.mp3");


	}

	void Sedna::CrazyPete::checkList()
	{
		if (eProjectiles.size() > 16) {
			eProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
			eProjectiles.front()->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin());
		}
		for (int i = 0; i < eProjectiles.size(); i++)
			eProjectiles[i]->updateGameObject();
		dynamite->updateGameObject();
	}




	//   ______             __        __                                   
	//  /      \           /  |      /  |                                  
	// /$$$$$$  |  ______  $$ |  ____$$ | _____  ____    ______   _______  
	// $$ | _$$/  /      \ $$ | /    $$ |/     \/    \  /      \ /       \ 
	// $$ |/    |/$$$$$$  |$$ |/$$$$$$$ |$$$$$$ $$$$  | $$$$$$  |$$$$$$$  |
	// $$ |$$$$ |$$ |  $$ |$$ |$$ |  $$ |$$ | $$ | $$ | /    $$ |$$ |  $$ |
	// $$ \__$$ |$$ \__$$ |$$ |$$ \__$$ |$$ | $$ | $$ |/$$$$$$$ |$$ |  $$ |
	// $$    $$/ $$    $$/ $$ |$$    $$ |$$ | $$ | $$ |$$    $$ |$$ |  $$ |
	//  $$$$$$/   $$$$$$/  $$/  $$$$$$$/ $$/  $$/  $$/  $$$$$$$/ $$/   $$/ 





	Goldman::Goldman(float x, float y) :Outlaw(x, y)
	{
		this->setHP(100);
		points = 5000;
		sprite->setTexture("boss.png");
		sprite->setScale(0.4f);
		sprite->setAnchorPoint(cocos2d::Vec2(0.4f, 0.3f));
		hitBox->setRadius(hitBox->getRadius() + 5);
		healthBar = new SquarePrimitive(cocos2d::Vec2(this->getBox()->getLocation().x - 160, this->getBox()->getLocation().y - 235),
			cocos2d::Vec2(this->getBox()->getLocation().x - 160 + this->getHP() * 3, this->getBox()->getLocation().y - 240));

	}

	Goldman::~Goldman()
	{
		this->healthBar->getDrawNode()->removeFromParent();
	}

	void Sedna::Goldman::shoot(float dt, cocos2d::Scene * s, CirclePrimitive* c)
	{
		//if its phase 3, pick randomly between phase 1 and 2
		if (this->getHP() <= 25) {
			phase3 = true;
			if (!playedMadSound) {
				cocos2d::experimental::AudioEngine::play2d("goldmanMad.mp3");
				playedMadSound = true;
			}
			if (1 + rand() % 2 == 1) {
				phase1 = true;
				phase2 = false;
			}
			else {
				phase1 = false;
				phase2 = true;
			}
		}
		//initiate phase 2
		else if (this->getHP() <= (100 / 2)/*left it as a fraction incase we wanna change it later*/)
		{
			phase1 = false;
			phase2 = true;
		}
		auto v = cocos2d::Vec2(0, 0);
		srand(time(0));
		if (phase1) {

			if (eShootTimer > ((phase3) ? 0.7f : 1.15f)) {
				eShootTimer = 0.0f;
				eHasShot = false;
			}
			if (!eShootTimer) {
				for (int i = 0; i < eProjectiles.size(); i++) {
					eProjectiles[i]->getBox()->getDrawNode()->removeFromParent();
					eProjectiles[i]->getSprite()->removeFromParent();
					eProjectiles.erase(eProjectiles.begin() + i);
					i--;
				}

				for (int i = 0; i < 10; i++) {
					this->eProjectiles.push_back(new Projectile(this->getBox()->getLocation().x, this->getBox()->getLocation().y + 60, Enemy));
					s->addChild(eProjectiles.back()->getBox()->getDrawNode());
					s->addChild(eProjectiles.back()->getSprite());
				}
				cocos2d::experimental::AudioEngine::play2d("shotgun.mp3");

				eHasShot = true;
				//the following mathematical function produces a random pattern in a shotgun arc/spread
				v.x = -5;
				for (int i = 0; i < 10; i++) {
					v.x++;
					v.y = -v.x*v.x;
					auto first = rand() % 4 >= 1 ?
						(rand() % 2 == 1 ?
						(rand() % 6) : (-rand() % 6)) : 0.0f;
					auto second = -3.0f;
					//make the projectiles come from above the screen
					eProjectiles[i]->getBox()->setLocation(cocos2d::Vec2(this->getBox()->getLocation().x, this->getBox()->getLocation().y + 60) + v);
					auto force = v / sqrt(v.x*v.x + v.y*v.y);
					//set the force to the normalized direction of v, and add in some random force as well
					eProjectiles[i]->getBox()->setForce(force*1.5f + cocos2d::Vec2(first, second*1.5f));
				}


			}
			if (eHasShot)
				eShootTimer += dt;

		}
		else if (phase2) {
			if (eShootTimer > ((phase3) ? 0.059f : 0.089f)) {
				eShootTimer = 0.0f;
				eHasShot = false;
			}
			if (!eShootTimer) {
				cocos2d::experimental::AudioEngine::play2d("revolver1.mp3");
				eHasShot = true;

				if (phase2Vec.x < -5.0f)
					switche = false;
				if (phase2Vec.x > 5.0f)
					switche = true;
				if (!switche)
					phase2Vec.x += 0.1f;
				if (switche)
					phase2Vec.x -= 0.1f;


				//c is an invisible circle primitive that moves back and forth across the screen during the bossfight
				auto direction = c->getLocation() - this->getBox()->getLocation();

				this->eProjectiles.push_back(new Projectile(this->getBox()->getLocation().x, this->getBox()->getLocation().y + 60, Enemy));
				s->addChild(eProjectiles.back()->getBox()->getDrawNode());
				s->addChild(eProjectiles.back()->getSprite());

				eProjectiles.back()->getBox()->setLocation(cocos2d::Vec2(this->getBox()->getLocation().x, this->getBox()->getLocation().y + 60) + v);
				auto force = direction / sqrt(direction.x*direction.x + direction.y*direction.y);
				eProjectiles.back()->getBox()->setForce(force * 8);




			}
			if (eHasShot)
				eShootTimer += dt;
		}
	}

	void Sedna::Goldman::animate(float dt)
	{
		//set 1
		if (!phase3) {

			if (animationTimer > 0.14375f && animationTimer < 0.2875f)
				this->getSprite()->setTexture("GOLDMAN walk2.png");

			if (animationTimer > 0.2875f && animationTimer < 0.575f)
				this->getSprite()->setTexture("GOLDMAN walk3.png");

			if (animationTimer > 0.8625f)
				this->getSprite()->setTexture("GOLDMAN walk4.png");

			if (animationTimer > 1.15f)
				animationTimer = 0.0f;

			if (!animationTimer)
				this->getSprite()->setTexture("GOLDMAN walk1.png");


			animationTimer += dt;
		}

		//set 2
		else if (phase3) {
			if (animationTimer > 0.14375f / 2.0f && animationTimer < 0.2875f / 2.0f)
				this->getSprite()->setTexture("GOLDMAN mad walk2.png");

			if (animationTimer > 0.2875f / 2.0f && animationTimer < 0.575f / 2.0f)
				this->getSprite()->setTexture("GOLDMAN mad walk3.png");

			if (animationTimer > 0.8625f / 2.0f)
				this->getSprite()->setTexture("GOLDMAN mad walk4.png");

			if (animationTimer > 1.15f / 2.0f)
				animationTimer = 0.0f;

			if (!animationTimer)
				this->getSprite()->setTexture("GOLDMAN mad walk1.png");


			animationTimer += dt;
		}

	}

	void Sedna::Goldman::checkList()
	{
		//make sure the healthbar stays on screen and update its length
		healthBar->setP2x(this->getBox()->getLocation().x - 160 + this->getHP() * 3);
		healthBar->setP1y(this->getBox()->getLocation().y - 215);
		healthBar->setP2y(this->getBox()->getLocation().y - 220);
		healthBar->update(true);

		if (eProjectiles.size() > (phase1 ? 20 : 100)) {
			eProjectiles.front()->getBox()->getDrawNode()->removeFromParent();
			eProjectiles.front()->getSprite()->removeFromParent();
			eProjectiles.erase(eProjectiles.begin());
		}
		for (int i = 0; i < eProjectiles.size(); i++)
			eProjectiles[i]->updateGameObject();
	}

	SquarePrimitive * Sedna::Goldman::getHealthBar() const
	{
		return healthBar;
	}

}
