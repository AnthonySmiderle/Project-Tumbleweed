#include "Powerup.h"
#include "Player.h"
#include "AudioEngine.h"
namespace Sedna {

	Sedna::Powerup::Powerup(const char* s, Gun* GUN, Gun* GUN2, float x, float y) : gun(GUN), gun2(GUN2)
	{
		sprite = cocos2d::Sprite::create(s);
		sprite->setScale(spriteScale);
		hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 15, 5, 30);
		hitBox->getDrawNode()->setVisible(false);
		this->updateGameObject();
	}

	Sedna::Powerup::~Powerup()
	{
		delete sprite;
		delete hitBox;
		delete gun;
		delete gun2;
	}



	void Sedna::Powerup::pickUp(Player * p)
	{
		if (this->getBox()->checkCollision(*p->getBox())) {
			//depending on which player it is, make them pick up their version of the gun
			p->setCurrentGun(p->getPlayerNumber() == 1 ? gun : gun2);
			p->getCurrentGun()->setAmmo(p->getCurrentGun()->getOriginalAmmo());

			//give the player the correct gun
			if (p->getCurrentGun()->getName() == "bloodyMary") {
				p->getUI()->getUIGunSprite()->setTexture("gun2.png");
				cocos2d::experimental::AudioEngine::play2d("pickupShot.mp3");
			}

			else if (p->getCurrentGun()->getName() == "theBiggestIron") {
				p->getUI()->getUIGunSprite()->setTexture("gun3.png");
				cocos2d::experimental::AudioEngine::play2d("pickupMini.mp3");

			}

			p->getUI()->updateList();
			//just move the thing, we dont need to delete it. it'll be used again later
			this->getBox()->setLocation(cocos2d::Vec2(-1000, 0));
			this->updateGameObject();
		}
		return;
	}
	Gun * Sedna::Powerup::getGun() const
	{
		return gun;
	}



}
