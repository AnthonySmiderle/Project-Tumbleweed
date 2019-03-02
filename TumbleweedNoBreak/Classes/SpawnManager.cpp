#include "SpawnManager.h"

void Sedna::SpawnManager::update(float dt, int DDOS)
{
	totalTime += dt;
	for (unsigned int i = 0; i < tables.update(dt,tableList.size()); i++)
		tableSpawn(DDOS);
	//for (unsigned int i = 0; i < outlaws.update(dt); i++)
	//	outlawSpawn(DDOS);
}


void Sedna::SpawnManager::tableSpawn(int DDOS)
{
	baseTable = new Sedna::Table(100 + rand() % 300, DDOS - 10 - rand() % 150);
	scene->addChild(baseTable->getBox()->getDrawNode());
	scene->addChild(baseTable->getSprite());
	tableList.push_back(new Sedna::Table(*baseTable));
	Sedna::BaseObjectManager::tableBObjects.push_back(baseTable);
}

void Sedna::SpawnManager::outlawSpawn(int DDOS)
{

}
