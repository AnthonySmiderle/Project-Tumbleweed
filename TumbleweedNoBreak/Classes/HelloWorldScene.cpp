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


	return true;
}

void HelloWorld::update(float dt)
{
	managerR.update();
	p1Controller->updateSticks(sticks);
	p1Controller->getTriggers(p1Triggers);


	checkInput(dt);
	getCollisions();
	if (gunTimer == 5)
	{
		gunTimer = 0;
		isShooting = false;
	}

	this->getDefaultCamera()->setPosition(cocos2d::Vec2(this->getDefaultCamera()->getPosition().x,
		this->getDefaultCamera()->getPosition().y + 1));
	if (!gunTimer)
	{
		isShooting = true;	
	}
		gunTimer += 1;

	//std::cout << p1Triggers.RT<<std::endl;
	if (p1Triggers.RT > 0 && isShooting) {
		//Sedna::Projectile* tempProjectile = new Sedna::Projectile(*playerProjectile);
		//tempProjectile->getBox()->setLocation(playerOne->getBox()->getLocation());
		//tempProjectile->getBox()->addForce(0, 1);
		//tempProjectile->updateGameObject();
		playerProjectile = new Sedna::Projectile(-1000, 0);
		this->addChild(playerProjectile->getBox()->getDrawNode());
		this->addChild(playerProjectile->getSprite());

		projectiles.push_back(new Sedna::Projectile(*playerProjectile));
		
		projectiles.back()->getBox()->setLocation(playerOne->getBox()->getLocation());
		projectiles.back()->getBox()->setForce(cocos2d::Vec2(0,1));
		projectiles.back()->updateGameObject();

	}
	//if(!projectiles.empty())
	//projectiles.back()->updateGameObject();

	for (int i = 0; i < projectiles.size(); i++) {
	
		projectiles[i]->updateGameObject();
	
	}
	std::cout << projectiles.size() << "\n";
	
	playerOne->updateGameObject();
	baseTable->updateGameObject();

}

void HelloWorld::initSprites()
{
	

	playerOne = new Sedna::Player(1,100,100);
	this->addChild(playerOne->getBox()->getDrawNode());
	this->addChild(playerOne->getSprite());
	playerOne->getSprite()->setVisible(true);

	//replace this with a base table that can be copied later
	baseTable = new Sedna::Table(200,200);
	this->addChild(baseTable->getBox()->getDrawNode());
	this->addChild(baseTable->getSprite());
	baseTable->getSprite()->setVisible(true);
}

void HelloWorld::checkInput(float dt)
{
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
		std::cout << tumbleTimer <<std::endl;
		if (tumbleTimer > 5)
		{
			tumbleTimer = 0;
			isTumbling = false;
		}
		
			
		if (!tumbleTimer)
		{
			isTumbling = true;
			playerOne->getBox()->setTumbling(true);
			playerOne->getBox()->addForce(0,1000);
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
