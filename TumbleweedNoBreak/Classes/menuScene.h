#pragma once
#include "cocos2d.h"
#include "XinputManager.h"
namespace Sedna {

	class SednaMenu {
	public:
		SednaMenu(XinputController* c, Stick s, int args, ...);
		SednaMenu(XinputController *c, Stick s, cocos2d::Label* l1, cocos2d::Label* l2);

		void hover(unsigned int index);

		//a menu has a...
		//label(s)
		//controller input
		//functions to highlight text when you're hovering over it
		std::vector<cocos2d::Label*> getLabelList() const;
		cocos2d::Label* getLabel1() const;
		cocos2d::Label* getLabel2() const;
	private:
		bool createdWithVA = false;
		cocos2d::Label* label1;
		cocos2d::Label* label2;

		std::vector<cocos2d::Label*> labelList;
		XinputController *menuController;
		Stick menuStick;
	};



}
class MenuScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//void update(float dt);

	void initMenu();
	void onEnter();

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MenuScene);
private:
	cocos2d::Director* director;

	cocos2d::Sprite* background;
	cocos2d::Label* title;
	cocos2d::Menu* menu;

	Sedna::XinputManager manager;
	Sedna::XinputController* p1Controller;
	Sedna::XinputController* p2Controller;
	Sedna::Stick p1Sticks[2];
	Sedna::Stick p2Sticks[2];

	Sedna::SednaMenu* menuE;
	cocos2d::Label* label;
	cocos2d::Label* label2;

};
