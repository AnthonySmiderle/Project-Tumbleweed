#include "GameObject.h"

Sedna::GameObject::GameObject(cocos2d::Sprite* image,Sedna::CirclePrimitive box):sprite(image),hitBox(box)
{
}

Sedna::GameObject::GameObject(const char * FILEPATH, const cocos2d::Vec2 & LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS) :hitBox(LOCATION,RADIUS,ANGLE,SEGMENTS)
{
	sprite = cocos2d::Sprite::create(FILEPATH);
	sprite->setPosition(hitBox.getLocation());
	
}

cocos2d::Sprite * Sedna::GameObject::getSprite() const
{
	return sprite;
}

Sedna::CirclePrimitive Sedna::GameObject::getBox() const
{
	return hitBox;
}

void Sedna::GameObject::updateGameObject()
{
	hitBox.update();
	sprite->setPosition(hitBox.getLocation());
}
