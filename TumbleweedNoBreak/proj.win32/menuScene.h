#pragma once
#include "cocos2d.h"
class MenuScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);

	CREATE_FUNC(MenuScene);
private:

};