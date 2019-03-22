#include "Sign.h"
namespace Sedna {
	///<REMEMBER TO SET VISIBLE TO TRUE>
	Sign::Sign(std::string LABELTEXT, cocos2d::Scene * s, const cocos2d::Vec2& LOCATION)
	{
		sprite = cocos2d::Sprite::create("Crazy.png");
		hitBox = new CirclePrimitive(LOCATION, 5, 5, 50);

		labelText = LABELTEXT;

		signText = cocos2d::Label::create(labelText, "fonts/Montague.ttf", 20);
		signText->setPosition(cocos2d::Vec2(250, 250));
		signText->enableShadow();
		signText->enableBold();
		signText->setVisible(false);
		s->addChild(signText,10000);
		s->addChild(sprite);
		s->addChild(hitBox->getDrawNode());

	}
	Sign::~Sign()
	{
		signText->removeFromParent();
		//sprite->removeFromParent();
		//hitBox->getDrawNode()->removeFromParent();

	}
	void Sign::signUpdate(Player* playerOne, Player* playerTwo)
	{
		this->updateGameObject();

		if ((this->getBox()->getLocation().x - playerOne->getBox()->getLocation().x) <= 20 &&
			(this->getBox()->getLocation().x - playerOne->getBox()->getLocation().x) >= -20 &&
			(this->getBox()->getLocation().y - playerOne->getBox()->getLocation().y) >= -20 &&
			(this->getBox()->getLocation().y - playerOne->getBox()->getLocation().y) <= 20 ||

			(this->getBox()->getLocation().x - playerTwo->getBox()->getLocation().x) <= 20 &&
			(this->getBox()->getLocation().x - playerTwo->getBox()->getLocation().x) >= -20 &&
			(this->getBox()->getLocation().y - playerTwo->getBox()->getLocation().y) <= 20 &&
			(this->getBox()->getLocation().y - playerTwo->getBox()->getLocation().y) >= -20)
			signText->setVisible(true);
		else
			signText->setVisible(false);
	}
	
	cocos2d::Label * Sign::getLabel() const
	{
		return signText;
	}
}