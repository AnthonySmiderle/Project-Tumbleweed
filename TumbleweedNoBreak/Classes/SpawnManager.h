#pragma once
#include "cocos2d.h"
#include "SpawnObject.h"
namespace Sedna {
	class SpawnManager//TODO
	{
	public:
		SpawnManager(cocos2d::Scene* s) :scene(s) {}
		void update(float dt, int DDOS);
	private:
		float totalTime = 0.0f;
		cocos2d::Scene* scene;
		void tableSpawn();
		void outlawSpawn();
		
		
	};



}