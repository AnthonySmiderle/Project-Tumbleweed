#include "Primitive.h"
#include "2d/CCDrawNode.h"

Pm::SquarePrimitive::SquarePrimitive(const cocos2d::Vec2 & startingPosition, const cocos2d::Vec2 & endPosition)
	: Node(cocos2d::DrawNode::create())
{

	Node->drawRect(startingPosition, endPosition, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));

}

Pm::SquarePrimitive::SquarePrimitive()
{
}

Pm::SquarePrimitive::~SquarePrimitive()
{
	Node->release();
}

cocos2d::DrawNode * Pm::SquarePrimitive::getDrawNode() const
{
	return Node;
}

Pm::CirclePrimitive::CirclePrimitive(const cocos2d::Vec2 &LOCATION, float RADIUS,float ANGLE, unsigned int SEGMENTS) 
	: Node(cocos2d::DrawNode::create())
{

	Node->drawCircle(LOCATION, RADIUS, ANGLE, SEGMENTS, false, cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	radius = RADIUS;
	angle = ANGLE;
	segments = SEGMENTS;
	

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

Pm::LinePrimitive::LinePrimitive(cocos2d::Vec2& ORIGIN, cocos2d::Vec2& ENDPOINT)
	: Node(cocos2d::DrawNode::create())
{
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

Pm::Capsule::Capsule(cocos2d::Vec2 & ORIGIN, cocos2d::Vec2 & ENDPOINT, float RADIUS)
	: Node(cocos2d::DrawNode::create())
{
	




}
