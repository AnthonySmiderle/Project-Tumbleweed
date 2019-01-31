#include "Bullet.h"



Bullet::Bullet() 
{
	sprite = Sprite::create("player1.png");
}


Bullet::~Bullet()
{
}

Bullet * Bullet::createBulletPointer()
{
	Bullet *tempBullet = new Bullet();
	return tempBullet;
}
