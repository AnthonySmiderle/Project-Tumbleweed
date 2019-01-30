#pragma once
#include "cocos2d.h"
class Bullet : public cocos2d::Sprite
{
public:
	Bullet();
	virtual ~Bullet();
	Bullet* createBulletPointer();
private:
	Sprite* sprite;
};

