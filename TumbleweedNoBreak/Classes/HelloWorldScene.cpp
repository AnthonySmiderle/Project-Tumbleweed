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


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label


	initSprites();
	//this->addChild(c.getDrawNode(), 100);

	this->addChild(c.getDrawNode(), 1);
	c.getDrawNode()->setVisible(false);


	p1 = managerR.getController(0);

	this->scheduleUpdate();


	return true;
}

void HelloWorld::update(float dt)
{
	managerR.update();
	p1->getSticks(sticks);


	this->getDefaultCamera()->runAction(cocos2d::MoveBy::create(0, cocos2d::Vec2(0, 60 * dt)));

	//std::cout<< p1->getLStickDirection()<<std::endl;
	player->setPosition(c.getLocation());

	c.update();
	checkInput();



}

void HelloWorld::initSprites()
{

	player = Sprite::create("player1.png");
	//player->setPosition(cocos2d::Vec2((s.getStart().x + s.getEnd().x) / 2, (s.getStart().y + s.getEnd().y) / 2));
	player->setPosition(c.getLocation());
	player->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	player->setScale(2.0f);
	this->addChild(player, 1);
	player->setVisible(true);
}

void HelloWorld::checkInput()
{
	////////////////////
	//move right
	if (sticks[0].x > 0.3f)
		c.setForce(cocos2d::Vec2(3.3,0 ));

	//move left
	else if (sticks[0].x < -0.3f) 
		c.setForce(cocos2d::Vec2(-3.3, 0));

	////////////////////

	////////////////////
	//move up
	if (sticks[0].y > 0.3f) 
		c.setForce(cocos2d::Vec2(0, 3));

	//move down
	else if (sticks[0].y < -0.3f) 
		c.setForce(cocos2d::Vec2(0, -3));

	////////////////////


	if (sticks[0].x > -0.3f && sticks[0].x < 0.3f && sticks[0].y > -0.3f && sticks[0].y < 0.3f) {
		c.addForce(cocos2d::Vec2(c.getVelocity().x *-1.0f, c.getVelocity().y*-1.0f));

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
