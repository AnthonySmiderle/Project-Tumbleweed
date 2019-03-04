#include "SpawnObject.h"

Sedna::SpawnObject::SpawnObject()
{
	//is handled
}

int Sedna::SpawnObject::update(float dt, int amount)
{
	counter += dt;
	if (amount<=maxType)
	{
		if (hasSpawned)
		{
			spawnTimer += dt;
			spawnTimerCurrentVariance = spawnVariance * ((rand() % 3));
			if (spawnTimer >= spawnTimerMax + spawnTimerCurrentVariance)	
			{
				hasSpawned = false;
				spawnTimer = 0.0f;
			}
		}
		if (!spawnTimer)
		{
			if (chainType)
			{
				int temp = 1 + amountVariance - (rand() % amountVariance);
				amount += temp;
				hasSpawned = true;
				return temp;
			}
			else
			{
				hasSpawned = true;
				amount++;
				return 1;
			}
		}
	}
	return 0;
}
