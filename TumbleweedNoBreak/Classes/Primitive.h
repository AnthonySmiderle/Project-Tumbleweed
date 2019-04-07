
#pragma once
#include "cocos2d.h"

namespace Sedna {
	class SquarePrimitive {

	public:
		
		SquarePrimitive(const cocos2d::Vec2 &startingPosition, const cocos2d::Vec2 &endPosition);
		SquarePrimitive();
		~SquarePrimitive();


		cocos2d::DrawNode* getDrawNode() const;
		cocos2d::Vec2 getP1() const { return p1; }
		void setP1x(float X) { p1.x = X; }
		void setP2x(float X) { p2.x = X; }
		void setP1y(float Y) { p1.y = Y; }
		void setP2y(float Y) { p2.y = Y; }
		cocos2d::Vec2 getP2() const { return p2; }
		cocos2d::Vec2 getCentre();
		
		//adding force to the square primtive
		void addForce(cocos2d::Vec2 v);
		void update();
		//dummy parameter to determine what kind of square to draw (filled or not)
		void update(bool yn);
	private:
		cocos2d::DrawNode *Node;
		cocos2d::Vec2 velocity;
		cocos2d::Vec2 location;
		cocos2d::Vec2 p1;
		cocos2d::Vec2 p2;

		float dt = 0, dt2 = 0.01f;

	};
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