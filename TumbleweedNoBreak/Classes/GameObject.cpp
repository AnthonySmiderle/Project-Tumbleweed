#include "GameObject.h"
namespace Sedna {


	//create a new gameobject with the default settings for a game object
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
	//call the update function for the hitbox
	hitBox->update();
	//make sure that the sprite is on the hitbox no matter what
	sprite->setPosition(hitBox->getLocation());
}
HP GameObject::getHP() const
{
	return objectHp;
}
void GameObject::setHP(HP hp)
{
	objectHp = hp;
}

}
