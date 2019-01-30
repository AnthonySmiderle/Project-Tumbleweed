#include "GameSprite.h"

void Sedna::GameSprite::setVelocity(cocos2d::Vec2 v)
{
	velocity = v;
}

void Sedna::GameSprite::updateVelocity(float dt)
{

	velocity += acceleration * dt;
	position += velocity * dt;

}
Sedna::GamePrimitive::GamePrimitive(cocos2d::Vec2 START, cocos2d::Vec2 END) : Sedna::SquarePrimitive(START,END)
{
	this->position = (START + END) / 2;
	velocity = cocos2d::Vec2(0,0);
	acceleration = velocity;
	
}
void Sedna::GamePrimitive::setVelocity(cocos2d::Vec2 v)
{
	velocity = v;
}

void Sedna::GamePrimitive::updateVelocity(float dt)
{

	velocity += acceleration * dt;
	position += velocity * dt;

}