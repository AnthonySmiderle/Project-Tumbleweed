#include "menuScene.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "HelloWorldScene.h"
#include "MusicList.h"
#include "Options.h"

USING_NS_CC;

bool MenuScene::end = false;

Scene* MenuScene::createScene() {
	return MenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


namespace Sedna {

	SednaMenu::SednaMenu(int args, ...)//create the Menu based on the arguments provided
	{
		va_list LIST;
		va_start(LIST, args);
		for (int i = 0; i < args; i++) {
			labelList.push_back(va_arg(LIST, cocos2d::Label*));
		}
		va_end(LIST);

	}



	void SednaMenu::select(unsigned int index)
	{
#ifdef _DEBUG
		if (index < 0 || index > labelList.size() - 1)
			exit(std::stoi("exception"));
#endif

		for (unsigned i = 0; i < labelList.size(); i++) {
			if (i == index)
				continue;
			else {
				labelList[i]->enableWrap(false);
				labelList[i]->disableEffect(LabelEffect::UNDERLINE);
			}
		}

		//labelList[lastIndex]->enableWrap(false);
		labelList[index]->enableWrap(false);
		//labelList[lastIndex]->disableEffect(LabelEffect::UNDERLINE);
		labelList[index]->enableUnderline();

		labelList[index]->enableWrap(true);

		//lastIndex = index;
	}

	unsigned int SednaMenu::getIndexOfSelected() const
	{
		for (int i = 0; i < labelList.size(); i++) {
			if (labelList[i]->isWrapEnabled())
				return i;
		}
		return 0;
	}


	std::vector<cocos2d::Label*> SednaMenu::getLabelList() const
	{
		return labelList;
	}

	cocos2d::Label * SednaMenu::operator[](const unsigned int index)
	{
		if (index > labelList.size())
			exit(std::stoi("We're out of index chief"));
		return labelList[index];
	}

}






//init the scene provided by cocos but we place what needs to be initialized in this section
bool MenuScene::init() {
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	

	

	director = Director::getInstance();

	p1Controller = manager.getController(0);
	p1Controller->updateSticks(p1Sticks);

	manager.update();//one update to avoid errors

	//creation of the menu and labels
	mLabel = Label::create("Exit", "fonts/Montague.ttf", 25);
	mLabel2 = Label::create("Options", "fonts/Montague.ttf", 25);
	mLabel3 = Label::create("Start Game", "fonts/Montague.ttf", 25);
	menuM = new Sedna::SednaMenu(3, mLabel, mLabel2, mLabel3);

	//creation of the options menu and options label
	oLabel = Label::create(oLabelStrings[Sedna::optionStuff::music], "fonts/Montague.ttf", 25);
	oLabel2 = Label::create(oLabel2Strings[((Tutorial*)this)->tutorial], "fonts/Montague.ttf", 25);
	menuO = new Sedna::SednaMenu(2,oLabel,oLabel2);

	//creation and placement of the A and B button for the menu
	bButton = Sprite::create("b.png");
	bButton->setScale(0.6);
	bButtonLabel = Label::create(": Back", "fonts/Montague.ttf", 12);
	bButtonLabel->setAnchorPoint(Vec2(0, 0));
	bButton->setAnchorPoint(Vec2(0, 0));
	bButton->setZOrder(1000);
	bButtonLabel->setZOrder(1000);
	bButton->setPosition(10,50);
	bButtonLabel->setPosition(30,50);
	bButton->setVisible(false);
	bButtonLabel->setVisible(false);
	this->addChild(bButton);
	this->addChild(bButtonLabel);

	//A Button stuff
	aButton = Sprite::create("a1.png");
	aButton->setScale(0.6);
	aButtonLabel = Label::create(": Select", "fonts/Montague.ttf", 12);
	aButtonLabel->setAnchorPoint(Vec2(0, 0));
	aButton->setAnchorPoint(Vec2(0, 0));
	aButton->setZOrder(1000);
	aButtonLabel->setZOrder(1000);
	aButton->setPosition(10, 70);
	aButtonLabel->setPosition(30, 70);
	aButton->setVisible(true);
	aButtonLabel->setVisible(true);
	this->addChild(aButton);
	this->addChild(aButtonLabel);

	//creation of the menu
	initMenu();

	menuM->select(2);//select the top one of the menu

	end = false;
	this->scheduleUpdate();

	return true;
}

void MenuScene::update(float dt)
{
	if (director->getInstance()->getRunningScene() == this) {

		if (!playingMusic) {//if the music is not playing
			cocos2d::experimental::AudioEngine::play2d("bgm2.mp3", true);//play the music
			playingMusic = true;//we are now playing music
		}


		manager.update();//update x input
		p1Controller->updateSticks(p1Sticks);
		if (!optionMenuBool)//checking if the option menu is open
		{
			if (!menuWait)//so that the player doesn't skip over the options every time they try to get to it (cannot condense with the line above) 
				//it is a float being used as a boolean 
			{
				if (p1Sticks[0].y < -0.3f && menuM->getIndexOfSelected() != 0)//stopping the player from trying to get out of the index
				{

					menuM->select(menuM->getIndexOfSelected() - 1);//go to the next index
					menuWait += dt;//this stops the player from going through the entire menu in a split second
				}
				else if (p1Sticks[0].y > 0.3f&&!(menuM->getIndexOfSelected() + 1 > menuM->getLabelList().size() - 1))//reverse of the top
				{
					menuM->select(menuM->getIndexOfSelected() + 1);//go to the next index
					menuWait += dt;
				}
			}
			else//this will run if the wait timer is not 0
			{
				menuWait += dt;//add the time to it
				if (menuWait >= 0.3)//if a third of a second has passed since the last move
					menuWait = 0.0f;//reset the timer so they can move their selection again
			}

			if (menuM->getIndexOfSelected() == 2 && p1Controller->isButtonPressed(Sedna::A)) {//if the play button is selected
				auto game = HelloWorld::createScene();//creation of the game scene
				cocos2d::experimental::AudioEngine::play2d("cha ching.mp3", false);//play a nice sound (Polish)

				cocos2d::experimental::AudioEngine::stopAll();//stop the main menu music
				end = true;//and end the scene
				//this->onExit();
				director->replaceScene(TransitionFade::create(1.0f, game));//transition to the other scene
			}
			if (menuM->getIndexOfSelected() == 1 && p1Controller->isButtonPressed(Sedna::A)) {//if the options menu is selected
				optionMenuBool = true;
				selectWait += dt;//stop them them selecting multiple times in the split second
				for (unsigned int i=0; i<menuM->getLabelList().size();i++)
				{
					menuM->getLabelList()[i]->setVisible(false);//hide the regular menu
				}
				for (unsigned int i=0; i <menuO->getLabelList().size();i++)
				{
					menuO->getLabelList()[i]->setVisible(true);//show the option menu
				}
				menuO->select(1);//select the top of the menu
				bButton->setVisible(true);//show the back button stuff
				bButtonLabel->setVisible(true);
			}
			if (menuM->getIndexOfSelected() == 0 && p1Controller->isButtonPressed(Sedna::A)) {//if the end game button is selected
				cocos2d::experimental::AudioEngine::play2d("cha ching.mp3", false);//play a sound
				exit(0);//end the game
			}
		}
		else//if the options menu is the current menu
		{
			if (p1Sticks[0].y < -0.3f && menuO->getIndexOfSelected() != 0)//index checking
			{

				menuO->select(menuM->getIndexOfSelected() - 1);
				menuWait += dt;
			}
			if (p1Sticks[0].y > 0.3f&& !(menuO->getIndexOfSelected() + 1 > menuO->getLabelList().size() - 1))//more index checking
			{
				menuO->select(menuO->getIndexOfSelected() + 1);
				menuWait += dt;
			}

			if (menuO->getIndexOfSelected() == 0 && p1Controller->isButtonPressed(Sedna::A) && !selectWait)//if they are selecting the music
			{
				((Tutorial*)this)->music ^= 1;
				menuO->getLabelList()[0]->setString(oLabelStrings[((Tutorial*)this)->music]);//change the boolean to its inverse
				selectWait += dt;
			}
			else if (menuO->getIndexOfSelected() == 1 && p1Controller->isButtonPressed(Sedna::A) && !selectWait)//for changing the tutorial
			{
				((Tutorial*)this)->tutorial ^= 1;
				menuO->getLabelList()[1]->setString(oLabel2Strings[((Tutorial*)this)->tutorial]);
				selectWait += dt;
			}
			else//if none has been seleced
			{
				if(selectWait)//add the time if the boolean is not zero
					selectWait += dt;
				if (selectWait >= 0.3f)//if it's greater than 0.3 seconds reset it
					selectWait = 0.0f;
			}
			if (p1Controller->isButtonPressed(Sedna::B))//if the b button is pressed
			{
				optionMenuBool = false;//go back to the main menu
				for (unsigned int i = 0; i < menuM->getLabelList().size(); i++)
				{
					menuM->getLabelList()[i]->setVisible(true);//show the main menu
				}
				for (unsigned int i = 0; i < menuO->getLabelList().size(); i++)
				{
					menuO->getLabelList()[i]->setVisible(false);//hide the options menu
				}
				menuM->select(1);//select the options in the main menu
				bButton->setVisible(false);
				bButtonLabel->setVisible(false);//hide the B button
			}
		}

	}
}

void MenuScene::initMenu()
{
	//preload the sounds for the menu
	cocos2d::experimental::AudioEngine::preload("cha ching.mp3");
	cocos2d::experimental::AudioEngine::preload("bgm2.mp3");
	Vec2 windowSize = director->getWinSizeInPixels();

	//create the background sprite 
	background = Sprite::create("Menu.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	background->setScale(0.85f, 0.92f);
	background->setPosition(0, 0);


	//create the labels for the menu
	for (int i = 0; i < menuM->getLabelList().size(); i++) {
		this->addChild(menuM->getLabelList()[i]);
		menuM->getLabelList()[i]->enableShadow();
		menuM->getLabelList()[i]->setAnchorPoint(cocos2d::Vec2(0, 0));
		if (i == 0)
			menuM->getLabelList()[i]->setPosition(140, 50);
		else {
			menuM->getLabelList()[i]->setPosition(140, menuM->getLabelList()[i - 1]->getPosition().y + 30);

		}
	}

	//create the labels for the option menu
	for (int i = 0; i < menuO->getLabelList().size(); i++) {
		this->addChild(menuO->getLabelList()[i]);
		menuO->getLabelList()[i]->enableShadow();
		menuO->getLabelList()[i]->setAnchorPoint(cocos2d::Vec2(0, 0));
		if (i == 0)
			menuO->getLabelList()[i]->setPosition(140, 50);
		else {
			menuO->getLabelList()[i]->setPosition(140, menuO->getLabelList()[i - 1]->getPosition().y + 30);
		}
		menuO->getLabelList()[i]->setVisible(false);
	}	

	this->addChild(background, -1000);//add the background image
}





void MenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

