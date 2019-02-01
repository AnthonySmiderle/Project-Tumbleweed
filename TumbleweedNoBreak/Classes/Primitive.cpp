//Anthony Smiderle
//100695532
#include "Primitive.h"
#include "2d/CCDrawNode.h"

namespace Sedna {

	//Square
	Sedna::SquarePrimitive::SquarePrimitive(cocos2d::Vec2  startingPosition, cocos2d::Vec2 endPosition)
		: Node(cocos2d::DrawNode::create())//initialize draw node
	{
		start = startingPosition;
		end = endPosition;
		//draw a rectangle given dimensions
		Node->drawRect(start, end, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}

	Sedna::SquarePrimitive::SquarePrimitive()
	{
	}

	Sedna::SquarePrimitive::~SquarePrimitive()
	{
//		Node->release();//destroy draw node
	}

	cocos2d::DrawNode * Sedna::SquarePrimitive::getDrawNode() const
	{
		return Node;
	}

	void Sedna::SquarePrimitive::setPoint(cocos2d::Vec2 & newPosition1, cocos2d::Vec2 & newPosition2)
	{
		start = newPosition1;
		end = newPosition2;
		position = cocos2d::Vec2(start.x + end.x, start.y + end.y);
		velocity = cocos2d::Vec2(0, 0);
	}

	cocos2d::Vec2 SquarePrimitive::getStart() const
	{
		return start;
	}cocos2d::Vec2 SquarePrimitive::getEnd() const
	{
		return end;
	}

	void SquarePrimitive::update()
	{
		position += velocity;
		Node->drawRect(start, end, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void SquarePrimitive::addForce(cocos2d::Vec2 v)
	{
		velocity = v;
		update();
	}

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

	void CirclePrimitive::addForce(cocos2d::Vec2 v)
	{
		int maxVelocity = 5;
		int minVelocity = -5;

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
		int maxVelocity = 5;
		int minVelocity = -5;

		velocity = v;
		if (velocity.x >= maxVelocity)
			velocity.x = maxVelocity;
		else if (velocity.x <= minVelocity)
			velocity.x = minVelocity;
		if (velocity.y >= maxVelocity)
			velocity.y = maxVelocity;
		else if (velocity.y <= minVelocity)
			velocity.y = minVelocity;
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

	//Line
	Sedna::LinePrimitive::LinePrimitive(cocos2d::Vec2& ORIGIN, cocos2d::Vec2& ENDPOINT)
		: Node(cocos2d::DrawNode::create())
	{
		//draw a line given two points
		Node->drawLine(ORIGIN, ENDPOINT, cocos2d::Color4F(0.0f, 0.0f, 1.0f, 1.0f));
	}

	Sedna::LinePrimitive::LinePrimitive()
	{
	}

	Sedna::LinePrimitive::~LinePrimitive()
	{
		Node->release();
	}

	cocos2d::DrawNode * Sedna::LinePrimitive::getDrawNode() const
	{
		return Node;
	}


	//Capsule
	Sedna::Capsule::Capsule(cocos2d::Vec2 & ORIGIN, cocos2d::Vec2 & ENDPOINT, float RADIUS)
		: Node(cocos2d::DrawNode::create())
	{
		//draw two circles, one at the left most point and one at the right most point, given dimensions
		Node->drawCircle(ORIGIN, RADIUS, 5, 20, false, cocos2d::Color4F(10.0f, 10.0f, 10.0f, 1.0f));
		Node->drawCircle(ENDPOINT, RADIUS, 5, 20, false, cocos2d::Color4F(10.0f, 10.0f, 10.0f, 1.0f));

		//top line of the capsule, add the radius to the y coordinate to translate the line up to the proper place
		cocos2d::Vec2 topLineVector1(ORIGIN.x, ORIGIN.y + RADIUS);
		cocos2d::Vec2 topLineVector2(ENDPOINT.x, ENDPOINT.y + RADIUS);

		Node->drawLine(topLineVector1, topLineVector2, cocos2d::Color4F(10.0f, 10.0f, 10.0f, 1.0f));

		//bottom line, subtract y to get to the right poisition
		cocos2d::Vec2 bottomLineVector1(ORIGIN.x, ORIGIN.y - RADIUS);
		cocos2d::Vec2 bottomLineVector2(ENDPOINT.x, ENDPOINT.y - RADIUS);

		Node->drawLine(bottomLineVector1, bottomLineVector2, cocos2d::Color4F(10.0f, 10.0f, 10.0f, 1.0f));

	}

	Sedna::Capsule::~Capsule()
	{
		Node->release();
	}

	cocos2d::DrawNode * Sedna::Capsule::getDrawNode() const
	{
		return Node;
	}

}