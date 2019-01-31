#include "GameObject.h"

Sedna::GameObject::GameObject(std::string image)
{
	sprite = cocos2d::Sprite::create(image);
}

cocos2d::Sprite * Sedna::GameObject::getSprite() const
{
	return sprite;
}
