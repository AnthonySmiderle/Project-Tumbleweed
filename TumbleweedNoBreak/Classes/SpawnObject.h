#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>
/*
	The SpawnObject goes hand in hand with the Object Spawner
	When updated the function adds dt to its counter it then checks to see how many objects of that type can possibly exist
	If the spawnTimer has met it's conditions plus the spawnTimerCurrentVariance, it will return an integer based on the amount of this type that should be created
	and will then change the spawnTimerCurrentVariance to a new variable based on the spawnVariance
	The chainType boolean basically signifies that it can return more than 1 for its return statement
	The amount is based off of the spawnVariance variable
	The hasSpawned Variable will then stop it from continually returning new data for it to spawn more
*/
namespace Sedna
{
	class SpawnObject 
	{
	public:
		SpawnObject();
		SpawnObject(float timerMax, float max, float timerDiff = 0.0f, int maxDiff = 0, bool chain = false)//constructor
			:spawnTimerMax(timerMax), maxType(max), spawnVariance(timerDiff), amountVariance(maxDiff),chainType(chain) {}
		int update(float dt,int amount);//update function (yes it returns data)
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