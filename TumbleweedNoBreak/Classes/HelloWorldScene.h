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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "XinputManager.h"
#include "Table.h"
#include "Player.h"
#include "Potion.h"
#include "Projectile.h"
#include "Enemy.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);

	void initSprites();
	void checkInput(float dt);
	void getCollisions();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
private:
	//std::vector<Sedna::SquarePrimitive> bullets;
	Sedna::XinputManager managerR;
	Sedna::XinputController* p1Controller;
	Sedna::Stick sticks[2];

	Sedna::Triggers p1Triggers;

	Sedna::Table* baseTable;


	Sedna::Player* playerOne;

	Sedna::Projectile *playerProjectile;
	std::vector<Sedna::Projectile*>pProjectileList;

	Sedna::Outlaw* outlaw;
	std::vector<Sedna::Outlaw*>outlawList;

	Sedna::CirclePrimitive tableC{ cocos2d::Vec2(200,200),10,5,20 };
	cocos2d::Sprite* tableSprite;
	std::vector <Sedna::Table> tableList;
	std::vector <Sedna::Potion> potionList;
	float tumbleTimer = 0.0f;
	bool isTumbling = false;
	float gunTimer = 0.0f;
	bool hasShot = false;
	bool paused = false;
	void togglePause();
	cocos2d::Menu* pauseMenu;
	void initPauseMenu();	
};

#endif // __HELLOWORLD_SCENE_H__
