#pragma once
#include <string>
#include "Player.h"
namespace Sedna {


	class Sign : public GameObject {
	public:
		//two constructors, one for a sign specifically with text, one for a sign that displays images
		Sign(std::string LABELTEXT,  cocos2d::Scene* s,const cocos2d::Vec2& LOCATION);
		Sign(std::string FILEPATH, cocos2d::Scene* s, const cocos2d::Vec2& LOCATION,bool CONSTWITHSPRITE);
		~Sign();

		//updates the sign, pass in player one for this game, but you *can* pass in any player
		void signUpdate(Player* playerOne);

		//animate the displayed sprite
		void animate(float dt,std::string TEMPSPRITE);

		//get the displayed sprite
		cocos2d::Sprite* getDisplayedSprite() const;
		
		//get the label that the sign displays
		cocos2d::Label* getLabel() const;
	private:
		bool constructedWithSprite = false;
		
		///<not to be confused with the game object sprite of the sign itself>
		cocos2d::Sprite* displayedSprite;
		std::string spritepath;

		//text stuff
		cocos2d::Label* signText;
		std::string labelText;

		bool hasAnimated = false;
		float animationTimer = 0.0f;

	};
}