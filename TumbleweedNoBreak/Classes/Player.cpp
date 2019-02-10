#include "Player.h"

namespace Sedna {


	Player::Player(int wPlayer, float x, float y)
	{
		if (wPlayer == playerOne) {
			sprite = cocos2d::Sprite::create("player1.png");
			hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);
		}
		else {

			sprite = cocos2d::Sprite::create("player1.png");
			hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);
		}
	}


	Player::~Player()
	{
		//delete this;
	}



}
