#pragma once
#include <string>
#include "Player.h"
namespace Sedna {


	class Sign : public GameObject {
	public:
		Sign(std::string LABELTEXT,  cocos2d::Scene* s,const cocos2d::Vec2& LOCATION);
		Sign(std::string FILEPATH, cocos2d::Scene* s, const cocos2d::Vec2& LOCATION,bool CONSTWITHSPRITE);
		~Sign();

		void signUpdate(Player* playerOne);
		void animate(float dt,std::string TEMPSPRITE);

		cocos2d::Sprite* getDisplayedSprite() const;
		cocos2d::Label* getLabel() const;
	private:
		bool constructedWithSprite = false;
		///<not to be confused with the game object sprite of the sign itself>
		cocos2d::Sprite* displayedSprite;
		std::string spritepath;

		cocos2d::Label* signText;
		std::string labelText;

		bool hasAnimated = false;
		float animationTimer = 0.0f;

	};
}