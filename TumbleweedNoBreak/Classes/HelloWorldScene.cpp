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





	initSprites();


	p1Controller = managerR.getController(0);

	this->scheduleUpdate();

	initPauseMenu();
	return true;
}

void HelloWorld::update(float dt)
{
	managerR.update();
	p1Controller->updateSticks(sticks);
	p1Controller->getTriggers(p1Triggers);


	checkInput(dt);
	getCollisions();


	//this->getDefaultCamera()->setPosition(cocos2d::Vec2(this->getDefaultCamera()->getPosition().x,
	//	this->getDefaultCamera()->getPosition().y + 1));
	if (enemyTimer >4.0f)
	{
		enemyTimer = 0.0f;
		hasSpawn = false;
	}
	if (!enemyTimer)
	{
		hasSpawn = true;
		outlaw = new Sedna::Outlaw(-1000, 0);
		this->addChild(outlaw->getBox()->getDrawNode());
		this->addChild(outlaw->getSprite());
		outlawList.push_back(new Sedna::Outlaw(*outlaw));
		outlawList.back()->getBox()->setLocation(cocos2d::Vec2(100, 100));
	}
	if (hasSpawn)
		enemyTimer += dt;
		///srand(time(0));
		///auto x = rand() % 100 + 100 + (rand() % 200 + 200);
		///auto y = 300;
		///outlaw = new Sedna::Outlaw(-1000, 0);
		///this->addChild(outlaw->getBox()->getDrawNode());
		///this->addChild(outlaw->getSprite());
		///outlawList.push_back(new Sedna::Outlaw(*outlaw));
		///outlawList.back()->getBox()->setLocation(cocos2d::Vec2(100, 100));
	if (p1Triggers.RT > 0) {
		
		if (gunTimer > 0.5f)
		{
			gunTimer = 0.0f;
			hasShot = false;
		}
		if (!gunTimer)
		{
			hasShot = true;
			//playerProjectile = new Sedna::Projectile(-1000, 0);
			//this->addChild(playerProjectile->getBox()->getDrawNode());
			//this->addChild(playerProjectile->getSprite());
			if (sticks[1].y < 0.3f && sticks[1].y > -0.3f && sticks[1].x > 0.3f ||
				sticks[1].y < 0.3f && sticks[1].y > -0.3f && sticks[1].x < -0.3f ||
				sticks[1].y < -0.3f) {
			}
			else {

				playerProjectile = new Sedna::Projectile(-1000, 0,Sedna::Ally);
				this->addChild(playerProjectile->getBox()->getDrawNode());
				this->addChild(playerProjectile->getSprite());

				pProjectileList.push_back(new Sedna::Projectile(*playerProjectile));

				pProjectileList.back()->getBox()->setLocation(playerOne->getBox()->getLocation());

				if (sticks[1].x < -0.3f && sticks[1].y > 0.3f)
					pProjectileList.back()->getBox()->setForce(cocos2d::Vec2(-5, 5));
				if (sticks[1].x > 0.3f && sticks[1].y > 0.3f)
					pProjectileList.back()->getBox()->setForce(cocos2d::Vec2(5, 5));
				if (sticks[1].y > 0.3f && sticks[1].x < 0.3f && sticks[1].x > -0.3f ||
					sticks[1].y < 0.3f && sticks[1].y > -0.3f && sticks[1].x < 0.3f && sticks[1].x > -0.3f)
					pProjectileList.back()->getBox()->setForce(cocos2d::Vec2(0, 5));
			}
		}
		

	}
	if (hasShot)
		gunTimer += dt;
	//if(!projectiles.empty())
	//projectiles.back()->updateGameObject();
	if (outlawList.size() > 4) {
		outlawList.erase(outlawList.begin());

	}
	for (int i = 0; i < outlawList.size(); i++) {

		outlawList[i]->updateGameObject(); 

	}

	if (pProjectileList.size() > 4) {
		pProjectileList.erase(pProjectileList.begin());

	}
	for (int i = 0; i < pProjectileList.size(); i++) {

		pProjectileList[i]->updateGameObject();
		
	}
	//std::cout << sticks[1].x<<" "<<sticks[1].y<< "\n";
	

	playerOne->updateGameObject();
	baseTable->updateGameObject();

}

void HelloWorld::initSprites()
{

	

	playerOne = new Sedna::Player(1, 100, 100);
	this->addChild(playerOne->getBox()->getDrawNode());
	this->addChild(playerOne->getSprite());
	playerOne->getSprite()->setVisible(true);

	//replace this with a base table that can be copied later
	baseTable = new Sedna::Table(200, 200);
	this->addChild(baseTable->getBox()->getDrawNode());
	this->addChild(baseTable->getSprite());
	baseTable->getSprite()->setVisible(true);
}

void HelloWorld::checkInput(float dt)
{
	if (p1Controller->isButtonPressed(Sedna::SELECT))
		exit(0);
	if (p1Controller->isButtonPressed(Sedna::START))
		togglePause();
	////////////////////
	//move right
	if (sticks[0].x > 0.3f) {
		playerOne->getBox()->addForce(3, 0);
		//	baseTable->getGameObject().getBox().setForce(cocos2d::Vec2(3.3, 0));
	}
	//move left
	else if (sticks[0].x < -0.3f)
		playerOne->getBox()->addForce(-3, 0);

	////////////////////

	////////////////////
	//move up
	if (sticks[0].y > 0.3f)
		playerOne->getBox()->addForce(0, 3);

	//move down
	else if (sticks[0].y < -0.3f)
		playerOne->getBox()->addForce(0, -3);

	////////////////////

	if (p1Controller->isButtonPressed(Sedna::B)) {
		//std::cout << tumbleTimer <<std::endl;
		if (tumbleTimer > 5)
		{
			tumbleTimer = 0;
			isTumbling = false;
		}


		if (!tumbleTimer)
		{
			isTumbling = true;
			playerOne->getBox()->setTumbling(true);
			playerOne->getBox()->addForce(0, 1000);
		}
	}
	else {
		playerOne->getBox()->setTumbling(false);
	}
	if (sticks[0].x > -0.3f && sticks[0].x < 0.3f && sticks[0].y > -0.3f && sticks[0].y < 0.3f)
		playerOne->getBox()->addForce(playerOne->getBox()->getVelocity().x *-2.0f, playerOne->getBox()->getVelocity().y*-2.0f);


	if (isTumbling)
		tumbleTimer += dt;
}

void HelloWorld::getCollisions()
{
	if (p1Controller->isButtonPressed(Sedna::A) && playerOne->getBox()->checkCollision(*baseTable->getBox())) {

		cocos2d::Vec2 distanceVector((baseTable->getBox()->getLocation().x - playerOne->getBox()->getLocation().x), (baseTable->getBox()->getLocation().y - playerOne->getBox()->getLocation().y));
		baseTable->spriteSwitch();
		//times 2 to give a better feel to kicking the table
		baseTable->getBox()->addForce(distanceVector.x * 2, distanceVector.y * 2);

	}
	//else if (playerOne->getBox()->checkTouching(*baseTable->getBox())) {
	//
	//	playerOne->getBox()->setForce(cocos2d::Vec2(0, 0));
	//
	//}

	else if (baseTable->getBox()->getVelocity() != cocos2d::Vec2(0, 0)) {

		baseTable->getBox()->addForce(
			baseTable->getBox()->getVelocity().x * -1,
			baseTable->getBox()->getVelocity().y * -1);
	}
	if (playerOne->getBox()->checkCloseTouching(*baseTable->getBox())) {
		cocos2d::Vec2 distanceVector((playerOne->getBox()->getLocation().x - baseTable->getBox()->getLocation().x), (playerOne->getBox()->getLocation().y - baseTable->getBox()->getLocation().y));
		playerOne->getBox()->addForce(((distanceVector.x * 2) / 2), (distanceVector.y * 2) / 2);
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
	paused ^=1;

	if (paused) {
		pauseMenu->setVisible(true);
	}
	else {
		pauseMenu->setVisible(false);
	}
}