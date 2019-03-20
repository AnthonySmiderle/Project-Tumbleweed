#pragma once
#include <string>
#include "Player.h"
namespace Sedna {


	class Sign : public GameObject {
	public:
		Sign(std::string LABELTEXT,  cocos2d::Scene* s,const cocos2d::Vec2& LOCATION);
		~Sign();

		void signUpdate(Player* playerOne, Player* playerTwo);

		cocos2d::Label* getLabel() const;
	private:
		cocos2d::Label* signText;
		std::string labelText;

	};
}