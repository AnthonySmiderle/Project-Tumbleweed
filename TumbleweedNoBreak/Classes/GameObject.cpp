#include "GameObject.h"

Sedna::GameObject::GameObject(cocos2d::Sprite* image,Pm::CirclePrimitive box):sprite(image),hitBox(box)
{
}

cocos2d::Sprite * Sedna::GameObject::getSprite() const
{
	return sprite;
}

Pm::CirclePrimitive Sedna::GameObject::getBox() const
{
	return hitBox;
}
