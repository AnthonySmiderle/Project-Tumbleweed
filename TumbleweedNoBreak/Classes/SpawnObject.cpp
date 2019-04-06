#include "SpawnObject.h"

Sedna::SpawnObject::SpawnObject()
{
	//is handled
}

int Sedna::SpawnObject::update(float dt, int amount)
{
	counter += dt;//first add to the counter this is for future implementation
	if (amount<=maxType)//if there are less than than the max allowed
	{
		if (hasSpawned)//if they have spawned recently
		{
			spawnTimer += dt;//add to the timer
			spawnTimerCurrentVariance = spawnVariance * ((rand() % 3));//get some variance
			if (spawnTimer >= spawnTimerMax + spawnTimerCurrentVariance)	//if the amount of timer with some variance has passes
			{
				hasSpawned = false;//it has not spawned recently
				spawnTimer = 0.0f;//reset the timer
			}
		}
		if (!spawnTimer)//if the timer is 0
		{
			if (chainType)//if it can spawn multiple at once
			{
				int temp = 1 + amountVariance - (rand() % amountVariance);//get an amount for variance
				amount += temp;//add to the amount
				hasSpawned = true;//it has spawned
				return temp;//return the amount wanting to spawn
			}
			else
			{
				hasSpawned = true;//same for singles but return 1
				amount++;
				return 1;
			}
		}
	}
	return 0;
}
