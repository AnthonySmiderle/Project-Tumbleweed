/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}



// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
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
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

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




	p1Controller = managerR.getController(0);
	p2Controller = managerR.getController(1);

	managerR.update();

	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);
	p2Controller->updateSticks(p2Sticks);
	p2Controller->getTriggers(p2Triggers);

	initSprites();



	this->scheduleUpdate();

	initPauseMenu();
	return true;
}

void HelloWorld::update(float dt)
{
	sManager.update(dt, DDOS->getSprite()->getPosition().y);
	managerR.update();
	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);
	p2Controller->updateSticks(p2Sticks);
	p2Controller->getTriggers(p2Triggers);

	srand(time(0));
	checkInput(dt);
	getCollisions();


	if (p1Controller->isButtonPressed(Sedna::Y))
	{
		this->getDefaultCamera()->setPosition(cocos2d::Vec2(this->getDefaultCamera()->getPosition().x,
			this->getDefaultCamera()->getPosition().y + 1));
		DDOS->getSprite()->setPosition(cocos2d::Vec2(100, (DDOS->getSprite()->getPosition().y + 1)));

	}
#ifdef _DEBUG
	if (p1Controller->isButtonPressed(Sedna::X)) {
		for (unsigned int i = 0; i < outlawList.size(); i++)
			outlawList[i]->getBox()->getDrawNode()->setVisible(true);
		for (unsigned int i = 0; i < tableList.size(); i++)
			tableList[i]->getBox()->getDrawNode()->setVisible(true);
		playerOne->getBox()->getDrawNode()->setVisible(true);
		playerTwo->getBox()->getDrawNode()->setVisible(true);
	}
	else {
		for (unsigned int i = 0; i < outlawList.size(); i++)
			outlawList[i]->getBox()->getDrawNode()->setVisible(false);
		for (unsigned int i = 0; i < tableList.size(); i++)
			tableList[i]->getBox()->getDrawNode()->setVisible(false);
		playerOne->getBox()->getDrawNode()->setVisible(false);
		playerTwo->getBox()->getDrawNode()->setVisible(false);
	}
#endif
	if (enemyTimer > 4.0f)
	{
		enemyTimer = 0.0f;
		hasSpawn = false;
	}
	if (!enemyTimer)
	{
		hasSpawn = true;
		int x = rand() % 100 + 1 + (rand() % 200 + 1);
		int y = DDOS->getSprite()->getPosition().y - 75;
		outlaw = new Sedna::Outlaw(x, y);
		Sedna::BaseObjectManager::outlawBObjects.push_back(outlaw);
		this->addChild(outlaw->getBox()->getDrawNode());
		this->addChild(outlaw->getSprite());
		outlawList.push_back(new Sedna::Outlaw(*outlaw));

	}
	if (hasSpawn)
		enemyTimer += dt;

	for (int i = 0; i < outlawList.size(); i++) {
		outlawList[i]->shoot(dt, this);
	}
	bigCheckList();

	a->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y));
	b->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 30));
	rsl->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 60));
	rsr->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 90));
	rt->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 120));

	playerOne->updateGameObject();
	playerTwo->updateGameObject();
	//baseTable->updateGameObject();
	bounceFunct();
}

void HelloWorld::initSprites()
{
	DDOS = new Sedna::GameObject("DOS.jpg", cocos2d::Vec2(100, 300), 1, 1, 1);
	this->addChild(DDOS->getBox()->getDrawNode());
	this->addChild(DDOS->getSprite());
	DDOS->getSprite()->setVisible(true);

	playerTwo = new Sedna::Player(2, 300, 100, managerR);
	this->addChild(playerTwo->getBox()->getDrawNode());
	this->addChild(playerTwo->getSprite(), 10);

	bg = cocos2d::Sprite::create("bg1.png");
	this->addChild(bg, -1000);
	bg->setScale(0.85f);
	bg->setPosition(483 / 2.0f, 315 / 2.0f);

	playerOne = new Sedna::Player(1, 100, 100, managerR);
	this->addChild(playerOne->getBox()->getDrawNode());
	this->addChild(playerOne->getSprite(), 10);

	a = cocos2d::Sprite::create("a.png");
	b = cocos2d::Sprite::create("b.png");
	rsl = cocos2d::Sprite::create("rsl.png");
	rsr = cocos2d::Sprite::create("rsr.png");
	rt = cocos2d::Sprite::create("rt.png");

	this->addChild(a, 1);
	this->addChild(b, 1);
	this->addChild(rsl, 1);
	this->addChild(rsr, 1);
	this->addChild(rt, 1);

	a->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y));
	b->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 30));
	rsl->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 60));
	rsr->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 90));
	rt->setPosition(cocos2d::Vec2(450,
		this->getDefaultCamera()->getPosition().y + 120));

	//replace this with a base table that can be copied later
	for (int i = 0; i < 4; i++) {
		baseTable = new Sedna::Table(100 + rand() % 200, rand() % 200 + rand() % 100);
		this->addChild(baseTable->getBox()->getDrawNode());
		this->addChild(baseTable->getSprite());
		tableList.push_back(new Sedna::Table(*baseTable));
		Sedna::BaseObjectManager::tableBObjects.push_back(baseTable);

	}
	recursiveFunction(tableList);
}

void HelloWorld::checkInput(float dt)
{
	playerOne->checkInput(dt);
	playerTwo->checkInput(dt);
	playerOne->shoot(dt, this);
	playerTwo->shoot(dt, this);
}

void HelloWorld::getCollisions()
{
	playerOne->checkTableStuff(tableList);
	playerTwo->checkTableStuff(tableList);
}

void HelloWorld::bigCheckList()
{

	if (outlawList.size() > 4) {
		outlawList.front()->removeProjectiles();
		outlawList.front()->getBox()->getDrawNode()->removeFromParent();
		outlawList.front()->getSprite()->removeFromParent();
		outlawList.erase(outlawList.begin());
		Sedna::BaseObjectManager::outlawBObjects.erase(Sedna::BaseObjectManager::outlawBObjects.begin());
	}


	recursiveFunction(outlawList);

	playerOne->checkBCollision(outlawList);
	playerTwo->checkBCollision(outlawList);
	playerOne->checkBCollision(tableList);
	playerTwo->checkBCollision(tableList);
	playerOne->checkList();
	playerTwo->checkList();
	for (unsigned int i = 0; i < tableList.size(); i++)
		tableList[i]->updateGameObject();

	for (unsigned int i = 0; i < outlawList.size(); i++) {

		outlawList[i]->checkBCollision(tableList);
		outlawList[i]->checkBCollision(playerOne);
		outlawList[i]->checkBCollision(playerTwo);
		outlawList[i]->checkList();
		outlawList[i]->updateGameObject();

	}
	for (unsigned int i = 0; i < tableList.size(); i++) {
		for (unsigned int j = 0; j < tableList.size(); j++) {
			if (i == j)
				continue;
				tableList[i]->collideTable(tableList);
		}
	}



}

void HelloWorld::recursiveFunction(std::vector<Sedna::Outlaw*>& outlawList)
{
yes:
	for (unsigned int i = 0; i < outlawList.size(); i++) {
		for (unsigned int j = 0; j < outlawList.size(); j++) {
			if (i == j)
				continue;
			if (outlawList[i]->getBox()->checkCollision(*outlawList[j]->getBox())) {
				outlawList[i]->getBox()->setLocation(cocos2d::Vec2(rand() % 100 + 1 + (rand() % 200 + 1),
					outlawList[i]->getBox()->getLocation().y));
				goto yes;
			}

		}
	}
}
void HelloWorld::recursiveFunction(std::vector<Sedna::Table*>& tableList)
{
yes:
	for (unsigned int i = 0; i < tableList.size(); i++) {
		for (unsigned int j = 0; j < tableList.size(); j++) {
			if (i == j)
				continue;
			if (tableList[i]->getBox()->checkCollision(*tableList[j]->getBox())) {
				tableList[i]->getBox()->setLocation(cocos2d::Vec2(rand() % 100 + 1 + (rand() % 200 + 1),
					tableList[i]->getBox()->getLocation().y));
				goto yes;
			}

		}
	}
}

void HelloWorld::checkPosAll()
{
	for (unsigned int i = 0; i < outlawList.size(); i++)
	{
		if (outlawList[i]->getBox()->getLocation().y < DDOS->getSprite()->getPosition().y - 400)
		{
			outlawList[i]->removeProjectiles();
			outlawList[i]->getBox()->getDrawNode()->removeFromParent();
			outlawList[i]->getSprite()->removeFromParent();
			outlawList.erase(outlawList.begin() + i);
			Sedna::BaseObjectManager::outlawBObjects.erase(Sedna::BaseObjectManager::outlawBObjects.begin() + i);
			i--;
		}
	}
	for (unsigned int i = 0; i < tableList.size(); i++)
	{
		if (tableList[i]->getBox()->getLocation().y < DDOS->getSprite()->getPosition().y - 400)
		{
			tableList[i]->getBox()->getDrawNode()->removeFromParent();
			tableList[i]->getSprite()->removeFromParent();
			tableList.erase(tableList.begin() + i);
			Sedna::BaseObjectManager::tableBObjects.erase(Sedna::BaseObjectManager::tableBObjects.begin() + i);
			i--;
		}
	}
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::bounceFunct()
{
	if ((int)playerOne->getBox()->getLocation().x >= barRightMax)
	{
		playerOne->getBox()->setLocation(cocos2d::Vec2(430, playerOne->getBox()->getLocation().y));
		playerOne->getBox()->addForce(-25, 0);
	}

	if ((int)playerOne->getBox()->getLocation().x <= barLeftMax)
	{
		playerOne->getBox()->setLocation(cocos2d::Vec2(90, playerOne->getBox()->getLocation().y));
		playerOne->getBox()->addForce(25, 0);
	}
	if ((int)playerTwo->getBox()->getLocation().x >= barRightMax)
	{
		playerTwo->getBox()->setLocation(cocos2d::Vec2(430, playerTwo->getBox()->getLocation().y));
		playerTwo->getBox()->addForce(-25, 0);
	}

	if ((int)playerTwo->getBox()->getLocation().x <= barLeftMax)
	{
		playerTwo->getBox()->setLocation(cocos2d::Vec2(90, playerTwo->getBox()->getLocation().y));
		playerTwo->getBox()->addForce(25, 0);
	}

	for (unsigned int i = 0; i < tableList.size(); i++)
	{
		if ((int)tableList[i]->getBox()->getLocation().x >= barRightMax)
		{
			tableList[i]->getBox()->setLocation(cocos2d::Vec2(430, tableList[i]->getBox()->getLocation().y));
			tableList[i]->getBox()->addForce(-25, 0);
		}

		if ((int)tableList[i]->getBox()->getLocation().x <= barLeftMax)
		{
			tableList[i]->getBox()->setLocation(cocos2d::Vec2(90, tableList[i]->getBox()->getLocation().y));
			tableList[i]->getBox()->addForce(25, 0);
		}
	}
}



void HelloWorld::initPauseMenu() {
	Label* pausedLabel = Label::create("PAUSED", "fonts/Roboto/Roboto-Regular.ttf", 48, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	pausedLabel->enableShadow();

	Label* resumeLabel = Label::create("Resume Game", "fonts/Roboto/Roboto-Regular.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::BOTTOM);
	resumeLabel->enableShadow();

	MenuItem* pausedItem = MenuItemLabel::create(pausedLabel, NULL);
	MenuItem* resumeButton = MenuItemLabel::create(resumeLabel, [&](Ref* sender) { togglePause(); });

	pausedItem->setPosition(0, 100);
	resumeButton->setPosition(0, -200);

	pauseMenu = Menu::create(pausedItem, resumeButton, NULL);

	this->addChild(pauseMenu, 100);
	pauseMenu->setVisible(false);
}

void HelloWorld::togglePause() {
	paused ^= 1;

	if (paused) {
		pauseMenu->setVisible(true);
	}
	else {
		pauseMenu->setVisible(false);
	}
}