#include "SpawnManager.h"



void Sedna::SpawnManager::update(float dt, int DDOS)
{
	srand(time(0));//just to reset the random timer
	totalTime += dt;
	DDOS += 25;//just to bump up the height of the spawns so it isn't on screen
	for (unsigned int i = 0; i < tables.update(dt,tableList.size()); i++)//update all the 
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

	for (unsigned int i = 0; i < CrazyPetes.update(dt, outlawList.size()); i++)
		peteSpawn(DDOS);
}
//all spawn functions
//they create a new object and push it to the list

void Sedna::SpawnManager::tableSpawn(int DDOS)
{
	
	tableList.push_back(new Sedna::Table(100 + rand() % 300, DDOS));
	scene->addChild(tableList.back()->getBox()->getDrawNode());
	scene->addChild(tableList.back()->getSprite());
}

void Sedna::SpawnManager::outlawSpawn(int DDOS)
{
	int x = 100 + (rand() % 300);
	outlawList.push_back(new Sedna::Outlaw(x, DDOS));
	scene->addChild(outlawList.back()->getBox()->getDrawNode());
	scene->addChild(outlawList.back()->getSprite());
}

void Sedna::SpawnManager::shotgunOutlawSpawn(int DDOS)
{
	int x = 100 + (rand() % 300);
	outlawList.push_back(new Sedna::ShotgunOutlaw(x, DDOS));
	scene->addChild(outlawList.back()->getBox()->getDrawNode());
	scene->addChild(outlawList.back()->getSprite());
}

void Sedna::SpawnManager::rifleOutlawSpawn(int DDOS)
{
	int x = 100 + (rand() % 300);
	outlawList.push_back(new Sedna::RifleOutlaw(x, DDOS));
	scene->addChild(outlawList.back()->getBox()->getDrawNode());
	scene->addChild(outlawList.back()->getSprite(), 10);
}

void Sedna::SpawnManager::peteSpawn(int DDOS)
{
	int x = 100 + (rand() % 300);
	outlawList.push_back(new Sedna::CrazyPete(x, DDOS));
	scene->addChild(outlawList.back()->getBox()->getDrawNode());
	scene->addChild(outlawList.back()->getSprite(), 10);
	scene->addChild(((CrazyPete*)outlawList.back())->getDyn()->getBox()->getDrawNode());
	scene->addChild(((CrazyPete*)outlawList.back())->getDyn()->getSprite());

}
