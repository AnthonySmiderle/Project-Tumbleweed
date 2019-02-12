#pragma once
#include "cocos2d.h"
#include "Primitive.h"
#include "Enums and Typdefs.h"
#include <string>
namespace Sedna {

	class GameObject{
	public:
		GameObject() {}
		//GameObject(cocos2d::Sprite* image,Sedna::CirclePrimitive box);
		GameObject(const char* FILEPATH, const cocos2d::Vec2 &LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS);
		~GameObject() { delete sprite; delete hitBox; }
		cocos2d::Sprite* getSprite()const;
		Sedna::CirclePrimitive* getBox()const;
		void setCircle(CirclePrimitive c) { *hitBox = c; }
		void updateGameObject();
		HP getHp() const;
		void setHp(HP hp);
	protected:
		HP objectHp;
		cocos2d::Sprite *sprite;
		Sedna::CirclePrimitive* hitBox;
	};
}