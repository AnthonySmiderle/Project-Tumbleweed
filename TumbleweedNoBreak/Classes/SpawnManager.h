#pragma once
#include "cocos2d.h"
#include "SpawnObject.h"
#include "Table.h"
#include "baseObjectManager.h"
namespace Sedna {
	class SpawnManager//TODO
	{
	public:
		SpawnManager(cocos2d::Scene* s) :scene(s) {}
		void update(float dt, int DDOS);
		std::vector <Sedna::Table*> tableList;
	private:
		float totalTime = 0.0f;
		cocos2d::Scene* scene;

		Sedna::Table* baseTable;
		



		void tableSpawn(int DDOS);
		void outlawSpawn(int DDOS);
		

		SpawnObject tables = SpawnObject(5.0f,5,3.0f);
		SpawnObject outlaws = SpawnObject(5.0f,6,2.0f);
	};



}