#pragma once
#include "cocos2d.h"
#include "Primitive.h"
#include "Enums and Typdefs.h"
#include <string>
namespace Sedna {

	class GameObject{
	public:
		GameObject() {}
		GameObject(const char* FILEPATH, const cocos2d::Vec2 &LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS);
		virtual ~GameObject() { delete sprite; delete hitBox; }
		virtual cocos2d::Sprite* getSprite()const;
		virtual Sedna::CirclePrimitive* getBox()const;
		virtual void setCircle(CirclePrimitive c) { *hitBox = c; }
		virtual void updateGameObject();
		virtual HP getHP() const;
		virtual void setHP(HP hp);
	protected:
		HP objectHp;
		cocos2d::Sprite *sprite;
		Sedna::CirclePrimitive* hitBox;
	};
}