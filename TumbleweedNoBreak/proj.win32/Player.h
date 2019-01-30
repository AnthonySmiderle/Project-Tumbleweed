#pragma once
#include "Primitive.h"
#include "XinputManager.h"
class Player :
	public Pm::CirclePrimitive, public cocos2d::Sprite
{
public:
	Player(cocos2d::Sprite PLAYERSPRITE);
	~Player();
	void setController();//make this take an xinput controller
	void checkInput();
	void setCircle(Pm::CirclePrimitive);
	cocos2d::Sprite* getPlayerSprite() const;

private:
	cocos2d::Sprite* playerSprite;
	Pm::CirclePrimitive hitCircle;

};

