#include "Sign.h"
namespace Sedna {
	///<REMEMBER TO SET VISIBLE TO TRUE....might not need this anymore>
	Sign::Sign(std::string LABELTEXT, cocos2d::Scene * s, const cocos2d::Vec2& LOCATION)
	{
		sprite = cocos2d::Sprite::create("Crazy.png");
		hitBox = new CirclePrimitive(LOCATION, 5, 5, 50);

		labelText = LABELTEXT;

		signText = cocos2d::Label::create(labelText, "fonts/Montague.ttf", 15);
		signText->setPosition(cocos2d::Vec2(220, 250));
		signText->enableShadow();
		signText->enableBold();
		signText->setVisible(false);
		s->addChild(signText, 10000);
		s->addChild(sprite);
		s->addChild(hitBox->getDrawNode());

		hitBox->getDrawNode()->setVisible(false);

	}

	Sign::Sign(std::string FILEPATH, cocos2d::Scene * s, const cocos2d::Vec2 & LOCATION, bool CONSTWITHSPRITE)
	{
		sprite = cocos2d::Sprite::create("Crazy.png");
		hitBox = new CirclePrimitive(LOCATION, 5, 5, 50);
		hitBox->getDrawNode()->setVisible(false);
		s->addChild(sprite);
		s->addChild(hitBox->getDrawNode());

		spritepath = FILEPATH;
		displayedSprite = cocos2d::Sprite::create(FILEPATH);
		displayedSprite->setPosition(cocos2d::Vec2(230,250));
		displayedSprite->setVisible(false);
		constructedWithSprite = true;
		s->addChild(displayedSprite, 1000);
	}

	Sign::~Sign()
	{
		if (constructedWithSprite)
			displayedSprite->removeFromParent();
		else
			signText->removeFromParent();
	}
	void Sign::signUpdate(Player* playerOne)
	{
		this->updateGameObject();

		if ((this->getBox()->getLocation().x - playerOne->getBox()->getLocation().x) <= 20 &&
			(this->getBox()->getLocation().x - playerOne->getBox()->getLocation().x) >= -20 &&
			(this->getBox()->getLocation().y - playerOne->getBox()->getLocation().y) >= -20 &&
			(this->getBox()->getLocation().y - playerOne->getBox()->getLocation().y) <= 20)
			(constructedWithSprite) ? displayedSprite->setVisible(true) : signText->setVisible(true);
		else
			(constructedWithSprite) ? displayedSprite->setVisible(false) : signText->setVisible(false);

		

	}

	void Sign::animate(float dt, std::string TEMPSPRITE)
	{
		if (!constructedWithSprite)
			return;
		if (animationTimer >= 0.75f) {
			animationTimer = 0.0f;
			hasAnimated = false;
		}
		if (animationTimer <= 0.25f) {
			hasAnimated = true;
			displayedSprite->setTexture(TEMPSPRITE);

		}
		else if (animationTimer >= 0.5f) 
			displayedSprite->setTexture(spritepath);

		if (hasAnimated)
			animationTimer += dt;

	}

	cocos2d::Sprite * Sign::getDisplayedSprite() const
	{
		if (constructedWithSprite)
			return displayedSprite;
		return nullptr;
	}

	cocos2d::Label * Sign::getLabel() const
	{
		return signText;
	}
}