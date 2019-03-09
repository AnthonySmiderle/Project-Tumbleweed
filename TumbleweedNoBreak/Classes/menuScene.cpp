#include "menuScene.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "HelloWorldScene.h"
#include "MusicList.h"

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

	SednaMenu::SednaMenu(int args, ...)
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
			exit(std::stoi("oi what the fuck"));
#endif

		labelList[lastIndex]->enableWrap(false);
		labelList[index]->enableWrap(false);
		labelList[lastIndex]->disableEffect(LabelEffect::UNDERLINE);
		labelList[index]->enableUnderline();

		labelList[index]->enableWrap(true);

		lastIndex = index;
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
	//p2Controller = manager.getController(1);

	p1Controller = manager.getController(0);
	p1Controller->updateSticks(p1Sticks);

	manager.update();

	label = Label::create("Exit", "fonts/Montague.ttf", 25);
	label2 = Label::create("Start Game", "fonts/Montague.ttf", 25);

	menuE = new Sedna::SednaMenu(2, label, label2);

	initMenu();

	menuE->select(1);


	cocos2d::experimental::AudioEngine::play2d("bgm2.mp3", true);
	this->scheduleUpdate();

	return true;
}

void MenuScene::update(float dt)
{
	if (!end) {

		manager.update();
		p1Controller->updateSticks(p1Sticks);

		if (p1Sticks[0].y < -0.3f && menuE->getIndexOfSelected() != 0) {

			menuE->select(menuE->getIndexOfSelected() - 1);
		}
		if (p1Sticks[0].y > 0.3f) {
			if (menuE->getIndexOfSelected() + 1 > menuE->getLabelList().size() - 1) {
				//do some other shit i dont wanna figure out right now
			}
			else
				menuE->select(menuE->getIndexOfSelected() + 1);

		}

		if (menuE->getIndexOfSelected() == 1 && p1Controller->isButtonPressed(Sedna::A)) {
			auto game = HelloWorld::createScene();
			cocos2d::experimental::AudioEngine::play2d("cha ching.mp3", false);

			cocos2d::experimental::AudioEngine::stop(0);
			end = true;
			HelloWorld::setEnd(false);
			//this->onExit();
			director->replaceScene(TransitionFade::create(2.0f, game));
		}
		if (menuE->getIndexOfSelected() == 0 && p1Controller->isButtonPressed(Sedna::A)) {
			cocos2d::experimental::AudioEngine::play2d(Music::menuSound[Music::MusicType], false);

			exit(0);

		}
	}
}

void MenuScene::initMenu()
{
	cocos2d::experimental::AudioEngine::preload("cha ching.mp3");
	cocos2d::experimental::AudioEngine::preload("bgm2.mp3");
	Vec2 windowSize = director->getWinSizeInPixels();

	background = Sprite::create("Menu.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	background->setScale(0.85f, 0.92f);
	background->setPosition(0, 0);

	title = Label::create("Goldman's Saloon", "fonts/Montague.ttf", 25);
	title->setAnchorPoint(Vec2(0.0f, 0.0f));
	title->setPosition(Vec2(140, 250));
	title->enableShadow();


	for (int i = 0; i < menuE->getLabelList().size(); i++) {
		this->addChild(menuE->getLabelList()[i]);
		menuE->getLabelList()[i]->enableShadow();
		menuE->getLabelList()[i]->setAnchorPoint(cocos2d::Vec2(0, 0));
		if (i == 0)
			menuE->getLabelList()[i]->setPosition(140, 50);
		else {
			menuE->getLabelList()[i]->setPosition(140, menuE->getLabelList()[i - 1]->getPosition().y + 30);

		}
	}

	this->addChild(background, -1000);
	this->addChild(title);
}





void MenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

