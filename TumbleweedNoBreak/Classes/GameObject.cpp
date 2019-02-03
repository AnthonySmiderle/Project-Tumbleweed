#include "GameObject.h"
namespace Sedna {

//GameObject::GameObject(cocos2d::Sprite* image,CirclePrimitive box):sprite(image),hitBox(new CirclePrimtive(box))
//{
//}

GameObject::GameObject(const char * FILEPATH, const cocos2d::Vec2 & LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS) 
	:hitBox(new CirclePrimitive(LOCATION,RADIUS,ANGLE,SEGMENTS))
{
	sprite = cocos2d::Sprite::create(FILEPATH);
	sprite->setScale(0.5f);
	sprite->setPosition(hitBox->getLocation());
	
}

cocos2d::Sprite * GameObject::getSprite() const
{
	return sprite;
}

CirclePrimitive* GameObject::getBox() const
{
	return hitBox;
}

void GameObject::updateGameObject()
{
	hitBox->update();
	sprite->setPosition(hitBox->getLocation());
}
}
