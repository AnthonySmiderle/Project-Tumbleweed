#pragma once
#include "cocos2d.h"
#include "Primitive.h"
#include <string>
namespace Sedna {

	class GameObject{
	public:
		GameObject(cocos2d::Sprite* image,Pm::CirclePrimitive box);
		cocos2d::Sprite* getSprite()const;
		Pm::CirclePrimitive getBox()const;
	private:
		cocos2d::Sprite *sprite;
		Pm::CirclePrimitive hitBox;
	};
}