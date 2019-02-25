#include "UserInterface.h"

Sedna::UI::UI()
{
}

Sedna::UI::UI(cocos2d::Sprite * UISPRITE, cocos2d::Label * UILABEL)
{
	uiLabel = UILABEL;
	uiSprite = UISPRITE;
	
	uiSprite->setPosition(cocos2d::Vec2(uiLabel->getPosition().x, uiLabel->getPosition().y + 10));
	
}

Sedna::UI::UI(const char * spriteFilepath, const char * labelText)
{
	uiSprite = cocos2d::Sprite::create(spriteFilepath);
	uiLabel = cocos2d::Label::create();
	uiLabel->setString(labelText);

	uiLabel->setPosition(cocos2d::Vec2(125, 125));
	uiSprite->setPosition(cocos2d::Vec2(uiLabel->getPosition().x, uiLabel->getPosition().y + 25));

}

Sedna::UI::~UI()
{
	uiSprite->removeFromParent();
	uiLabel->removeFromParent();
}


cocos2d::Sprite * Sedna::UI::getSprite() const
{
	return uiSprite;
}

cocos2d::Label * Sedna::UI::getLabel() const
{
	return uiLabel;
}
