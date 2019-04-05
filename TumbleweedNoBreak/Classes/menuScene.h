#pragma once
#include "cocos2d.h"
#include "XinputManager.h"
#include "Tutorial.h"
namespace Sedna {

	

	class SednaMenu {
	public:
		//pass in however many labels you want
		SednaMenu(int args, ...);
	
		//select a place in the list
		void select(unsigned int index);
	
		//gets the selected index
		unsigned int getIndexOfSelected() const;
		//get the currently selected label out of the list
		std::vector<cocos2d::Label*> getLabelList() const;


		cocos2d::Label* operator[](const unsigned int);

	private:
		unsigned lastIndex = 0;
		std::vector<cocos2d::Label*> labelList;
	};



}
class MenuScene : public cocos2d::Scene,public Tutorial {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//void update(float dt);

	void initMenu();
	

	void update(float dt);

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MenuScene);
private:
	bool playingMusic = false;

	static bool end;
	cocos2d::Director* director;

	cocos2d::Sprite* background;
	cocos2d::Menu* menu;

	Sedna::XinputManager manager;
	Sedna::XinputController* p1Controller;//these allow for Xinput in the menu 
	Sedna::Stick p1Sticks[2];

	Sedna::SednaMenu* menuM;
	cocos2d::Label* mLabel;//labels for the main menu
	cocos2d::Label* mLabel2;
	cocos2d::Label* mLabel3;

	Sedna::SednaMenu* menuO;
	cocos2d::Label* oLabel;//labels for the options menu
	cocos2d::Label* oLabel2;

	std::string oLabelStrings[2] = {"Music: Off","Music: On"};//Strings for the options menu
	std::string oLabel2Strings[2] = { "Tutorial: Off","Tutorial: On" };

	float selectWait = 0.0f;//this variable stops you from selecting an item every single update which is impossible for the player to know if it will be on or off when they release the button
	float menuWait = 0.0f;//this does the same as above but for moving the stick selection so they can stop in the center
	bool optionMenuBool = false;//this tells us if the Option menu is open or not

	cocos2d::Sprite* bButton;//these labels are polish so that the player can see the select and back Button respectively
	cocos2d::Label* bButtonLabel;

	cocos2d::Sprite* aButton;
	cocos2d::Label* aButtonLabel;
};
