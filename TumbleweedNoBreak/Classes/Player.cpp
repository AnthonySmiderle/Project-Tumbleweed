#include "Player.h"

namespace Sedna {


Player::Player(int wPlayer,float x, float y)
{
	if (wPlayer == playerOne) {
		sprite = cocos2d::Sprite::create("player1.png");
		hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 20, 5, 30);
	}

	//else 
	//	playerGameObject = new GameObject("player2.png", cocos2d::Vec2(100, 100), 20, 5, 50);
}


Player::~Player()
{
	delete this;
}



}
