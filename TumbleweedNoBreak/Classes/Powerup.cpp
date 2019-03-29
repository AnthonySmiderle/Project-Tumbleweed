#include "Powerup.h"
#include "Player.h"
#include "AudioEngine.h"
namespace Sedna {

	Sedna::Powerup::Powerup(const char* s, Gun* GUN, float x, float y) : gun(GUN)
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
	}



	void Sedna::Powerup::pickUp(Player * p)
	{
		if (this->getBox()->checkCollision(*p->getBox())) {
			p->setCurrentGun(gun);
			p->getCurrentGun()->setAmmo(p->getCurrentGun()->getOriginalAmmo());

			if (p->getCurrentGun()->getName() == "bloodyMary") {
				p->getUI()->getUIGunSprite()->setTexture("gun2.png");
				cocos2d::experimental::AudioEngine::play2d("pickupShot.mp3");
			}

			else if (p->getCurrentGun()->getName() == "theBiggestIron") {
				p->getUI()->getUIGunSprite()->setTexture("gun3.png");
				cocos2d::experimental::AudioEngine::play2d("pickupMini.mp3");

			}

			p->getUI()->updateList();
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
