//Anthony Smiderle
//100695532
#include "Primitive.h"
#include "2d/CCDrawNode.h"

namespace Pm {

	//Square
	Pm::SquarePrimitive::SquarePrimitive(cocos2d::Vec2  startingPosition, cocos2d::Vec2 endPosition)
		: Node(cocos2d::DrawNode::create())//initialize draw node
	{
		start = startingPosition;
		end = endPosition;
		//draw a rectangle given dimensions
		Node->drawRect(start, end, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}

	Pm::SquarePrimitive::SquarePrimitive()
	{
	}

	Pm::SquarePrimitive::~SquarePrimitive()
	{
		Node->release();//destroy draw node
	}

	cocos2d::DrawNode * Pm::SquarePrimitive::getDrawNode() const
	{
		return Node;
	}

	void Pm::SquarePrimitive::setPoint(cocos2d::Vec2 & newPosition1, cocos2d::Vec2 & newPosition2)
	{
		start = newPosition1;
		end = newPosition2;
	}

	void SquarePrimitive::update()
	{
		Node->drawRect(start, end, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	}

	//Circle
	Pm::CirclePrimitive::CirclePrimitive(const cocos2d::Vec2 &LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS)
		: Node(cocos2d::DrawNode::create())
	{
		//draw a circle given dimensions
		Node->drawCircle(LOCATION, RADIUS, ANGLE, SEGMENTS, false, cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	}

	Pm::CirclePrimitive::CirclePrimitive()
	{
	}

	Pm::CirclePrimitive::~CirclePrimitive()
	{
		Node->release();
	}

	cocos2d::DrawNode * Pm::CirclePrimitive::getDrawNode() const
	{
		return Node;
	}

	//Line
	Pm::LinePrimitive::LinePrimitive(cocos2d::Vec2& ORIGIN, cocos2d::Vec2& ENDPOINT)
		: Node(cocos2d::DrawNode::create())
	{
		//draw a line given two points
		Node->drawLine(ORIGIN, ENDPOINT, cocos2d::Color4F(0.0f, 0.0f, 1.0f, 1.0f));
	}

	Pm::LinePrimitive::LinePrimitive()
	{
	}

	Pm::LinePrimitive::~LinePrimitive()
	{
		Node->release();
	}

	cocos2d::DrawNode * Pm::LinePrimitive::getDrawNode() const
	{
		return Node;
	}


	//Capsule
	Pm::Capsule::Capsule(cocos2d::Vec2 & ORIGIN, cocos2d::Vec2 & ENDPOINT, float RADIUS)
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

	Pm::Capsule::~Capsule()
	{
		Node->release();
	}

	cocos2d::DrawNode * Pm::Capsule::getDrawNode() const
	{
		return Node;
	}

}