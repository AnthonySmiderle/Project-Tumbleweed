#include "menuScene.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MenuScene::createScene() {
	return MenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


namespace Sedna {

	SednaMenu::SednaMenu(XinputController *c, Stick s, int args, ...)
		:menuController(c)
	{
#ifdef _DEBUG
		if (args <= 0)
			exit(std::stoi("excuse me what the fuck"));
#endif
		//*menuSticks = *s;
		menuStick = s;
		menuStick = s;
		va_list LIST;
		va_start(LIST, args);
		for (int i = 0; i < args; i++) {
			labelList.push_back(va_arg(LIST, cocos2d::Label*));
		}
		va_end(LIST);

		createdWithVA = true;
	}

	SednaMenu::SednaMenu(XinputController *c, Stick s, cocos2d::Label * l1, cocos2d::Label * l2)
	{
		menuController = c;
		menuStick = s;
		label1 = l1;
		label2 = l2;
		createdWithVA = false;

	}

	void SednaMenu::hover(unsigned int index)
	{
		if (createdWithVA) {
#ifdef _DEBUG
			if (index < 0 || index > labelList.size() - 1)
				exit(std::stoi("oi what the fuck"));
#endif
			labelList[index]->enableUnderline();
		}
	}

	std::vector<cocos2d::Label*> SednaMenu::getLabelList() const
	{
		return labelList;
	}

	cocos2d::Label * SednaMenu::getLabel1() const
	{
		return label1;
	}

	cocos2d::Label * SednaMenu::getLabel2() const
	{
		return label2;
	}

}



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
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	director = Director::getInstance();

	p1Controller = manager.getController(0);
	p1Controller->updateSticks(p1Sticks);
	p2Controller = manager.getController(1);

	manager.update();

	label = Label::create("Toaster Bath", "fonts/Roboto/Roboto-Regular.ttf", 25);
	label2 = Label::create("Time to Commit", "fonts/Roboto/Roboto-Regular.ttf", 25);

	menuE = new Sedna::SednaMenu(p1Controller, p1Sticks[0], 2, label, label2);

	initMenu();

	menuE->hover(0);

	return true;
}



void MenuScene::initMenu()
{
	Vec2 windowSize = director->getWinSizeInPixels();

	background = Sprite::create("DOS.jpg");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	background->setScale(10.85f, 10.92f);
	background->setPosition(0, 0);

	title = Label::create("Goldman's Saloon", "fonts/Roboto/Roboto-Regular.ttf", 25);
	title->setAnchorPoint(Vec2(0.0f, 0.0f));
	title->setPosition(Vec2(140, 250));
	title->enableShadow();

	//auto playLabel = Label::create("Start Game", "fonts/arial.ttf", 24);
	//auto exitLabel = Label::create("Exit Game", "fonts/arial.ttf", 24);
	//exitLabel->enableShadow();
	//playLabel->enableShadow();
	//
	//auto playButton = MenuItemLabel::create(playLabel, [&](Ref* sender) {
	//	auto gameScene = HelloWorld::createScene();
	//	director->replaceScene(TransitionFade::create(2.0f, gameScene));
	//});
	//auto exitButton = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
	//	director->end();
	//});
	//
	//playButton->setPosition(140, 250);
	//exitButton->setPosition(140, 200);
	//
	//menu = Menu::create(playButton, exitButton, NULL);
	//menu->setPosition(140, 250);
	//this->addChild(menu);
	for (int i = 0; i < menuE->getLabelList().size(); i++) {
		this->addChild(menuE->getLabelList()[i]);
		menuE->getLabelList()[i]->enableShadow();
		menuE->getLabelList()[i]->setAnchorPoint(cocos2d::Vec2(0, 0));
		if (i == 0)
			menuE->getLabelList()[i]->setPosition(140, 100);
		else {
			menuE->getLabelList()[i]->setPosition(140, menuE->getLabelList()[i - 1]->getPosition().y + 30);

		}
	}

	this->addChild(background, -1000);
	this->addChild(title);
}

void MenuScene::onEnter()
{
	Scene::onEnter();
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

