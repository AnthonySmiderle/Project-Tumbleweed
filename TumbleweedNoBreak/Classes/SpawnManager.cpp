#include "SpawnManager.h"

void Sedna::SpawnManager::update(float dt, int DDOS)
{
	totalTime += dt;
	DDOS += 25;
	for (unsigned int i = 0; i < tables.update(dt,tableList.size()); i++)
		tableSpawn(DDOS);
	int tableChainMax = tableChain.update(dt, tableList.size());
	for (unsigned int i = 0; i < tableChainMax; i++)
		tableSpawn(DDOS);
	for (unsigned int i = 0; i < outlaws.update(dt,outlawList.size()); i++)
		outlawSpawn(DDOS);
	int outlawChainMax = outlawChain.update(dt, outlawList.size());
	for (unsigned int i = 0; i < outlawChainMax; i++)
		outlawSpawn(DDOS);
	for (unsigned int i = 0; i < shotgunOutlaws.update(dt, outlawList.size()); i++)
		shotgunOutlawSpawn(DDOS);
	for (unsigned int i = 0; i < rifleOutlaws.update(dt, outlawList.size()); i++)
		rifleOutlawSpawn(DDOS);
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
	shotgunOutlaw = new Sedna::ShotgunOutlaw(x, DDOS);
	Sedna::BaseObjectManager::outlawBObjects.push_back(shotgunOutlaw);
	scene->addChild(shotgunOutlaw->getBox()->getDrawNode());
	scene->addChild(shotgunOutlaw->getSprite(), 10);
	outlawList.push_back(new Sedna::ShotgunOutlaw(*shotgunOutlaw));
}

void Sedna::SpawnManager::rifleOutlawSpawn(int DDOS)
{
	int x = 100 + (rand() % 300);
	rifleOutlaw = new Sedna::RifleOutlaw(x, DDOS);
	Sedna::BaseObjectManager::outlawBObjects.push_back(rifleOutlaw);
	scene->addChild(rifleOutlaw->getBox()->getDrawNode());
	scene->addChild(rifleOutlaw->getSprite(), 10);
	outlawList.push_back(new Sedna::RifleOutlaw(*rifleOutlaw));
}
