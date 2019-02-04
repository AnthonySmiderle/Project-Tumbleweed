//Anthony Smiderle
//100695532
#include "Primitive.h"
#include "2d/CCDrawNode.h"

namespace Sedna {

	//Square
	
	//Circle
	Sedna::CirclePrimitive::CirclePrimitive(const cocos2d::Vec2 &LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS)
		: Node(cocos2d::DrawNode::create()),location(LOCATION), radius(RADIUS), angle(ANGLE), segments(SEGMENTS)
	{
		//draw a circle given dimensions
		Node->drawCircle(LOCATION, RADIUS, ANGLE, SEGMENTS, false, cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	}

	Sedna::CirclePrimitive::CirclePrimitive()
	{
	}

	Sedna::CirclePrimitive::~CirclePrimitive()
	{
		
//		Node->release();
	}

	cocos2d::DrawNode * Sedna::CirclePrimitive::getDrawNode() const
	{
		return Node;
	}

	void CirclePrimitive::update()
	{
		location += velocity;
		Node->clear();
		Node->drawCircle(location, radius, angle, segments, false, cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));

	}

	void CirclePrimitive::addForce(float vX, float vY)
	{
		cocos2d::Vec2 v = cocos2d::Vec2(vX, vY);
		int maxVelocity = 4;
		int minVelocity = -4;

		velocity += v / 10;

		if (velocity.x >= maxVelocity)
			velocity.x = maxVelocity;
		else if (velocity.x <= minVelocity)
			velocity.x = minVelocity;		
		if (velocity.y >= maxVelocity)
			velocity.y = maxVelocity;
		else if (velocity.y <= minVelocity)
			velocity.y = minVelocity;
	}

	void CirclePrimitive::setForce(cocos2d::Vec2 v)
	{
		velocity = v;
	}

	void CirclePrimitive::setLocation(cocos2d::Vec2 p)
	{
		this->location = p;
	}

	cocos2d::Vec2 CirclePrimitive::getVelocity() const
	{
		return velocity;
	}

	cocos2d::Vec2 CirclePrimitive::getLocation() const
	{
		return location;
	}

	bool CirclePrimitive::checkCollision(CirclePrimitive other)
	{
		float distance = sqrt((this->location.x - other.location.x)*(this->location.x - other.location.x) + 
			(this->location.y - other.location.y)*(this->location.y - other.location.y));

		
		if (distance <= (this->radius + other.radius))
			return true;

		return false;
	}

	bool CirclePrimitive::checkTouching(CirclePrimitive other)
	{
		float distance = sqrt((this->location.x - other.location.x)*(this->location.x - other.location.x) +
			(this->location.y - other.location.y)*(this->location.y - other.location.y));


		if (distance == (this->radius + other.radius))
			return true;
		return false;
	}

	

}