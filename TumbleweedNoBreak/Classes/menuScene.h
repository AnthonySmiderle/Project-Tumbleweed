#pragma once
#include "cocos2d.h"
#include "XinputManager.h"
namespace Sedna {

	

	class SednaMenu {
	public:
		//pass in however many labels you want
		SednaMenu(int args, ...);
	
		//select a place in the list
		void select(unsigned int index);
	
		//does what it says on the tin
		unsigned int getIndexOfSelected() const;
		//get the currently selected label out of the list
		std::vector<cocos2d::Label*> getLabelList() const;


		cocos2d::Label* operator[](const unsigned int);

	private:
		unsigned lastIndex = 0;
		std::vector<cocos2d::Label*> labelList;
	};



}
class MenuScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//void update(float dt);

	void initMenu();
	

	void update(float dt);

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MenuScene);
private:
	static bool end;
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
	cocos2d::Label* label3;

	Sedna::SednaMenu* menuO;
	cocos2d::Label* oLabel;
	cocos2d::Label* oLabel2;
	std::string oLabelStrings[2] = {"Music: Off","Music: On"};
	std::string oLabel2Strings[2] = { "Tutorial: Off","Tutorial: On" };
	float selectWait = 0.0f;

	float menuWait = 0.0f;
	bool optionMenuBool = false;
};
