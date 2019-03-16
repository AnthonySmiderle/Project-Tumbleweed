#pragma once
#include "cocos2d.h"
#include "SpawnObject.h"
#include "Table.h"
#include "baseObjectManager.h"
#include "Enemy.h"
namespace Sedna {


	class SpawnManager
	{
	public:
		SpawnManager(cocos2d::Scene* s) :scene(s) {}
		void update(float dt, int DDOS);
		std::vector <Sedna::Table*> tableList;
		std::vector<Sedna::Outlaw*>outlawList;
	private:
		void tableSpawn(int DDOS);
		void outlawSpawn(int DDOS);
		void shotgunOutlawSpawn(int DDOS);
		void rifleOutlawSpawn(int DDOS);
		void peteSpawn(int DDOS);

		Sedna::Table* baseTable;
		Sedna::Outlaw* outlaw;
		Sedna::ShotgunOutlaw* shotgunOutlaw;
		Sedna::RifleOutlaw* rifleOutlaw;
		Sedna::CrazyPete* pete;

		
		float totalTime = 0.0f;
		cocos2d::Scene* scene;

		SpawnObject tables = SpawnObject(3.0f,5,1.0f);
		SpawnObject tableChain = SpawnObject(10.0f,7,51.0f,6,true);
		SpawnObject outlaws = SpawnObject(1.5f,6,2.0f);
		SpawnObject outlawChain = SpawnObject(20.0f,10.0f,10.0f,5,true);
		SpawnObject shotgunOutlaws = SpawnObject(7.0f,4.0f,1.0f);
		SpawnObject rifleOutlaws = SpawnObject(14.0f, 7.0f, 1.0f);
		SpawnObject CrazyPetes = SpawnObject(20.0f, 10.0f, 1.0f);
		//SpawnObject CrazyPetes = SpawnObject(1, 1, 1.0f);

	};



}