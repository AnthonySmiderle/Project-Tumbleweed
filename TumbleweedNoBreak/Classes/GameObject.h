#pragma once
#include "cocos2d.h"
#include "Primitive.h"
#include <string>
namespace Sedna {

	class GameObject{
	public:
		GameObject() {}
		GameObject(cocos2d::Sprite* image,Sedna::CirclePrimitive box);
		GameObject(const char* FILEPATH, const cocos2d::Vec2 &LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS);

		cocos2d::Sprite* getSprite()const;
		Sedna::CirclePrimitive getBox()const;
		void setCircle(Sedna::CirclePrimitive c) { hitBox = c; };
		void setSprite(cocos2d::Sprite* temp) {  sprite = temp; };
		void updateGameObject();//todo
	private:
		cocos2d::Sprite *sprite;
		Sedna::CirclePrimitive hitBox;
	};
}