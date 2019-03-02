#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>
namespace Sedna
{
	class SpawnObject 
	{
	public:
		SpawnObject();
		SpawnObject(float timerMax, float max, float timerDiff = 0.0f, int maxDiff = 0) //timer max, max, timer diff, maxdiff
			:spawnTimerMax(timerMax), maxType(max), spawnVariance(timerDiff), amountVariance(maxDiff) {}
		int update(float dt,int amount);
	private:
		bool hasSpawned = true;
		float spawnTimer=0.0f;
		float spawnTimerMax=0.0f;
		float spawnTimerCurrentVariance = 0.0f;
		float spawnVariance = 0.0f;
		unsigned int maxType=0;
		unsigned int amountVariance = 0;
		float counter=0.0f;
		bool chainType = false;
	};



}