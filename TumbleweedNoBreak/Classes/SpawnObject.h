#pragma once
namespace Sedna
{
	class SpawnObject
	{
	public:
		SpawnObject(float timerMax, float max, float timerDiff = 0.0f, int maxDiff = 0) 
			:spawnTimer(timerMax), maxType(max), spawnVariance(timerDiff), amountVariance(maxDiff) {}
		void update(float dt);
	private:
		bool hasSpawned = false;
		float spawnTimer=0.0f;
		float spawnTimerMax=0.0f;
		float spawnVariance = 0.0f;
		unsigned int amount = 0;
		unsigned int maxType=0;
		unsigned int amountVariance = 0;
		float counter=0.0f;
		bool chainType = false;
	};



}