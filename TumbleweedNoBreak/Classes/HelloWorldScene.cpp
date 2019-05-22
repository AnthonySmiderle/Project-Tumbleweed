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
#include <fstream>

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



	//create the pausemenu
	auto localL1 = cocos2d::Label::create("Exit to Main Menu", "fonts/Montague.ttf", 25);
	auto localL2 = cocos2d::Label::create("Resume", "fonts/Montague.ttf", 25);
	pauseMenu = new Sedna::SednaMenu(2, localL1, localL2);

	//initialize xinpu stuff
	p1Controller = managerR.getController(0);
	p2Controller = managerR.getController(1);

	managerR.update();

	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);
	p2Controller->updateSticks(p2Sticks);
	p2Controller->getTriggers(p2Triggers);


	//make sure no tutorial functions happen before the cutscene
	tutFunc1 = false;
	tutFunc2 = false;
	tutFunc3 = false;
	tutFunc4 = false;

	tutCutscene = true;

	initSprites();

	director = cocos2d::Director::getInstance();
	end = false;


	this->scheduleUpdate();

	return true;
}
void HelloWorld::initSprites()
{
	//preload all the sounds
	cocos2d::experimental::AudioEngine::preload("bgm.mp3");
	cocos2d::experimental::AudioEngine::preload("bgm2.mp3");
	cocos2d::experimental::AudioEngine::preload("bgmWin.mp3");
	cocos2d::experimental::AudioEngine::preload("cha ching.mp3");
	cocos2d::experimental::AudioEngine::preload("gattling.mp3");
	cocos2d::experimental::AudioEngine::preload("outlawNormal.mp3");
	cocos2d::experimental::AudioEngine::preload("outlawShotgun.mp3");
	cocos2d::experimental::AudioEngine::preload("outlawRifle.mp3");
	cocos2d::experimental::AudioEngine::preload("p1Hurt.mp3");
	cocos2d::experimental::AudioEngine::preload("p1Hur2.mp3");
	cocos2d::experimental::AudioEngine::preload("p1Hurt3.mp3");
	cocos2d::experimental::AudioEngine::preload("p2Hurt.mp3");
	cocos2d::experimental::AudioEngine::preload("p2Hurt2.mp3");
	cocos2d::experimental::AudioEngine::preload("p2Hurt3.mp3");
	cocos2d::experimental::AudioEngine::preload("p2Hurt3.mp3");
	cocos2d::experimental::AudioEngine::preload("p2Hurt3.mp3");
	cocos2d::experimental::AudioEngine::preload("pickupMini.mp3");
	cocos2d::experimental::AudioEngine::preload("pickupPotion.mp3");
	cocos2d::experimental::AudioEngine::preload("pickupShot.mp3");
	cocos2d::experimental::AudioEngine::preload("revolver.mp3");
	cocos2d::experimental::AudioEngine::preload("revolver.mp3");
	cocos2d::experimental::AudioEngine::preload("shotgun.mp3");
	cocos2d::experimental::AudioEngine::preload("goldmanMad.mp3");

	///<all of the following lines are just initializations. we will comment on specifically important / outlying code>

	DDOS = new Sedna::GameObject("a.png", cocos2d::Vec2(100, 300), 1, 1, 1);
	this->addChild(DDOS->getBox()->getDrawNode());
	this->addChild(DDOS->getSprite());
	DDOS->getSprite()->setVisible(true);


	btLabel = cocos2d::Label::create("Bullet Time", "fonts/Montague.ttf", 8);
	btLabel->setPosition(cocos2d::Vec2(230, DDOS->getSprite()->getPosition().y - 15));
	this->addChild(btLabel, 101);
	btMeter = Sedna::SquarePrimitive(cocos2d::Vec2(190, DDOS->getSprite()->getPosition().y - 20), cocos2d::Vec2(280, DDOS->getSprite()->getPosition().y - 10));
	this->addChild(btMeter.getDrawNode(), 100);

	//labels for the scoreboard
	score.highScoreLabel = cocos2d::Label::create("Highscore", "fonts/Montague.ttf", 15);
	score.highScoreLabel->setPosition(cocos2d::Vec2(100, DDOS->getSprite()->getPosition().y - 100));
	score.highScoreLabel->setVisible(false);
	this->addChild(score.highScoreLabel, 10000);

	score.highScoreNameLabel = cocos2d::Label::create("", "fonts/Montague.ttf", 30);
	score.highScoreNameLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	score.highScoreNameLabel->setPosition(cocos2d::Vec2(100, DDOS->getSprite()->getPosition().y - 100));
	score.highScoreNameLabel->setVisible(false);
	this->addChild(score.highScoreNameLabel);



	//powerups
	bloodyMaryP_up = new Sedna::Powerup("gun2.png", Sedna::Guns::bloodyMary, Sedna::Guns::bloodyMary2, -1000, 0);
	theBiggestIronP_up = new Sedna::Powerup("gun3.png", Sedna::Guns::theBiggestIron, Sedna::Guns::theBiggestIron2, -1000, 0);

	this->addChild(bloodyMaryP_up->getBox()->getDrawNode());
	this->addChild(bloodyMaryP_up->getSprite());
	this->addChild(theBiggestIronP_up->getBox()->getDrawNode());
	this->addChild(theBiggestIronP_up->getSprite());


	playerOne = new Sedna::Player(1, 300, 150, managerR, Sedna::Guns::olReliable);
	this->addChild(playerOne->getBox()->getDrawNode());
	this->addChild(playerOne->getSprite(), 10);
	this->addChild(playerOne->getUI()->getUIGunSprite(), 20);

	for (unsigned int i = 0; i < playerOne->getUI()->getLabelList().size(); i++)
		this->addChild(playerOne->getUI()->getLabelList()[i], 20);

	for (unsigned int i = 0; i < playerOne->getUI()->getHPSprites().size(); i++)
		this->addChild(playerOne->getUI()->getHPSprites()[i]);


	playerTwo = new Sedna::Player(2, 300, 100, managerR, Sedna::Guns::olReliable2);
	this->addChild(playerTwo->getBox()->getDrawNode());
	this->addChild(playerTwo->getSprite(), 10);
	this->addChild(playerTwo->getUI()->getUIGunSprite(), 19);

	for (unsigned int i = 0; i < playerTwo->getUI()->getLabelList().size(); i++)
		this->addChild(playerTwo->getUI()->getLabelList()[i], 20);

	for (unsigned int i = 0; i < playerTwo->getUI()->getHPSprites().size(); i++)
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

	bg3 = cocos2d::Sprite::create("bgPlain.png");
	this->addChild(bg3, -1000);
	bg3->setScale(0.85f, 0.92f);
	bg3->setAnchorPoint(cocos2d::Vec2(0, 0));
	bg3->setPosition(cocos2d::Vec2(0, (bg2->getContentSize().height * 0.92f) * 2));

	score.flashingScore1 = cocos2d::Sprite::create("ScoreArrow.png");
	score.flashingScore2 = cocos2d::Sprite::create("ScoreArrow1.png");
	score.flashingScore1->setAnchorPoint(Vec2(0.0f, 0.0f));
	score.flashingScore2->setAnchorPoint(Vec2(0.0f, 0.0f));
	score.flashingScore1->setScale(0.7);
	score.flashingScore2->setScale(0.7);
	this->addChild(score.flashingScore1, 100);
	this->addChild(score.flashingScore2, 100);
	score.flashingScore1->setVisible(false);
	score.flashingScore2->setVisible(false);

	stairs = cocos2d::Sprite::create("stairs.png");
	stairs->setScale(0.85f, 0.92f);
	stairs->setAnchorPoint(cocos2d::Vec2(0, 0));
	stairs->setPosition(-1000, 0);

	level2 = cocos2d::Sprite::create("Level 2.png");
	level2->setScale(0.85f, 0.92f);
	level2->setAnchorPoint(cocos2d::Vec2(0, 0));
	level2->setPosition(-1000, 0);

	level2Other = cocos2d::Sprite::create("Other Level 2.png");
	level2Other->setScale(0.85f, 0.92f);
	level2Other->setAnchorPoint(cocos2d::Vec2(0, 0));
	level2Other->setPosition(-1000, 0);

	outsideTransition = cocos2d::Sprite::create("level2Exit.png");
	outsideTransition->setScale(0.85f, 0.92f);
	outsideTransition->setAnchorPoint(cocos2d::Vec2(0, 0));
	outsideTransition->setPosition(-1000, 0);

	level3 = cocos2d::Sprite::create("Level 3.png");
	level3->setScale(0.85f, 0.92f);
	level3->setAnchorPoint(cocos2d::Vec2(0, 0));
	level3->setPosition(-1000, 0);

	level3Other = cocos2d::Sprite::create("Other Level 3.png");
	level3Other->setScale(0.85f, 0.92f);
	level3Other->setAnchorPoint(cocos2d::Vec2(0, 0));
	level3Other->setPosition(-1000, 0);

	this->addChild(stairs);
	this->addChild(level2);
	this->addChild(level2Other);

	this->addChild(outsideTransition);
	this->addChild(level3);
	this->addChild(level3Other);

	///menu 

	pausedLabel = Label::create("Paused", "fonts/Montague.ttf", 25);
	pausedLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	pausedLabel->setPosition(Vec2(140, 250));
	pausedLabel->enableShadow();
	this->addChild(pausedLabel, 100);
	pausedLabel->setVisible(false);

	startLabel = Label::create("3", "fonts/Montague.ttf", 100);
	startLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	startLabel->setPosition(Vec2(200, 150));
	startLabel->enableShadow();
	this->addChild(startLabel, 100);
	startLabel->setVisible(false);



	for (unsigned int i = 0; i < pauseMenu->getLabelList().size(); i++) {
		this->addChild(pauseMenu->getLabelList()[i], 100);
		pauseMenu->getLabelList()[i]->enableShadow();
		pauseMenu->getLabelList()[i]->setAnchorPoint(cocos2d::Vec2(0, 0));
		if (i == 0)
			pauseMenu->getLabelList()[i]->setPosition(140, 50);
		else
			pauseMenu->getLabelList()[i]->setPosition(140, pauseMenu->getLabelList()[i - 1]->getPosition().y + 30);

	}



	for (unsigned int i = 0; i < pauseMenu->getLabelList().size(); i++)
		pauseMenu->getLabelList()[i]->setVisible(false);
	pauseMenu->select(1);



	//tutorial outlaws and tables
	tutOutlaws.push_back(new Sedna::Outlaw(200, DDOS->getSprite()->getPosition().y));
	this->addChild(tutOutlaws.back()->getBox()->getDrawNode());
	this->addChild(tutOutlaws.back()->getSprite());

	for (int i = 0; i < 3; i++) {
		tutTables.push_back(new Sedna::Table(200 + (i * 70), 100));
		this->addChild(tutTables.back()->getBox()->getDrawNode());
		this->addChild(tutTables.back()->getSprite());
	}



	//goldman specific stuff
	dummy = new Sedna::Player(1, 320, 40, managerR, Sedna::Guns::olReliable);
	this->addChild(dummy->getBox()->getDrawNode());
	this->addChild(dummy->getSprite());

	g.push_back(new Sedna::Goldman(250, DDOS->getSprite()->getPosition().y - 60));
	this->addChild(g.back()->getBox()->getDrawNode());
	this->addChild(g.back()->getSprite());
	g.back()->getSprite()->setPosition(cocos2d::Vec2(-1000, 0));
	this->addChild(((Sedna::Goldman*)g.back())->getHealthBar()->getDrawNode(), 100);
	static_cast<Sedna::Goldman*>(g.back())->getHealthBar()->getDrawNode()->setVisible(false);

	dummyTracker = new Sedna::CirclePrimitive(cocos2d::Vec2(0, static_cast<Sedna::Goldman*>(g.back())->getHealthBar()->getP2().y), 5, 20, 50);
	this->addChild(dummyTracker->getDrawNode());
	dummyTracker->getDrawNode()->setVisible(false);

	bossTimeLabel = cocos2d::Label::create(std::to_string(bossTimeMax), "fonts/Montague.ttf", 20);
	bossTimeLabel->setPosition(cocos2d::Vec2(50, 250));
	bossTimeLabel->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	this->addChild(bossTimeLabel, 1000);
	bossTimeLabel->setVisible(false);

	aButton = Sprite::create("a1.png");
	aButton->setScale(0.6);
	aButtonLabel = Label::create(": Select", "fonts/Montague.ttf", 12);
	aButtonLabel->setAnchorPoint(Vec2(0, 0));
	aButton->setAnchorPoint(Vec2(0, 0));
	aButton->setZOrder(1000);
	aButtonLabel->setZOrder(1000);
	aButton->setPosition(10, 150);
	aButtonLabel->setPosition(30, 150);
	aButton->setVisible(true);
	aButtonLabel->setVisible(true);
	this->addChild(aButton);
	this->addChild(aButtonLabel);
	aButton->setVisible(false);
	aButtonLabel->setVisible(false);

	//only make these if the tutorial is true
	if (static_cast<Tutorial*>(this)->tutorial)
		if (tutBool) {

			movementSign = new Sedna::Sign("lsl.png", this, cocos2d::Vec2(-1000, 0), true);

			shootSign = new Sedna::Sign("rt.png", this, cocos2d::Vec2(-1000, 0), true);
			tutorialGun = cocos2d::Sprite::create("tutorialGun.png");
			this->addChild(tutorialGun);
			tutorialGun->setScale(0.5f);
			tutorialGun->setVisible(false);
			tutorialGun->setPosition(shootSign->getDisplayedSprite()->getPosition() + cocos2d::Vec2(30, 0));
			shootSign2 = new Sedna::Sign("rsl.png", this, shootSign->getBox()->getLocation(), true);
			shootSign2->getDisplayedSprite()->setPosition(shootSign2->getDisplayedSprite()->getPosition() + cocos2d::Vec2(0, -30));
			crosshair = cocos2d::Sprite::create("Crosshairs.png");
			this->addChild(crosshair);
			crosshair->setVisible(false);
			crosshair->setPosition(shootSign2->getDisplayedSprite()->getPosition() + cocos2d::Vec2(30, 0));

			btSign = new Sedna::Sign("lt.png", this, cocos2d::Vec2(-1000, 0), true);
			tutorialTime = cocos2d::Sprite::create("tutorialTime.png");
			this->addChild(tutorialTime);
			tutorialTime->setVisible(false);
			tutorialTime->setPosition(btSign->getDisplayedSprite()->getPosition() + cocos2d::Vec2(30, 0));

			tablekickSign = new Sedna::Sign("a1.png", this, cocos2d::Vec2(-1000, 0), true);
			tutorialBoot = cocos2d::Sprite::create("Boot.png");
			this->addChild(tutorialBoot);
			tutorialBoot->setVisible(false);
			tutorialBoot->setPosition(tablekickSign->getDisplayedSprite()->getPosition() + cocos2d::Vec2(30, 0));

			invinceSign = new Sedna::Sign("Invincibility Drink!", this, cocos2d::Vec2(-1000, 0));
			reviveSign = new Sedna::Sign("Revive your friend Drink!", this, cocos2d::Vec2(-1000, 0));
			healSign = new Sedna::Sign("Healing Drink!", this, cocos2d::Vec2(-1000, 0));

			tutorialLabel2 = cocos2d::Label::create("Tutorial\nTry everything out then\nPress X to play the game!", "fonts/Montague.ttf", 12);
			tutorialLabel2->setPosition(cocos2d::Vec2(400, 270));
			this->addChild(tutorialLabel2, 1000);
			tutorialLabel2->setVisible(false);

			tutorialLabel = cocos2d::Label::create("Tutorial", "fonts/Montague.ttf", 30);
			tutorialLabel->setPosition(cocos2d::Vec2(400, 280));
			this->addChild(tutorialLabel, 1000);

			tutorialKickedLabel = cocos2d::Label::create("Kicked", "fonts/Montague.ttf", 12);
			tutorialKickedLabel->setPosition(cocos2d::Vec2(400, 240));
			this->addChild(tutorialKickedLabel, 1000);
			tutorialKickedLabel->setTextColor(cocos2d::Color4B::RED);

			tutorialMovedLabel = cocos2d::Label::create("Moved", "fonts/Montague.ttf", 12);
			tutorialMovedLabel->setPosition(cocos2d::Vec2(400, 230));
			this->addChild(tutorialMovedLabel, 1000);
			tutorialMovedLabel->setTextColor(cocos2d::Color4B::RED);

			tutorialBulletLabel = cocos2d::Label::create("Bullet Time", "fonts/Montague.ttf", 12);
			tutorialBulletLabel->setPosition(cocos2d::Vec2(400, 220));
			this->addChild(tutorialBulletLabel, 1000);
			tutorialBulletLabel->setTextColor(cocos2d::Color4B::RED);

			tutorialShootLabel = cocos2d::Label::create("Has Shot", "fonts/Montague.ttf", 12);
			tutorialShootLabel->setPosition(cocos2d::Vec2(400, 210));
			this->addChild(tutorialShootLabel, 1000);
			tutorialShootLabel->setTextColor(cocos2d::Color4B::RED);

			tutorialKickedLabel->setVisible(false);
			tutorialShootLabel->setVisible(false);
			tutorialBulletLabel->setVisible(false);
			tutorialMovedLabel->setVisible(false);

			tutorialKickedLabel2 = cocos2d::Label::create("Kicked", "fonts/Montague.ttf", 12);
			tutorialKickedLabel2->setPosition(cocos2d::Vec2(50, 240));
			this->addChild(tutorialKickedLabel2, 1000);
			tutorialKickedLabel2->setTextColor(cocos2d::Color4B::RED);

			tutorialMovedLabel2 = cocos2d::Label::create("Moved", "fonts/Montague.ttf", 12);
			tutorialMovedLabel2->setPosition(cocos2d::Vec2(50, 230));
			this->addChild(tutorialMovedLabel2, 1000);
			tutorialMovedLabel2->setTextColor(cocos2d::Color4B::RED);

			tutorialBulletLabel2 = cocos2d::Label::create("Bullet Time", "fonts/Montague.ttf", 12);
			tutorialBulletLabel2->setPosition(cocos2d::Vec2(50, 220));
			this->addChild(tutorialBulletLabel2, 1000);
			tutorialBulletLabel2->setTextColor(cocos2d::Color4B::RED);

			tutorialShootLabel2 = cocos2d::Label::create("Has Shot", "fonts/Montague.ttf", 12);
			tutorialShootLabel2->setPosition(cocos2d::Vec2(50, 210));
			this->addChild(tutorialShootLabel2, 1000);
			tutorialShootLabel2->setTextColor(cocos2d::Color4B::RED);

			tutorialKickedLabel2->setVisible(false);
			tutorialShootLabel2->setVisible(false);
			tutorialBulletLabel2->setVisible(false);
			tutorialMovedLabel2->setVisible(false);


			noControl = cocos2d::Sprite::create("nope.png");
			noControl->setPosition(cocos2d::Vec2(400, 210));
			noControl->setScale(2);
			this->addChild(noControl, 1000);
		}




}

void HelloWorld::update(float dt)
{
	if (!end) {
		if (bulletTime)
			dt *= 0.5f;
		//update all the xinput stuff
		managerR.update();
		p1Controller->updateSticks(p1Sticks);
		p1Controller->getTriggers(p1Triggers);
		p2Controller->updateSticks(p2Sticks);
		p2Controller->getTriggers(p2Triggers);

		//switch back to the base gun if you're out of ammo
		if (playerOne->getCurrentGun()->getAmmo() <= 0)
			playerOne->setCurrentGun(Sedna::Guns::olReliable);
		if (playerTwo->getCurrentGun()->getAmmo() <= 0)
			playerTwo->setCurrentGun(Sedna::Guns::olReliable2);



		if (this->tutorial)
			this->gameTutorial(dt);
		else {
			if (!paused) {
				bossTimer += dt;
				bossTimeMax -= dt;
			}
			if (bossTimeMax <= 0)
				bossTimeLabel->setVisible(false);
			else
				bossTimeLabel->setVisible(true);

			if (bossTimeMax <= 10)
				bossTimeLabel->setString(std::to_string(bossTimeMax));
			else
				bossTimeLabel->setString(std::to_string((int)bossTimeMax));

			if (bossTimer >= 120)
				bossTime = true;
			this->pause(dt);
			this->play(dt);
		}



	}

}

void HelloWorld::useBulletTime(float dt)
{

	if ((p1Triggers.LT > 0.0f || p2Triggers.LT > 0.0f) && bulletTimeMax < 3.0f)//triggers can be replaced by a power up boolean for a drink instead of a toggle thing
		bulletTime = true;

	if (bulletTime)
	{
		playerOne->usedBt = true;
		playerTwo->usedBt = true;
		//pause and unpause REALLY fast (this instance is just toggling pause)
		paused ^= 1;

		//decrease the hitbox size of the players
		playerOne->getBox()->setRadius(15);	///
		playerTwo->getBox()->setRadius(15);	///
		bulletTimeMax += dt;
	}
	if (p1Triggers.LT == 0 && p2Triggers.LT == 0 || bulletTimeMax >= 3.0f)
	{
		bulletTime = false;
		paused = false;
		bulletTimeMax -= dt;

		playerOne->getBox()->setRadius(20);	 ///
		playerTwo->getBox()->setRadius(20);	 ///
	}
	if (bulletTimeMax < 0.0f)
		bulletTimeMax = 0;

}
void HelloWorld::gameTutorial(float dt)
{
	//set the length of the bullet time meter
	btMeter.setP2x(280 - (bulletTimeMax * 30));

	btMeter.update();

	useBulletTime(dt);
	if (!paused) {

		if (!tutCutscene) {
			//if both players have completed the tutorial
			if (playerOne->getController()->isButtonPressed(Sedna::X) &&
				playerOne->hasMoved() && playerOne->usedShot() && playerOne->usedBt && playerOne->pressedA() &&
				playerTwo->hasMoved() && playerTwo->usedShot() && playerTwo->usedBt && playerTwo->pressedA())
			{

				//move all of the stuff out of the way
				tutFunc4 = true;
				for (auto x : tutTables)
					x->getBox()->setLocation(cocos2d::Vec2(-1000, 0));
				for (auto x : tutOutlaws)
					x->getBox()->setLocation(cocos2d::Vec2(-1000, 0));

				movementSign->getBox()->setLocation(cocos2d::Vec2(-1300, 150));
				shootSign->getBox()->setLocation(cocos2d::Vec2(-1340, 190));
				shootSign2->getBox()->setLocation(cocos2d::Vec2(-1340, 190));
				btSign->getBox()->setLocation(cocos2d::Vec2(-1360, 80));
				tablekickSign->getBox()->setLocation(cocos2d::Vec2(-1195, 270));
				invinceSign->getBox()->setLocation(cocos2d::Vec2(-1195, 185));
				reviveSign->getBox()->setLocation(cocos2d::Vec2(-1195, 113));
				healSign->getBox()->setLocation(cocos2d::Vec2(-1195, 49));

				playerOne->getBox()->setLocation(cocos2d::Vec2(150, 100));
				playerTwo->getBox()->setLocation(cocos2d::Vec2(280, 100));

			}

		}

		//tutorial signs
		movementSign->signUpdate(playerOne);
		movementSign->animate(dt, "lsR.png");
		tablekickSign->signUpdate(playerOne);
		shootSign->signUpdate(playerOne);
		shootSign2->signUpdate(playerOne);
		shootSign2->animate(dt, "rsr.png");
		btSign->signUpdate(playerOne);
		invinceSign->signUpdate(playerOne);
		reviveSign->signUpdate(playerOne);
		healSign->signUpdate(playerOne);

		//sub images that go along with the tutorial signs
		if (shootSign->getDisplayedSprite()->isVisible() && !tutorialGun->isVisible())
			tutorialGun->setVisible(true);
		else if (!shootSign->getDisplayedSprite()->isVisible() && tutorialGun->isVisible())
			tutorialGun->setVisible(false);


		if (tablekickSign->getDisplayedSprite()->isVisible() && !tutorialBoot->isVisible())
			tutorialBoot->setVisible(true);
		else if (!tablekickSign->getDisplayedSprite()->isVisible() && tutorialBoot->isVisible())
			tutorialBoot->setVisible(false);


		if (btSign->getDisplayedSprite()->isVisible() && !tutorialTime->isVisible())
			tutorialTime->setVisible(true);
		else if (!btSign->getDisplayedSprite()->isVisible() && tutorialTime->isVisible())
			tutorialTime->setVisible(false);


		if (shootSign->getDisplayedSprite()->isVisible() && !crosshair->isVisible())
			crosshair->setVisible(true);
		else if (!shootSign->getDisplayedSprite()->isVisible() && crosshair->isVisible())
			crosshair->setVisible(false);


		//if the cutscene should play
		if (tutCutscene) {
			//this is the dummy player. it is here to showcase a mechanic in our game
			if (dummy->getBox()->getLocation().x == 320)
				dummy->getBox()->setForce(cocos2d::Vec2(1, 0));
			else if (dummy->getBox()->getLocation().x == 380)
				dummy->getBox()->setForce(cocos2d::Vec2(-1, 0));
			bounds();

			dummy->updateGameObject();

			//play the next part of the cutscene
			if (tutTables.size() == 2 && !tutFunc1) {
				tutOutlaws.push_back(new Sedna::ShotgunOutlaw(250, DDOS->getSprite()->getPosition().y));
				this->addChild(tutOutlaws.back()->getBox()->getDrawNode());
				this->addChild(tutOutlaws.back()->getSprite());
				tutFunc1 = true;
			}


			//play the next part of the cutscene
			else if (tutTables.size() == 1 && !tutFunc2) {
				tutOutlaws.push_back(new Sedna::RifleOutlaw(350, DDOS->getSprite()->getPosition().y));
				this->addChild(tutOutlaws.back()->getBox()->getDrawNode());
				this->addChild(tutOutlaws.back()->getSprite());
				tutFunc2 = true;
			}


			//move the most recent outlaw
			if (tutOutlaws.back()->getBox()->getLocation().y > 200)
				tutOutlaws.back()->getBox()->setForce(cocos2d::Vec2(0, -2));
			else
				tutOutlaws.back()->getBox()->setForce(cocos2d::Vec2(0, 0));

			//if all the tables are gone, move on
			if (tutTables.empty()) {
				noControl->removeFromParent();
				tutCutscene = false;
			}
		}




		if (!tutCutscene) {

			tutorialLabel->setVisible(false);
			tutorialLabel2->setVisible(true);
			tutorialKickedLabel->setVisible(true);
			tutorialShootLabel->setVisible(true);
			tutorialBulletLabel->setVisible(true);
			tutorialMovedLabel->setVisible(true);
			tutorialKickedLabel2->setVisible(true);
			tutorialShootLabel2->setVisible(true);
			tutorialBulletLabel2->setVisible(true);
			tutorialMovedLabel2->setVisible(true);

			//clear all the previous stuff
			if (!tutFunc3) {
				dummy->getBox()->getDrawNode()->removeFromParent();
				dummy->getSprite()->removeFromParent();

				for (auto x : tutOutlaws) {
					x->removeProjectiles();
					x->getBox()->getDrawNode()->removeFromParent();
					x->getSprite()->removeFromParent();
				}
				for (auto x : tutTables) {

					x->getBox()->getDrawNode()->removeFromParent();
					x->getSprite()->removeFromParent();
				}

				tutOutlaws.clear();
				tutTables.clear();
				tutFunc3 = true;

				for (int i = 0; i < 4; i++) {
					tutTables.push_back(new Sedna::Table(150, 40 + (70 * i), Sedna::health + i));
					this->addChild(tutTables.back()->getBox()->getDrawNode());
					this->addChild(tutTables.back()->getSprite());
				}
				movementSign->getBox()->setLocation(cocos2d::Vec2(300, 150));
				shootSign->getBox()->setLocation(cocos2d::Vec2(340, 190));
				shootSign2->getBox()->setLocation(cocos2d::Vec2(340, 190));
				btSign->getBox()->setLocation(cocos2d::Vec2(360, 80));
				tablekickSign->getBox()->setLocation(cocos2d::Vec2(195, 270));
				invinceSign->getBox()->setLocation(cocos2d::Vec2(195, 185));
				reviveSign->getBox()->setLocation(cocos2d::Vec2(195, 113));
				healSign->getBox()->setLocation(cocos2d::Vec2(195, 49));


			}
			//make sure the player doesnt go out of bounds
			bounds();

			//signs
			checkInput(dt);
			playerOne->updateInvince(dt);
			playerOne->updateGameObject();
			playerTwo->updateInvince(dt);
			playerTwo->updateGameObject();
			checkPosAll();

			//set the labels to green when the tutorial actions have been completed
			if (playerTwo->pressedA())
				tutorialKickedLabel->setTextColor(cocos2d::Color4B::GREEN);
			if (playerTwo->hasMoved())
				tutorialMovedLabel->setTextColor(cocos2d::Color4B::GREEN);
			if (playerTwo->usedShot())
				tutorialShootLabel->setTextColor(cocos2d::Color4B::GREEN);
			if (playerTwo->usedBt)
				tutorialBulletLabel->setTextColor(cocos2d::Color4B::GREEN);

			if (playerOne->pressedA())
				tutorialKickedLabel2->setTextColor(cocos2d::Color4B::GREEN);
			if (playerOne->hasMoved())
				tutorialMovedLabel2->setTextColor(cocos2d::Color4B::GREEN);
			if (playerOne->usedShot())
				tutorialShootLabel2->setTextColor(cocos2d::Color4B::GREEN);
			if (playerOne->usedBt)
				tutorialBulletLabel2->setTextColor(cocos2d::Color4B::GREEN);


		}
		srand(time(0));

		getCollisions();
		checkManyLists(dt);

		if (tutFunc4) {
			//clear everything and start the game


			static_cast<Tutorial*>(this)->tutorial = false;
			tutorialLabel->removeFromParent();
			tutorialLabel2->removeFromParent();
			tutorialKickedLabel->removeFromParent();
			tutorialShootLabel->removeFromParent();
			tutorialBulletLabel->removeFromParent();
			tutorialMovedLabel->removeFromParent();
			tutorialKickedLabel2->removeFromParent();
			tutorialShootLabel2->removeFromParent();
			tutorialBulletLabel2->removeFromParent();
			tutorialMovedLabel2->removeFromParent();

			playerOne->setScore(0);
			playerTwo->setScore(0);

			playerOne->getUI()->updateList();
			playerTwo->getUI()->updateList();
		}
	}

}
void HelloWorld::play(float dt)
{
	if (!paused)
	{
		btMeter.setP2x(280 - (bulletTimeMax * 30));

		btMeter.update();

		//if the player dies
		if (playerOne->isDead() && playerTwo->isDead())//is this loss
		{
			aButton->setVisible(true);
			aButtonLabel->setVisible(true);
			CAMERASPEED = 0;
			startLabel->setString("You Lose");
			startLabel->setVisible(true);
			startLabel->setPosition(50, startLabel->getPosition().y);

			if (!score.hasWritten)
			{
				score.highScoreNameLabel->setVisible(true);
				score.highScoreNameLabel->setPosition(200, DDOS->getSprite()->getPosition().y - 200);
				score.flashingScore1->setPosition(cocos2d::Vec2(198 + score.currentScoreName * 16, DDOS->getSprite()->getPosition().y - 170));
				score.flashingScore2->setPosition(cocos2d::Vec2(196 + score.currentScoreName * 16, DDOS->getSprite()->getPosition().y - 210));

				//allow the player with the higher score to enter their highscore
				if (playerTwo->getScore() > playerOne->getScore())
					score.getScore(p2Controller, p2Sticks, dt, playerTwo, DDOS->getSprite()->getPosition().y - 200);

				else
					score.getScore(p1Controller, p1Sticks, dt, playerOne, DDOS->getSprite()->getPosition().y - 200);
			}
			else
				loseTimer += dt;

			if (loseTimer >= 3.0f)
			{
				auto mMenu = MenuScene::create();
				cocos2d::experimental::AudioEngine::stopAll();
				end = true;

				director->replaceScene(TransitionFade::create(2.0f, mMenu));
			}

		}
		else
			notDead(dt);

		srand(time(0));
		checkInput(dt);
		getCollisions();


		checkManyLists(dt);


		playerOne->updateGameObject();
		playerTwo->updateGameObject();
		bounds();

		bloodyMaryP_up->pickUp(playerOne);
		bloodyMaryP_up->pickUp(playerTwo);
		theBiggestIronP_up->pickUp(playerOne);
		theBiggestIronP_up->pickUp(playerTwo);

		if (bossTime)
			boss(dt);

	}
}

void HelloWorld::boss(float dt)
{
	if (!g.empty())
		dummyTracker->setLocation(cocos2d::Vec2(dummyTracker->getLocation().x, g.back()->getBox()->getLocation().y - 260));
	if (dummyTracker->getLocation().x <= 0)
		dummyTracker->setForce(cocos2d::Vec2(10, 0));
	else if (dummyTracker->getLocation().x >= 500)
		dummyTracker->setForce(cocos2d::Vec2(-10, 0));
	dummyTracker->update();

	if (!g.empty())
	{
		if (!sManager.outlawList.empty())
		{
			for (unsigned i = 0; i < sManager.outlawList.size(); i++) {
				sManager.outlawList[i]->removeProjectiles();
				sManager.outlawList[i]->getBox()->getDrawNode()->removeFromParent();
				sManager.outlawList[i]->getSprite()->removeFromParent();
				sManager.outlawList.erase(sManager.outlawList.begin() + i);
				i--;
			}
		}
		g.back()->getBox()->setLocation(cocos2d::Vec2(g.back()->getBox()->getLocation().x, DDOS->getSprite()->getPosition().y - 45));
		static_cast<Sedna::Goldman*>(g.back())->getHealthBar()->getDrawNode()->setVisible(true);
		g.back()->updateGameObject();
		g.back()->animate(dt);
		static_cast<Sedna::Goldman*>(g.back())->shoot(dt, this, dummyTracker);
		static_cast<Sedna::Goldman*>(g.back())->checkList();
		g.back()->checkBCollision(playerOne);
		g.back()->checkBCollision(playerTwo);


		playerOne->checkBCollision(g, bloodyMaryP_up, theBiggestIronP_up, this);
		playerTwo->checkBCollision(g, bloodyMaryP_up, theBiggestIronP_up, this);
	}
	if (g.empty()) {
		CAMERASPEED = 0;
		aButton->setVisible(true);
		aButtonLabel->setVisible(true);
		if (!playedWinSound) {
			cocos2d::experimental::AudioEngine::stopAll();
			cocos2d::experimental::AudioEngine::play2d("bgmWin.mp3", true);
		}
		playedWinSound = true;
		startLabel->setString("You Win");
		startLabel->setVisible(true);
		startLabel->setPosition(50, startLabel->getPosition().y);

		if (!score.hasWritten)
		{

			score.highScoreNameLabel->setVisible(true);
			score.highScoreNameLabel->setPosition(200, DDOS->getSprite()->getPosition().y - 200);
			score.flashingScore1->setPosition(cocos2d::Vec2(198 + score.currentScoreName * 16, DDOS->getSprite()->getPosition().y - 170));
			score.flashingScore2->setPosition(cocos2d::Vec2(196 + score.currentScoreName * 16, DDOS->getSprite()->getPosition().y - 210));
			if (playerTwo->getScore() > playerOne->getScore())
			{
				score.getScore(p2Controller, p2Sticks, dt, playerTwo, DDOS->getSprite()->getPosition().y - 200);
			}
			else
			{
				score.getScore(p1Controller, p1Sticks, dt, playerOne, DDOS->getSprite()->getPosition().y - 200);
			}
		}
		else
		{
			loseTimer += dt;
		}
		if (loseTimer >= 8.0f)
		{
			auto mMenu = MenuScene::create();
			cocos2d::experimental::AudioEngine::stopAll();
			end = true;

			director->replaceScene(TransitionFade::create(2.0f, mMenu));
		}
		//WIN STUFF
	}

	bossTime = false;

}


void HelloWorld::pause(float dt)
{
	if (p1Controller->isButtonPressed(Sedna::START) || p2Controller->isButtonPressed(Sedna::START))
	{
		p1Controller->setVibration(0, 0);
		p2Controller->setVibration(0, 0);
		if (!TEMPPAUSE)
		{
			for (unsigned int i = 0; i < pauseMenu->getLabelList().size(); i++) {
				pausedLabel->setVisible(true);
				pauseMenu->getLabelList()[i]->setVisible(true);
			}
			TEMPPAUSE = true;
			TRUEPAUSE ^= 1;
		}
	}


	if (p1Controller->isButtonReleased(Sedna::START) && p2Controller->isButtonReleased(Sedna::START))
		TEMPPAUSE = false;


	if (TRUEPAUSE)
	{

		paused = true;
		for (unsigned int i = 0; i < pauseMenu->getLabelList().size(); i++) {
			pausedLabel->setVisible(true);
			pauseMenu->getLabelList()[i]->setVisible(true);
		}



		if ((p1Sticks[0].y < -0.3f || p2Sticks[0].y < -0.3f) && pauseMenu->getIndexOfSelected() != 0)
			pauseMenu->select(pauseMenu->getIndexOfSelected() - 1);


		if (p1Sticks[0].y > 0.3f || p2Sticks[0].y > 0.3f) {
			if (pauseMenu->getIndexOfSelected() + 1 > pauseMenu->getLabelList().size() - 1) {
			}
			else
				pauseMenu->select(pauseMenu->getIndexOfSelected() + 1);
		}



		if (pauseMenu->getIndexOfSelected() == 1 && (p1Controller->isButtonPressed(Sedna::A) || p2Controller->isButtonPressed(Sedna::A)))
			TRUEPAUSE = false;


		if (pauseMenu->getIndexOfSelected() == 0 && (p1Controller->isButtonPressed(Sedna::A) || p2Controller->isButtonPressed(Sedna::A)) && !end) {
			auto mMenu = MenuScene::create();
			cocos2d::experimental::AudioEngine::stopAll();
			cocos2d::experimental::AudioEngine::play2d("cha ching.mp3", false);
			end = true;
			director->replaceScene(TransitionFade::create(2.0f, mMenu));
		}
	}


	else
		for (unsigned int i = 0; i < pauseMenu->getLabelList().size(); i++) {
			pausedLabel->setVisible(false);
			pauseMenu->getLabelList()[i]->setVisible(false);
		}




	if (!TRUEPAUSE)
	{
		useBulletTime(dt);

		if (gameStart < 5)
		{
			gameStart += dt;
			paused = true;
			startLabel->setVisible(true);

			if (gameStart > 1 && gameStart < 2)
			{
				startLabel->setString("3");
				if (!playMusic) {
					if (static_cast<Tutorial*>(this)->music)
						cocos2d::experimental::AudioEngine::play2d("bgm.mp3", true);
					playMusic = true;
				}
			}

			else if (gameStart > 2 && gameStart < 3)
				startLabel->setString("2");

			else if (gameStart > 3 && gameStart < 4)
				startLabel->setString("1");

			else if (gameStart > 4 && gameStart < 5)
				startLabel->setString("0");

			else if (!playerOne->isDead() && !playerTwo->isDead())
				startLabel->setVisible(false);
		}

	}

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
	if (((Tutorial*)this)->tutorial) {
		playerOne->checkTableStuff(tutTables, playerTwo);
		playerTwo->checkTableStuff(tutTables, playerOne);
	}
	playerOne->checkTableStuff(sManager.tableList, playerTwo);
	playerTwo->checkTableStuff(sManager.tableList, playerOne);
}



void HelloWorld::checkManyLists(float dt)
{
	if (((Tutorial*)this)->tutorial) {

		for (unsigned int i = 0; i < tutOutlaws.size(); i++) {

			tutOutlaws[i]->animate(dt);
			tutOutlaws[i]->checkBCollision(tutTables);
			if (tutOutlaws[i]->points == 300)
				((Sedna::RifleOutlaw*)tutOutlaws[i])->setTrack(dummy);

			tutOutlaws[i]->shoot(dt, this);
			tutOutlaws[i]->checkList();
			tutOutlaws[i]->updateGameObject();

		}
		for (unsigned int i = 0; i < tutTables.size(); i++)
			tutTables[i]->updateGameObject();

		if (!tutCutscene) {
			playerOne->checkList();
			playerTwo->checkList();
		}

	}
	else {
		if (!bossTime) {

			for (unsigned int i = 0; i < sManager.outlawList.size(); i++) {
				auto first = playerOne->getBox()->getLocation() - sManager.outlawList[i]->getBox()->getLocation();
				auto second = playerTwo->getBox()->getLocation() - sManager.outlawList[i]->getBox()->getLocation();

				if (sManager.outlawList[i]->points == 200)
					(static_cast<Sedna::ShotgunOutlaw*>(sManager.outlawList[i]))->onLeftSideOf
					((first.getLengthSq() < second.getLengthSq()) ?
						playerOne : playerTwo);

				if (sManager.outlawList[i]->points == 300)
					(static_cast<Sedna::RifleOutlaw*>(sManager.outlawList[i]))->setTrack
					((first.getLengthSq() < second.getLengthSq()) ?
						playerOne : playerTwo);

				if (sManager.outlawList[i]->points == 1000)
					(static_cast<Sedna::CrazyPete*>(sManager.outlawList[i])->updateDyn(dt, this));
				else
					sManager.outlawList[i]->shoot(dt, this);
			}
		}


		checkPosAll();
		if (!bossTime && sManager.outlawList.size() > 6) {
			sManager.outlawList.front()->removeProjectiles();
			sManager.outlawList.front()->getBox()->getDrawNode()->removeFromParent();
			sManager.outlawList.front()->getSprite()->removeFromParent();
			sManager.outlawList.erase(sManager.outlawList.begin());
		}

		recursiveFunctionKnocked();
		if (!bossTime)
			recursiveFunctionOutlaw();
		recursiveFunctionTable();

		playerOne->checkBCollision(sManager.outlawList, bloodyMaryP_up, theBiggestIronP_up, this);
		playerTwo->checkBCollision(sManager.outlawList, bloodyMaryP_up, theBiggestIronP_up, this);
		playerOne->checkList();
		playerTwo->checkList();
		for (unsigned int i = 0; i < sManager.tableList.size(); i++)
			sManager.tableList[i]->updateGameObject();
		if (!bossTime)
			for (unsigned int i = 0; i < sManager.outlawList.size(); i++) {

				sManager.outlawList[i]->animate(dt);
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

		btMeter.getDrawNode()->setPosition(btMeter.getDrawNode()->getPosition().x, btMeter.getDrawNode()->getPosition().y + CAMERASPEED);
		btLabel->setPosition(btLabel->getPosition().x, btLabel->getPosition().y + CAMERASPEED);
	}
}


void HelloWorld::recursiveFunctionOutlaw()
{
	for (unsigned int i = 0; i < sManager.outlawList.size(); i++) {
		for (unsigned int j = 0; j < sManager.outlawList.size(); j++) {
			if (i == j)
				continue;
			if (sManager.outlawList[i]->getBox()->checkCollision(*sManager.outlawList[j]->getBox())) {
				sManager.outlawList[i]->getBox()->setLocation(
					cocos2d::Vec2(100 + (rand() % 300),
						sManager.outlawList[i]->getBox()->getLocation().y + 50));
				recursiveFunctionOutlaw();
			}

		}
	}
}
void HelloWorld::recursiveFunctionTable()
{
	for (unsigned int i = 0; i < sManager.tableList.size(); i++) {
		if (!sManager.tableList[i]->knocked)
		{
			for (unsigned int j = 0; j < sManager.tableList.size(); j++) {
				if (i == j)
					continue;
				if (sManager.tableList[i]->getBox()->checkCollision(*sManager.tableList[j]->getBox())) {
					sManager.tableList[i]->getBox()->setLocation(
						cocos2d::Vec2(100 + (rand() % 300),
							sManager.tableList[i]->getBox()->getLocation().y + 50));
					recursiveFunctionTable();
				}

			}
		}

	}

}
void HelloWorld::recursiveFunctionKnocked()
{
	for (unsigned int i = 0; i < sManager.tableList.size(); i++) {
		if (sManager.tableList[i]->knocked != true)
		{
			for (unsigned int j = 0; j < sManager.outlawList.size(); j++) {
				if (sManager.tableList[i]->getBox()->checkCollision(*sManager.outlawList[j]->getBox())) {
					sManager.tableList[i]->getBox()->setLocation(
						cocos2d::Vec2(100 + (rand() % 300),
							sManager.tableList[i]->getBox()->getLocation().y + 50));

					recursiveFunctionKnocked();
				}

			}
		}

	}

}

void HelloWorld::checkPosAll()//this function will remove and objects that go to far below the screen
{
	if (!bossTime)
		for (unsigned int i = 0; i < sManager.outlawList.size(); i++)
		{
			if (sManager.outlawList[i]->getBox()->getLocation().y < DDOS->getSprite()->getPosition().y - 400)
			{
				sManager.outlawList[i]->removeProjectiles();
				sManager.outlawList[i]->getBox()->getDrawNode()->removeFromParent();
				sManager.outlawList[i]->getSprite()->removeFromParent();
				sManager.outlawList.erase(sManager.outlawList.begin() + i);
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
			i--;
		}
	}
	if (!((Tutorial*)this)->tutorial) {

		checkUnderScreen(playerOne);
		checkUnderScreen(playerTwo);
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
void HelloWorld::performBounce(Sedna::Player* p) {
	if ((int)p->getBox()->getLocation().x >= barRightMax)
	{
		p->getBox()->setLocation(cocos2d::Vec2(430, p->getBox()->getLocation().y));
		p->getBox()->addForce(-25, 0);
	}

	if ((int)p->getBox()->getLocation().x <= barLeftMax)
	{
		p->getBox()->setLocation(cocos2d::Vec2(90, p->getBox()->getLocation().y));
		p->getBox()->addForce(25, 0);
	}
	if (p->getBox()->getLocation().y >= DDOS->getSprite()->getPosition().y) {
		p->getBox()->setLocation(cocos2d::Vec2(p->getBox()->getLocation().x, DDOS->getSprite()->getPosition().y));
		p->getBox()->addForce(0, -25);
	}
	if (static_cast<Tutorial*>(this)->tutorial) {
		if (p->getBox()->getLocation().y <= 30) {
			p->getBox()->setLocation(cocos2d::Vec2(p->getBox()->getLocation().x, 30));
			p->getBox()->addForce(0, 25);
		}
	}


}
void HelloWorld::notDead(float dt)
{

	//update all the player stuff
	playerOne->updateInvince(dt);
	playerTwo->updateInvince(dt);
	bloodyMaryP_up->updateGameObject();
	theBiggestIronP_up->updateGameObject();

	if (!bossTime)
		CAMERASPEED += 0.005 * dt;
	else {
		if (CAMERASPEED <= -2)
			CAMERASPEED = -2;
		else
			CAMERASPEED += -0.5 * dt;
	}
	sManager.update(dt, DDOS->getSprite()->getPosition().y);

	if (moveScreen)
	{
		///<basically set all the below variable's positions to their previous position plus the camera speed>

		bossTimeLabel->setPosition(bossTimeLabel->getPosition() + cocos2d::Vec2(0, CAMERASPEED));

		aButton->setPosition(aButton->getPosition() + cocos2d::Vec2(0, CAMERASPEED));
		aButtonLabel->setPosition(aButtonLabel->getPosition() + cocos2d::Vec2(0, CAMERASPEED));

		for (unsigned int i = 0; i < pauseMenu->getLabelList().size(); i++) {
			pauseMenu->getLabelList()[i]->setPosition(cocos2d::Vec2(pauseMenu->getLabelList()[i]->getPosition().x,
				pauseMenu->getLabelList()[i]->getPosition().y + CAMERASPEED));
		}


		pausedLabel->setPosition(pausedLabel->getPosition() + cocos2d::Vec2(0, CAMERASPEED));
		startLabel->setPosition(startLabel->getPosition() + cocos2d::Vec2(0, CAMERASPEED));


		playerOne->getUI()->updatePosition(cocos2d::Vec2(0, CAMERASPEED));
		playerTwo->getUI()->updatePosition(cocos2d::Vec2(0, CAMERASPEED));


		this->getDefaultCamera()->setPosition(cocos2d::Vec2(this->getDefaultCamera()->getPosition().x,
			this->getDefaultCamera()->getPosition().y + CAMERASPEED));
		DDOS->getSprite()->setPosition(cocos2d::Vec2(100, (DDOS->getSprite()->getPosition().y + CAMERASPEED)));


		if (CAMERASPEED > 0) {

			//background switching code
			if (DDOS->getSprite()->getPosition().y - bg2->getPosition().y >= 598.8f) {

				//this code switches the background sprite based on what the in game time is and where the image is on the screen
				if (bossTimeMax <= 61 && bossTimeMax > 58 && bg2->getTexture() != stairs->getTexture())
					bg2->setTexture(stairs->getTexture());///

				if (bossTimeMax <= 56 && bossTimeMax > 52 && bg2->getTexture() != level2Other->getTexture())
					bg2->setTexture(level2Other->getTexture());///

				if (bossTimeMax <= 33 && bossTimeMax > 28 && bg2->getTexture() != outsideTransition->getTexture())
					bg2->setTexture(outsideTransition->getTexture());

				if (bossTimeMax <= 26 && bossTimeMax > 24 && bg2->getTexture() != level3Other->getTexture())
					bg2->setTexture(level3Other->getTexture());



				bg2->setPosition(cocos2d::Vec2(bg2->getPosition().x, bg2->getPosition().y + 588.8f));
			}


			if (DDOS->getSprite()->getPosition().y - bg3->getPosition().y >= 598.8f) {
				if (bossTimeMax <= 61 && bossTimeMax > 56 && bg3->getTexture() != level2->getTexture())
					bg3->setTexture(level2->getTexture());///

				if (bossTimeMax <= 33 && bossTimeMax > 24 && bg3->getTexture() != level3->getTexture())
					bg3->setTexture(level3->getTexture());

				bg3->setPosition(cocos2d::Vec2(bg3->getPosition().x, bg3->getPosition().y + 588.8f));
			}
		}
		else if (CAMERASPEED < 0) {

			//make the backgrounds scroll backwards
			if (DDOS->getSprite()->getPosition().y - bg2->getPosition().y <= 0.0f)
				bg2->setPosition(cocos2d::Vec2(bg2->getPosition().x, bg2->getPosition().y - 588.8f));

			if (DDOS->getSprite()->getPosition().y - bg3->getPosition().y <= 0.0f)
				bg3->setPosition(cocos2d::Vec2(bg3->getPosition().x, bg3->getPosition().y - 588.8f));
		}

	}
}
void HelloWorld::checkUnderScreen(Sedna::Player* p)
{
	//player dies if they go off screen
	if (p->getBox()->getLocation().y <= DDOS->getSprite()->getPosition().y - 400) {
		p->setHP(0);
		p->die();
		p->getUI()->updateList();
	}
}
void HelloWorld::bounds()//this function stops the player from leaving the screen on the left and right
{

	if (!playerOne->isDead())
		performBounce(playerOne);
	if (!playerTwo->isDead())
		performBounce(playerTwo);



	if (static_cast<Tutorial*>(this)->tutorial) {
		for (unsigned int i = 0; i < tutTables.size(); i++)
		{
			if ((int)tutTables[i]->getBox()->getLocation().x >= barRightMax)
			{
				tutTables[i]->getBox()->setLocation(cocos2d::Vec2(430, tutTables[i]->getBox()->getLocation().y));
				tutTables[i]->getBox()->addForce(-25, 0);
			}

			if ((int)tutTables[i]->getBox()->getLocation().x <= barLeftMax)
			{
				tutTables[i]->getBox()->setLocation(cocos2d::Vec2(90, tutTables[i]->getBox()->getLocation().y));
				tutTables[i]->getBox()->addForce(25, 0);
			}
		}
	}
	else {
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

}

void HelloWorld::togglePause() {//this actually has many applications
	//dpes ot really
	paused ^= 1;
}


