#include "SpawnManager.h"

void Sedna::SpawnManager::update(float dt, int DDOS)
{
	totalTime += dt;
	DDOS += 25;
	for (unsigned int i = 0; i < tables.update(dt,tableList.size()); i++)
		tableSpawn(DDOS);
	for (unsigned int i = 0; i < outlaws.update(dt,outlawList.size()); i++)
		outlawSpawn(DDOS);
	int outlawChainMax = outlawChain.update(dt, outlawList.size());
	for (unsigned int i = 0; i < outlawChainMax; i++)
		outlawSpawn(DDOS);
	for (unsigned int i = 0; i < shotgunOutlaw.update(dt, shotgunOutlawList.size()); i++)
		shotgunOutlawSpawn(DDOS);
}


void Sedna::SpawnManager::tableSpawn(int DDOS)
{
	baseTable = new Sedna::Table(100 + rand() % 300, DDOS);
	scene->addChild(baseTable->getBox()->getDrawNode());
	scene->addChild(baseTable->getSprite());
	tableList.push_back(new Sedna::Table(*baseTable));
	Sedna::BaseObjectManager::tableBObjects.push_back(baseTable);
}

void Sedna::SpawnManager::outlawSpawn(int DDOS)
{
	int x = 100 + (rand() % 300);
	outlaw = new Sedna::Outlaw(x, DDOS);
	Sedna::BaseObjectManager::outlawBObjects.push_back(outlaw);
	scene->addChild(outlaw->getBox()->getDrawNode());
	scene->addChild(outlaw->getSprite());
	outlawList.push_back(new Sedna::Outlaw(*outlaw));
}

void Sedna::SpawnManager::shotgunOutlawSpawn(int DDOS)
{
	int x = 100 + (rand() % 300);
	shotgunTest = new Sedna::ShotgunOutlaw(x, DDOS);
	scene->addChild(shotgunTest->getBox()->getDrawNode());
	scene->addChild(shotgunTest->getSprite(), 10);
	shotgunOutlawList.push_back(new Sedna::ShotgunOutlaw(*shotgunTest));
}
