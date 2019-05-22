#pragma once
#include "cocos2d.h"
#include "Primitive.h"
#include "Enums and Typdefs.h"
#include <string>

namespace Sedna {

	class GameObject{
	public:
		//this default constructor is here so that if the lazy programmer wants to create a child of game object, they have to define the hitbox and sprite themselves
		GameObject() { gameObjects.push_back(this); }

		GameObject(const char* FILEPATH, const cocos2d::Vec2 &LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS);
		virtual ~GameObject() { delete sprite; delete hitBox; }
		cocos2d::Sprite* getSprite()const;
		Sedna::CirclePrimitive* getBox()const;

		//you can set the hitbox to a different circle if you really want
		void setCircle(CirclePrimitive c) { *hitBox = c; }

		///<important function that makes the game work!!>
		void updateGameObject();
		HP getHP() const;
		void setHP(HP hp);
		virtual void die() {}
		
		const float spriteScale = 0.75f;
		float dt;
		static std::vector<GameObject*> gameObjects;
	protected:
		HP objectHp;
		cocos2d::Sprite *sprite;
		Sedna::CirclePrimitive* hitBox;
	};
}