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
#include "baseObjectManager.h"
#include "XinputManager.h"
#include "Table.h"
#include "Player.h"
#include "Potion.h"
#include "Projectile.h"
#include "Enemy.h"
#include "SpawnManager.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);

	void initSprites();
	void checkInput(float dt);
	void getCollisions();
	void bigCheckList();
	void recursiveFunction(std::vector<Sedna::Outlaw*>& outlawList);
	void recursiveFunction(std::vector<Sedna::Table*>& tableList);
	void checkPosAll();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
private:
	cocos2d::Director* director;

	void bounceFunc();
	Sedna::SpawnManager sManager = Sedna::SpawnManager(this);
	Sedna::XinputManager managerR;
	Sedna::XinputController* p1Controller;
	Sedna::XinputController* p2Controller;
	Sedna::Stick p1Sticks[2];
	Sedna::Stick p2Sticks[2];
	Sedna::Triggers p1Triggers;
	Sedna::Triggers p2Triggers;

	cocos2d::Sprite* a;
	cocos2d::Sprite* b;
	cocos2d::Sprite* rsl;
	cocos2d::Sprite* rsr;
	cocos2d::Sprite* rt;

	

	Sedna::Player* playerOne;
	Sedna::Player* playerTwo;


	//guns
	Sedna::Gun* olReliable;//base gun
	Sedna::Gun* bloodyMary;//shotgun
	Sedna::Gun* theBiggestIron;//gattling gun

	Sedna::Projectile *baseProjectile;
	std::vector<Sedna::Projectile*>pProjectiles;
	Sedna::Projectile* eBaseProjectile;
	std::vector<Sedna::Projectile*>eProjectiles;

	

	Sedna::GameObject* DDOS;
	std::vector <Sedna::Potion> potionList;

	cocos2d::Sprite* bg;
	cocos2d::Sprite* bg2;
	cocos2d::Sprite* bg3;

	int barRightMax = 430;
	int barLeftMax = 90;

	bool TRUEPAUSE = false;
	bool TEMPPAUSE = false;
	bool paused = false;
	void togglePause();
	float pauseTimer = 0.0f;
	float bulletTimeTimer = 0.0f;
	float bulletTimeWait = 0.0f;
	float bulletTimeMiniWait = 0.0f;
	bool bulletTime = false;
	bool bulletTimeAgain = false;
};

#endif // __HELLOWORLD_SCENE_H__
