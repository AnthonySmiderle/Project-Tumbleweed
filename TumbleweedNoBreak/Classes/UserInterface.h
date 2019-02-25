#pragma once
#include "cocos2d.h"

namespace Sedna {

	class UI {
	public:

		UI();
		UI(cocos2d::Sprite* UISPRITE, cocos2d::Label* UILABEL);
		UI(const char* spriteFilepath, const char* labelText);

		
		~UI();
		cocos2d::Sprite* getSprite() const;
		cocos2d::Label* getLabel() const;


	private:
		cocos2d::Sprite* uiSprite;//the sprite that is associated with the label
		cocos2d::Label* uiLabel;//the numbers or information being displayed
	};




}