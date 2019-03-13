//Anthony Smiderle
//100695532
#pragma once

#include "cocos2d.h"

//forward declaring a vec2 class for use in constructor
//namespace cocos2d {
//	class Vec2;
//	class DrawNode;
//}


		

namespace Sedna {

	//the actually useful one
	class CirclePrimitive {
	public:
		CirclePrimitive(const cocos2d::Vec2 &LOCATION,float RADIUS, float ANGLE,unsigned int SEGMENTS);
		CirclePrimitive();
		~CirclePrimitive();


		void setRadius(float r) { radius = r; }
		float getRadius() const { return radius; }
		cocos2d::DrawNode* getDrawNode() const;
		void update();
		void addForce(float vX, float vY);
		void setForce(cocos2d::Vec2 v);
		void setLocation(cocos2d::Vec2 p);//test function 
		cocos2d::Vec2 getVelocity() const;
		cocos2d::Vec2 getLocation() const;
		bool checkCollision(CirclePrimitive other);
		bool checkTouching(CirclePrimitive other);

		bool checkCloseTouching(CirclePrimitive other);

	private:
		cocos2d::Vec2 location;
		float radius;
		float angle;
		unsigned int segments;
		cocos2d::Vec2 velocity;
		cocos2d::DrawNode* Node;
		bool isTumble;

		float dt = 0, dt2 = 0.01f;
	};

}