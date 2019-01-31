#pragma once
#include "cocos2d.h"
#include "Primitive.h"
#include <string>
namespace Sedna {

	class GameObject : public Pm::CirclePrimitive {
	public:
		GameObject(std::string image);
		cocos2d::Sprite* getSprite()const;
	private:
		cocos2d::Sprite *sprite;

	};
}