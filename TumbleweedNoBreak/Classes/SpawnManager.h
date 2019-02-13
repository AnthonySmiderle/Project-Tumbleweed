#pragma once
#include "cocos2d.h"
namespace Sedna {
	class SpawnManager//TODO
	{
	public:
		SpawnManager(cocos2d::Scene* s) :scene(s) {}
		void update(float dt, int DDOS);
	private:
		float totalTime = 0.0f;
		cocos2d::Scene* scene;
		unsigned int tableMax = 4;
		unsigned int tableTime = 20;
		void tableSpawn();
		float tableCounter=0.0f;
		bool tableSpawned = false;//turn into object for space
		unsigned int outlawMax = 4;
		unsigned int outlawTime = 20;
		void outlawSpawn();
		
		
	};



}