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
#include "AudioEngine.h"
#include "menuScene.h"
#include "MusicList.h"
#define CAMERASPEED 2

USING_NS_CC;

bool HelloWorld::end = false;

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

	//bottom label

	auto localL1 = cocos2d::Label::create("Exit to Main Menu", "fonts/Montague.ttf", 25);
	auto localL2 = cocos2d::Label::create("Resume", "fonts/Montague.ttf", 25);
	pauseMenu = new Sedna::SednaMenu(2, localL1, localL2);



	p1Controller = managerR.getController(0);
	p2Controller = managerR.getController(1);

	managerR.update();

	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);
	p2Controller->updateSticks(p2Sticks);
	p2Controller->getTriggers(p2Triggers);
	initSprites();

	director = cocos2d::Director::getInstance();
	this->scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
{
	if (!end) {


		managerR.update();
		p1Controller->updateSticks(p1Sticks);
		p1Controller->getTriggers(p1Triggers);
		p2Controller->updateSticks(p2Sticks);
		p2Controller->getTriggers(p2Triggers);


		//////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////

		if (playerOne->getCurrentGun()->getAmmo() <= 0)
			playerOne->setCurrnetGun(olReliable);


		if (p1Controller->isButtonPressed(Sedna::SELECT))
		{
			if (!TEMPPAUSE)
			{
				for (int i = 0; i < pauseMenu->getLabelList().size(); i++) {
					pausedLabel->setVisible(true);
					pauseMenu->getLabelList()[i]->setVisible(true);
				}
				TEMPPAUSE = true;
				TRUEPAUSE ^= 1;
			}
		}
		if (p1Controller->isButtonReleased(Sedna::SELECT))
			TEMPPAUSE = false;

		if (TRUEPAUSE)
		{
			paused = true;
			for (int i = 0; i < pauseMenu->getLabelList().size(); i++) {
				pausedLabel->setVisible(true);
				pauseMenu->getLabelList()[i]->setVisible(true);
			}

			if (p1Sticks[0].y < -0.3f && pauseMenu->getIndexOfSelected() != 0) {

				pauseMenu->select(pauseMenu->getIndexOfSelected() - 1);
			}
			if (p1Sticks[0].y > 0.3f) {
				if (pauseMenu->getIndexOfSelected() + 1 > pauseMenu->getLabelList().size() - 1) {
					//do some other shit i dont wanna figure out right now
				}
				else
					pauseMenu->select(pauseMenu->getIndexOfSelected() + 1);
			}

			if (pauseMenu->getIndexOfSelected() == 1 && p1Controller->isButtonPressed(Sedna::A)) {
				TRUEPAUSE = false;
			}
			if (pauseMenu->getIndexOfSelected() == 0 && p1Controller->isButtonPressed(Sedna::A)) {
				auto mMenu = MenuScene::create();
				cocos2d::experimental::AudioEngine::stopAll();
				cocos2d::experimental::AudioEngine::play2d(Music::menuSound[Music::MusicType], false);
				end = true;
				MenuScene::setEnd(false);
				//this->onExit();
				director->replaceScene(TransitionFade::create(2.0f, mMenu));
			}
		}
		else {
			for (int i = 0; i < pauseMenu->getLabelList().size(); i++) {
				pausedLabel->setVisible(false);
				pauseMenu->getLabelList()[i]->setVisible(false);
			}
		}

		if (!TRUEPAUSE)
		{
			if (p1Triggers.LT > 0 && !bulletTime)//triggers can be replaced by a power up boolean for a drink instead of a toggle thing
			{
				bulletTime = true;
			}
			if (bulletTime)
			{
				togglePause();
			}
			if (p1Triggers.LT == 0 && p2Triggers.LT == 0)
			{
				bulletTime = false;
				paused = false;
			}
			if (gameStart < 5)
			{
				gameStart += dt;
				paused = true;
				startLabel->setVisible(true);
				if (gameStart > 1 && gameStart < 2)
				{
					startLabel->setString("3");
					if (!playMusic) {
						cocos2d::experimental::AudioEngine::play2d("bgm.mp3", true);
						playMusic = true;
					}
				}
				else if (gameStart > 2 && gameStart < 3)
				{
					startLabel->setString("2");
				}
				else if (gameStart > 3 && gameStart < 4)
				{
					startLabel->setString("1");
				}
				else if (gameStart > 4 && gameStart < 5) {
					startLabel->setString("0");

				}
				else
				{
					startLabel->setVisible(false);
				}
			}

		}

		if (!paused)
		{
			sManager.update(dt, DDOS->getSprite()->getPosition().y);

			srand(time(0));
			checkInput(dt);
			getCollisions();


#ifdef _DEBUG
			if (p1Controller->isButtonPressed(Sedna::Y))
				moveScreen ^= 1;
			if (moveScreen)
			{
				for (int i = 0; i < pauseMenu->getLabelList().size(); i++) {
					pauseMenu->getLabelList()[i]->setPosition(cocos2d::Vec2(pauseMenu->getLabelList()[i]->getPosition().x,
						pauseMenu->getLabelList()[i]->getPosition().y + CAMERASPEED));
				}
				pausedLabel->setPosition(pausedLabel->getPosition() + cocos2d::Vec2(0, CAMERASPEED));

				//playerOne->getUI()->getLabelList()[0]->setPosition(playerOne->getUI()->getLabelList()[0]->getPosition() + cocos2d::Vec2(0, 2));
				//playerOne->getUI()->getUIGunSprite()->setPosition(playerOne->getUI()->getUIGunSprite()->getPosition() + cocos2d::Vec2(0, 2));
				//for(int i = 0; i < playerOne->getUI()->getHPSprites().size();i++)
				//playerOne->getUI()->getHPSprites()[i]->setPosition(playerOne->getUI()->getHPSprites()[i]->getPosition() + cocos2d::Vec2(0, 2));
				//
				//playerTwo->getUI()->getLabelList()[0]->setPosition(playerTwo->getUI()->getLabelList()[0]->getPosition() + cocos2d::Vec2(0, 2));
				//playerTwo->getUI()->getUIGunSprite()->setPosition(playerTwo->getUI()->getUIGunSprite()->getPosition() + cocos2d::Vec2(0, 2));
				//for (int i = 0; i < playerTwo->getUI()->getHPSprites().size(); i++)
				//	playerTwo->getUI()->getHPSprites()[i]->setPosition(playerTwo->getUI()->getHPSprites()[i]->getPosition() + cocos2d::Vec2(0, 2));

				playerOne->getUI()->updatePosition(cocos2d::Vec2(0, CAMERASPEED));
				playerTwo->getUI()->updatePosition(cocos2d::Vec2(0, CAMERASPEED));


				this->getDefaultCamera()->setPosition(cocos2d::Vec2(this->getDefaultCamera()->getPosition().x,
					this->getDefaultCamera()->getPosition().y + CAMERASPEED));
				DDOS->getSprite()->setPosition(cocos2d::Vec2(100, (DDOS->getSprite()->getPosition().y + CAMERASPEED)));

			}
			if (p1Controller->isButtonPressed(Sedna::X)) {
				for (unsigned int i = 0; i < sManager.outlawList.size(); i++)
					sManager.outlawList[i]->getBox()->getDrawNode()->setVisible(true);
				for (unsigned int i = 0; i < sManager.tableList.size(); i++)
					sManager.tableList[i]->getBox()->getDrawNode()->setVisible(true);
				playerOne->getBox()->getDrawNode()->setVisible(true);
				playerTwo->getBox()->getDrawNode()->setVisible(true);

				//shotgunTest->getBox()->getDrawNode()->setVisible(true);
			}
			else {
				for (unsigned int i = 0; i < sManager.outlawList.size(); i++)
					sManager.outlawList[i]->getBox()->getDrawNode()->setVisible(false);
				for (unsigned int i = 0; i < sManager.tableList.size(); i++)
					sManager.tableList[i]->getBox()->getDrawNode()->setVisible(false);
				playerOne->getBox()->getDrawNode()->setVisible(false);
				playerTwo->getBox()->getDrawNode()->setVisible(false);
			}//show hitboxes
#endif


			//shotgunTest->updateGameObject();
			//shotgunTest->shoot(dt,this);
			//shotgunTest->checkList();

			


			for (int i = 0; i < sManager.outlawList.size(); i++) {
				sManager.outlawList[i]->shoot(dt, this);
			}
			bigCheckList();


			if (DDOS->getSprite()->getPosition().y - bg2->getPosition().y >= 588.8f) {
				bg2->setPosition(cocos2d::Vec2(bg2->getPosition().x, bg2->getPosition().y + 588.8f));
			}
			if (DDOS->getSprite()->getPosition().y - bg3->getPosition().y >= 588.8f) {
				bg3->setPosition(cocos2d::Vec2(bg3->getPosition().x, bg3->getPosition().y + 588.8f));
			}

			playerOne->updateGameObject();
			playerTwo->updateGameObject();
			bounceFunc();

			rifleTest->updateGameObject();
			rifleTest->setTrack(playerOne);
			rifleTest->shoot(dt, this);
			rifleTest->checkList();
		}
	}

}

void HelloWorld::initSprites()
{
	cocos2d::experimental::AudioEngine::preload("bgm.mp3");
	///<cocos2d::experimental::AudioEngine::preload("oRsound.mp3");>

	DDOS = new Sedna::GameObject("DOS.jpg", cocos2d::Vec2(100, 300), 1, 1, 1);
	this->addChild(DDOS->getBox()->getDrawNode());
	this->addChild(DDOS->getSprite());
	DDOS->getSprite()->setVisible(true);
	/////////////////////////////////////

	shotgunTest = new Sedna::ShotgunOutlaw(150,260);
	this->addChild(shotgunTest->getBox()->getDrawNode());
	this->addChild(shotgunTest->getSprite(),10);

	rifleTest = new Sedna::RifleOutlaw(150, 260);
	this->addChild(rifleTest->getBox()->getDrawNode());
	this->addChild(rifleTest->getSprite(), 10);


	olReliable = new Sedna::Gun("olReliable", 2, 4, 0.35f);
	bloodyMary = new Sedna::Gun("bloodyMary", 3, 10, 10, 0.85f);
	theBiggestIron = new Sedna::Gun("theBiggestIron", 1, 10,100, 0.089f);


	playerOne = new Sedna::Player(1, 100, 100, managerR, bloodyMary);
	this->addChild(playerOne->getBox()->getDrawNode());
	this->addChild(playerOne->getSprite(), 10);
	this->addChild(playerOne->getUI()->getUIGunSprite(), 20);
	for (int i = 0; i < playerOne->getUI()->getLabelList().size(); i++) {
		this->addChild(playerOne->getUI()->getLabelList()[i], 20);
	}
	for (int i = 0; i < playerOne->getUI()->getHPSprites().size(); i++)
		this->addChild(playerOne->getUI()->getHPSprites()[i]);


	playerTwo = new Sedna::Player(2, 300, 100, managerR, olReliable);
	this->addChild(playerTwo->getBox()->getDrawNode());
	this->addChild(playerTwo->getSprite(), 10);
	this->addChild(playerTwo->getUI()->getUIGunSprite(), 20);
	for (int i = 0; i < playerTwo->getUI()->getLabelList().size(); i++) {
		this->addChild(playerTwo->getUI()->getLabelList()[i], 20);
	}
	for (int i = 0; i < playerTwo->getUI()->getHPSprites().size(); i++)
		this->addChild(playerTwo->getUI()->getHPSprites()[i]);


	bg = cocos2d::Sprite::create("bg1.png");
	this->addChild(bg, -1000);
	bg->setScale(0.85f, 0.92f);
	bg->setAnchorPoint(cocos2d::Vec2(0, 0));
	bg->setPosition(0, 0);



	bg2 = cocos2d::Sprite::create("bgPlain.png");
	this->addChild(bg2, -1000);
	bg2->setScale(0.85f, 0.92f);
	bg2->setAnchorPoint(cocos2d::Vec2(0, 0));
	bg2->setPosition(cocos2d::Vec2(0, bg->getContentSize().height * 0.92f));

	bg3 = cocos2d::Sprite::create("test.png");
	this->addChild(bg3, -1000);
	bg3->setScale(0.85f, 0.92f);
	bg3->setAnchorPoint(cocos2d::Vec2(0, 0));
	bg3->setPosition(cocos2d::Vec2(0, (bg2->getContentSize().height * 0.92f) * 2));


	///menu shit

	pausedLabel = Label::create("Paused", "fonts/Montague.ttf", 25);
	pausedLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	pausedLabel->setPosition(Vec2(140, 250));
	pausedLabel->enableShadow();
	this->addChild(pausedLabel, 100);
	pausedLabel->setVisible(false);

	startLabel = Label::create("3", "fonts/Montague.ttf", 125);
	startLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	startLabel->setPosition(Vec2(200, 150));
	startLabel->enableShadow();
	this->addChild(startLabel, 100);
	startLabel->setVisible(false);

	for (int i = 0; i < pauseMenu->getLabelList().size(); i++) {
		this->addChild(pauseMenu->getLabelList()[i], 100);
		pauseMenu->getLabelList()[i]->enableShadow();
		pauseMenu->getLabelList()[i]->setAnchorPoint(cocos2d::Vec2(0, 0));
		if (i == 0)
			pauseMenu->getLabelList()[i]->setPosition(140, 50);
		else {
			pauseMenu->getLabelList()[i]->setPosition(140, pauseMenu->getLabelList()[i - 1]->getPosition().y + 30);

		}
	}

	for (int i = 0; i < pauseMenu->getLabelList().size(); i++) {
		pauseMenu->getLabelList()[i]->setVisible(false);
	}
	pauseMenu->select(1);
}

void HelloWorld::checkInput(float dt)
{
	playerOne->checkInput(dt);
	playerTwo->checkInput(dt);
	if (!paused) {
		playerOne->shoot(dt, this);
		playerTwo->shoot(dt, this);
	}
}

void HelloWorld::getCollisions()
{
	playerOne->checkTableStuff(sManager.tableList);
	playerTwo->checkTableStuff(sManager.tableList);
}

void HelloWorld::bigCheckList()
{
	checkPosAll();
	if (sManager.outlawList.size() > 4) {
		sManager.outlawList.front()->removeProjectiles();
		sManager.outlawList.front()->getBox()->getDrawNode()->removeFromParent();
		sManager.outlawList.front()->getSprite()->removeFromParent();
		sManager.outlawList.erase(sManager.outlawList.begin());
		Sedna::BaseObjectManager::outlawBObjects.erase(Sedna::BaseObjectManager::outlawBObjects.begin());
	}


	recursiveFunction(sManager.outlawList);

	playerOne->checkBCollision(sManager.outlawList);
	playerTwo->checkBCollision(sManager.outlawList);
	playerOne->checkBCollision(sManager.tableList);
	playerTwo->checkBCollision(sManager.tableList);
	playerOne->checkList();
	playerTwo->checkList();
	for (unsigned int i = 0; i < sManager.tableList.size(); i++)
		sManager.tableList[i]->updateGameObject();

	for (unsigned int i = 0; i < sManager.outlawList.size(); i++) {

		sManager.outlawList[i]->checkBCollision(sManager.tableList);
		sManager.outlawList[i]->checkBCollision(playerOne);
		sManager.outlawList[i]->checkBCollision(playerTwo);
		sManager.outlawList[i]->checkList();
		sManager.outlawList[i]->updateGameObject();

	}
	for (unsigned int i = 0; i < sManager.tableList.size(); i++) {
		for (unsigned int j = 0; j < sManager.tableList.size(); j++) {
			if (i == j)
				continue;
			sManager.tableList[i]->collideTable(sManager.tableList[j]);
		}
	}



}

void HelloWorld::recursiveFunction(std::vector<Sedna::Outlaw*>& outlawList)
{
	for (unsigned int i = 0; i < sManager.outlawList.size(); i++) {
		for (unsigned int j = 0; j < sManager.outlawList.size(); j++) {
			if (i == j)
				continue;
			if (sManager.outlawList[i]->getBox()->checkCollision(*sManager.outlawList[j]->getBox())) {
				sManager.outlawList[i]->getBox()->setLocation(cocos2d::Vec2(100 + (rand() % 300),
					sManager.outlawList[i]->getBox()->getLocation().y + 50));
				recursiveFunction(sManager.outlawList);
			}

		}
	}
}
void HelloWorld::recursiveFunction(std::vector<Sedna::Table*>& tableList)
{
	for (unsigned int i = 0; i < tableList.size(); i++) {
		for (unsigned int j = 0; j < tableList.size(); j++) {
			if (i == j)
				continue;
			if (tableList[i]->getBox()->checkCollision(*tableList[j]->getBox())) {
				tableList[i]->getBox()->setLocation(cocos2d::Vec2(rand() % 100 + 1 + (rand() % 200 + 1),
					tableList[i]->getBox()->getLocation().y));
				recursiveFunction(tableList);
			}

		}
	}
}

void HelloWorld::checkPosAll()//this function will remove and objects that go to far below the screen
{
	for (unsigned int i = 0; i < sManager.outlawList.size(); i++)
	{
		if (sManager.outlawList[i]->getBox()->getLocation().y < DDOS->getSprite()->getPosition().y - 400)
		{
			sManager.outlawList[i]->removeProjectiles();
			sManager.outlawList[i]->getBox()->getDrawNode()->removeFromParent();
			sManager.outlawList[i]->getSprite()->removeFromParent();
			sManager.outlawList.erase(sManager.outlawList.begin() + i);
			Sedna::BaseObjectManager::outlawBObjects.erase(Sedna::BaseObjectManager::outlawBObjects.begin() + i);
			i--;
		}
	}
	for (unsigned int i = 0; i < sManager.tableList.size(); i++)
	{
		if (sManager.tableList[i]->getBox()->getLocation().y < DDOS->getSprite()->getPosition().y - 400)
		{
			sManager.tableList[i]->getBox()->getDrawNode()->removeFromParent();
			sManager.tableList[i]->getSprite()->removeFromParent();
			sManager.tableList.erase(sManager.tableList.begin() + i);
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

void HelloWorld::bounceFunc()//this function stops the player from leaving th screen on the left and right
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

	for (unsigned int i = 0; i < sManager.tableList.size(); i++)
	{
		if ((int)sManager.tableList[i]->getBox()->getLocation().x >= barRightMax)
		{
			sManager.tableList[i]->getBox()->setLocation(cocos2d::Vec2(430, sManager.tableList[i]->getBox()->getLocation().y));
			sManager.tableList[i]->getBox()->addForce(-25, 0);
		}

		if ((int)sManager.tableList[i]->getBox()->getLocation().x <= barLeftMax)
		{
			sManager.tableList[i]->getBox()->setLocation(cocos2d::Vec2(90, sManager.tableList[i]->getBox()->getLocation().y));
			sManager.tableList[i]->getBox()->addForce(25, 0);
		}
	}
}




void HelloWorld::togglePause() {//this actually has many applications
	paused ^= 1;
}