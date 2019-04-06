#pragma once
#include "cocos2d.h"
#include "SpawnObject.h"
#include "Table.h"
#include "Enemy.h"
namespace Sedna {

	/*
	The Spawn Manager handles all spawning of objects and enemies
	It takes a scene pointer and uses that to know where to spawn the enemies
	Every update it takes in two data members, dt and DDOS
	dt is delta time and used for the timers in each object
	DDOS is the y position of the screen since the camera is moving at a rate that is not constant
	Each Object has its own spawn function
	*/
	class SpawnManager
	{
	public:
		SpawnManager(cocos2d::Scene* s) :scene(s) {}
		void update(float dt, int DDOS);
		std::vector <Sedna::Table*> tableList;//lists of how many tables and enemies
		std::vector<Sedna::Outlaw*>outlawList;
	private:
		void tableSpawn(int DDOS);//spawning functions
		void outlawSpawn(int DDOS);
		void shotgunOutlawSpawn(int DDOS);
		void rifleOutlawSpawn(int DDOS);
		void peteSpawn(int DDOS);


		
		float totalTime = 0.0f;//time that has run since the start of the game
		cocos2d::Scene* scene;//the scene pointer
		//spawnObjects
		SpawnObject tables = SpawnObject(3.0f,5,1.0f);
		SpawnObject tableChain = SpawnObject(10.0f,7,51.0f,6,true);
		SpawnObject outlaws = SpawnObject(1.5f,6,2.0f);
		SpawnObject outlawChain = SpawnObject(20.0f,10.0f,10.0f,5,true);
		SpawnObject shotgunOutlaws = SpawnObject(7.0f,4.0f,1.0f);
		SpawnObject rifleOutlaws = SpawnObject(16.0f, 10.0f, 1.0f);
		SpawnObject CrazyPetes = SpawnObject(24.0f, 10.0f, 1.0f);
	};



}